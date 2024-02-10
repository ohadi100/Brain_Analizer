/**
 * @file
 * @brief     This file contains the functionality of the GDCPublisher class
 */
#include "GDCPublisher.hpp"
#include <limits>
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/os/time/Time.hpp"

using brain::publishers::gdc_publisher::GDCPublisher;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

GDCPublisher::GDCPublisher(std::shared_ptr<common::memory::PersistentMemoryFactory> persistentMemoryFactory,
                           std::shared_ptr<common::counters::CounterManager>        debugCounters,
                           ConfigurationPtr                                         configuration)
  : m_gdcAgent{persistentMemoryFactory}
  , m_persistentMemoryFactory(persistentMemoryFactory)
{
    if (debugCounters)
    {
        m_sendMessageCounter = debugCounters->CreateCounter(common::counters::info::PUBLISHER_SEND_MESSAGE,
                                                            EventCounterLevelType::COUNTER_INFO);
    }
    m_exceededMessageSizeCheck = std::make_shared<ExceededMessageSizeCheck>(configuration);
}

bool
GDCPublisher::Connect(ChangeModeCallback callback)
{
    m_callback = callback;
    m_gdcAgent.InitCallback(callback);
    m_gdcAgent.OfferService();
    return true;
}

bool
GDCPublisher::Disconnect()
{
    m_gdcAgent.StopOfferService();
    return true;
}

bool
GDCPublisher::SendMessage(std::shared_ptr<std::vector<uint8_t>> payload)
{
    if (!m_exceededMessageSizeCheck->IsValid(payload->size()))
    {
        LOG_ERROR << "message size " << payload->size() << " exceeded allowed size" << LOG_NOOP;
        return -1;
    }
    // SampleType for data.Send where
    // data =
    // ::ara::com::internal::skeleton::Event<::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge::data>
    // Event<>.Send uses sample type from
    // ::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge::data::SampleType SampleType
    // = GdcAgentGenericHuge_data_eventData
    common::counters::IncreaseCounter(m_sendMessageCounter);
    GdcAgentGenericHuge_data_eventData output;
    output.keyID     = m_gdcAgent.GetKeyId();
    output.timestamp = common::Time::GetCurrentTimeMilliSec();

    auto& buffer = output.value;
    buffer.reserve(kMaxChunkSizeInBytes);
    auto& buff  = output.value;
    std::ignore = std::copy(payload->data(), payload->data() + payload->size(), std::back_inserter(buff));

    // ChunkInfo chunkInfo{currentChunkIdx, totalChunks}; // Check if nedded
    // output.chunkInfo = std::move(chunkInfo);

    // for GDCAgent m_gdcAgent.data is a member of type ::ara::com::internal::skeleton::Event defined in base
    // class gdcagentgenerihuge_skeleton.h
    SendEvent(m_gdcAgent.data, output);
    buff.clear();

    return true;
}
