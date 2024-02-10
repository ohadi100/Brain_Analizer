/**
 * @file
 * @brief     This file contains the functionality of the Communicator class
 */
#include "brain/communicator/Communicator.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterManager.hpp"

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION) && !(defined(MEB_PLATFORM)))
#include "brain/engines/security_events/SecurityEventsEngine.hpp"
using brain::engines::security_events::SecurityEventsEngine;
#endif // !defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)

using brain::brain_communicator::Communicator;
using brain::brain_noise_filter::SensorNoiseFilter;
using common::notification_handler::SensorDataQueuesManager;

Communicator::Communicator(SensorDataQueuesManagerPtr queuesManager,
                           uint32_t                   flushThreshold,
                           CommunicatorId const       communicatorId,
                           NoiseFilterPtr             sensorNoiseFilter /*=nullptr*/)
  : m_queuesManager(queuesManager)
  , m_flushTimedThreshold(flushThreshold)
  , m_sensorNoiseFilter(std::move(sensorNoiseFilter))
  , m_sdChunks{std::make_shared<SensorDataChunk>(),
               std::make_shared<SensorDataChunk>(),
               std::make_shared<SensorDataChunk>(),
               std::make_shared<SensorDataChunk>()}
  , m_totalSDsInAllChunks(0U)
  , m_communicatorId(communicatorId)
  , m_lastCreatedEventTS(0U)
{
    if (m_sensorNoiseFilter)
    {
        m_sdFilteredCounter    = m_sensorNoiseFilter->GetSDFilteredCounter();
        m_sdNotFilteredCounter = m_sensorNoiseFilter->GetSDNotFilteredCounter();
    }
}

Communicator::~Communicator()
{
    try
    {
        flushAllChunks();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the Communicator failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

Communicator::UPSensorData
Communicator::FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData)
{
    if (nullptr == sd)
    {
        hasData = false;
        return nullptr;
    }

    if (nullptr == m_sensorNoiseFilter)
    {
        // No noise filter defined, thus pass the sd
        hasData = true;
        return sd;
    }

	uint32_t const sdTag = static_cast<uint32_t>(sd->GetTag());
    if(!m_sensorNoiseFilter->IsFilteredOutBySDTag(sdTag, m_sdFilteredCounter, m_sdNotFilteredCounter, static_cast<uint32_t>(eventSize)))
    {
        // Either no sensor noise filter or sensor noise filter didn't filter the sd. Thus, return sd
        hasData = true;
        return sd;
    }

    LOG_DEBUG << "Sensor filter filtered incident with tag = " << sdTag << LOG_NOOP;
    m_droppedSensorData = std::move(sd);
    hasData = false;
    return nullptr;
}

void Communicator::handle(UPSensorData sd, size_t const eventSize, bool const preventFlush /* = false */)
{    
    // TAG validation
    auto const& sdTag = sd->GetTag();
    if (static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS) <= static_cast<uint32_t>(sdTag))
    {
        LOG_ERROR << "SD With bad tag encountered! SD tag is " << static_cast<uint32_t>(sdTag) << LOG_NOOP;
        return;
    }

    // Pass sd through noise filter
    // Pay attention that sd can't be used after next line
    bool hasData{};
    auto filteredData = FilterIncomeSD(std::move(sd), eventSize, hasData); 
    if ((nullptr == filteredData) || !hasData)
    {
        return;
    }

    // Update SD into the its priority chunck and update the m_lastCreatedEventTS
    auto const priority = filteredData->GetPriority();
    auto const chunk = m_sdChunks[static_cast<size_t>(priority)];
    m_lastCreatedEventTS = filteredData->GetCreatedTimestamp();

    chunk->emplace_back(std::move(filteredData));
    m_totalSDsInAllChunks++;

    // For each new SD event, checks all the priority Qs if they need to be flush
    if(!preventFlush)
    {
        flushAllChunks(false);
    }
}
#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION) && !(defined(MEB_PLATFORM)))

void Communicator::handleQueueAddFailed(UPSensorData sd, DropReason dropReason)
{
    SecurityEventsEngine::HandleDroppedSecurityEventExt(std::move(sd), dropReason);
}

void Communicator::flushChunk(SensorDataChunkPtr sensorChunk, SDPriority const priority)
{
    if (!m_queuesManager->AddNotificationToQueue(std::move(sensorChunk)))
    {
        auto droppedSd = GetDroppedSensorData();
        auto dropReason{DropReason::PriorityQueueInvalid};
        switch (priority)
        {
            case SDPriority::Invalid:
            break;
            case SDPriority::Critical:
            dropReason = DropReason::PriorityQueueCritical;
            break;
            case SDPriority::Important:
            dropReason = DropReason::PriorityQueueImportant;
            break;
            case SDPriority::Normal:
            dropReason = DropReason::PriorityQueueNormal;
            break;
            case SDPriority::Low:
            dropReason = DropReason::PriorityQueueLow;
            break;
            default:
                LOG_ERROR << "Unknown SD priority " << static_cast<uint32_t>(priority) << LOG_NOOP;
        }
        handleQueueAddFailed(std::move(droppedSd), dropReason);
    }

    m_sdChunks[static_cast<size_t>(priority)] = std::make_shared<SensorDataChunk>();
}
#else //!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
void Communicator::flushChunk(SensorDataChunkPtr sensorChunk, SDPriority const priority)
{
    std::ignore = m_queuesManager->AddNotificationToQueue(std::move(sensorChunk));
    m_sdChunks[static_cast<size_t>(priority)] = std::make_shared<SensorDataChunk>();
}
#endif //!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST)
void Communicator::flushAllChunks(bool const forceFlush /* = true */)
{
    for (uint8_t priority = 0; priority < common::sensor_data::PRIORITY_COUNT; ++priority)
    {
        auto& chunks = m_sdChunks[priority];
        if(chunks->empty())
        {
            continue;
        }

        // Check if flush need to be done, either by forceFlush, or max max size, or the delta time between the old data to new data exceed the threshold
        if( (forceFlush) ||
            (MAX_CHUNCKQ_SIZE <= chunks->size()) ||
            (m_lastCreatedEventTS - chunks->front()->GetCreatedTimestamp() >= m_flushTimedThreshold) )
            {
                if (m_totalSDsInAllChunks > static_cast<uint32_t>(chunks->size()))
                {
                    m_totalSDsInAllChunks -= static_cast<uint32_t>(chunks->size());  // update the counter
                }
                else
                {
                    m_totalSDsInAllChunks = 0U;
                }
                flushChunk(chunks, static_cast<SDPriority>(priority));
            }
    }
}
