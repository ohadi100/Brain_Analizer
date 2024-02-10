/**
 * @file
 * @brief     This file contains the functionality of the SciCommunicator class
 */
#include "SciCommunicator.hpp"
#include "brain/engines/security_events/SecurityEventsEngine.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/utils/UtilsConstants.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/logger/Logger.hpp"

#include <sci/frontend/api/ClientFactory.hpp>
#include <sci/frontend/common/ReceivedSignal.hpp>
#include <sci/frontend/common/ReceivedSignalGroup.hpp>

using namespace vwg::e3p::com::sci;
using namespace brain::brain_communicator::sci_communicator;
using brain::brain_communicator::sci_communicator::SciCommunicator;
using brain::engines::security_events::SecurityEventsEngine;
using brain::engines::security_events::DropReason;

static const SciCommunicator::SciRxSignalGroups&&
initSciRxSignalGroups() noexcept
{
    static const SciCommunicator::SciRxSignalGroups newMap{
        {
            "IDS_Sensors_01",
            {
                "IdsSecurityEventCan_Timestamp",
                "IdsSecurityEventCan_EventFrame",
                "IdsSecurityEventCan_ContextData1",
                "IdsSecurityEventCan_ContextData2",
                "IdsSecurityEventCan_ContextData3",
                "IdsSecurityEventCan_ContextData4",
                "IdsSecurityEventCan_ContextData5",
                "IdsSecurityEventCan_ContextData6",
                // "SOK_IDS_Sensors_01_Signatur", // Not yet supported in E³
            },
        },
        {"IDS_SensorsA_01",
         {
             "IdsSecurityEventCanA_Timestamp",
             "IdsSecurityEventCanA_EventFrame",
             "IdsSecurityEventCanA_ContextDat1",
             "IdsSecurityEventCanA_ContextDat2",
             "IdsSecurityEventCanA_ContextDat3",
             "IdsSecurityEventCanA_ContextDat4",
             "IdsSecurityEventCanA_ContextDat5",
             "IdsSecurityEventCanA_ContextDat6"
             // "SOK_IDS_SensorsA_01_Signatur", // Not yet supported in E³
         }}};
    return std::move(newMap);
}

const SciCommunicator::SciRxSignalGroups SciCommunicator::m_sciRxSignalGroups = initSciRxSignalGroups();

SciCommunicator::SciCommunicator(SensorDataQueuesManagerPtr queuesManager,
                                 CounterManagerPtr          debugCounters,
                                 uint32_t                   flushThreshold,
                                 NoiseFilterPtr             sensorNoiseFilter)
  : Communicator(queuesManager, flushThreshold, CommunicatorId::SCI, sensorNoiseFilter)
  , m_debugCounters(debugCounters)
{
    if (m_debugCounters)
    {
        m_receivedSciSignal = m_debugCounters->CreateCounter(common::counters::debug::RECEIVED_SCI_SIGNAL_COUNTER_NAME,
                                                             EventCounterLevelType::COUNTER_DEBUG);
    }
}

SciCommunicator::~SciCommunicator()
{
    try
    {
        Stop();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the SciCommunicator failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

bool
SciCommunicator::initSignalClient()
{
    static constexpr uint8_t SCI_CLIENT_RECONECT_DELAY         = 10U;
    static constexpr uint8_t SCI_CLIENT_MAX_RECONNECT_ATTEMPTS = 10U;

    LOG_INFO << "Initializing SCI signal client" << LOG_NOOP;

    m_signalClient      = api::ClientFactory::createClient(common::IDS_APPLICATION_NAME);
    auto creationStatus = m_signalClient
                              ->connect(
                                  []() {
                                  },
                                  sci::Milliseconds(SCI_CLIENT_RECONECT_DELAY),
                                  SCI_CLIENT_MAX_RECONNECT_ATTEMPTS)
                              .get();

    if ( creationStatus != Status::kOk )
    {
        if(creationStatus == sci::Status::kNetworkError)
        {
            LOG_ERROR << "Network error received; please check if the commserver is turned on" << LOG_NOOP;
        }
        else
        {
            LOG_ERROR << "Failed to create Signal client with status " << static_cast<int>(creationStatus)
                      << " aborting" << LOG_NOOP;
        }
        
        return false;
    }

    return true;
}

void
SciCommunicator::Stop()
{
    LOG_INFO << "Deregistering SCI signal handling" << LOG_NOOP;

    // Client must be freed before the signal handlers, since it holds a weak_ptr of each signalHandler
    m_signalClient.reset();
    m_signalHandlers.clear();
}

bool
SciCommunicator::registerRxSignalGroup(std::string const& pduName, std::vector<std::string> const& signals)
{
    if (signals.empty())
    {
        LOG_WARNING << "registerRxSignalGroup called with no signals to register to" << LOG_NOOP;
        return false;
    }

    LOG_DEBUG << "Registering signal group " << pduName << LOG_NOOP;


    if (sci::ExecutionState::kConnected != m_signalClient->getExecutionState())
    {
        LOG_ERROR << "Sci client is not connected" << LOG_NOOP;
        return false;
    }

	static constexpr uint32_t SYNC_RATE_MS = 10U;
    // Initialize all received signals
    auto const timestampSignal = registerRxSignal(signals[SignalIndexes::kTimestamp], SYNC_RATE_MS);
    if (!timestampSignal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_Timestamp!" << LOG_NOOP;
        return false;
    }
    auto const eventFrameSignal = registerRxSignal(signals[SignalIndexes::kEventFrame], SYNC_RATE_MS);
    if (!eventFrameSignal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_EventFrame!" << LOG_NOOP;
        return false;
    }
    auto const contextData1Signal = registerRxSignal(signals[SignalIndexes::kContextData1], SYNC_RATE_MS);
    if (!contextData1Signal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_ContextData1!" << LOG_NOOP;
        return false;
    }
    auto const contextData2Signal = registerRxSignal(signals[SignalIndexes::kContextData2], SYNC_RATE_MS);
    if (!contextData2Signal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_ContextData2!" << LOG_NOOP;
        return false;
    }
    auto const contextData3Signal = registerRxSignal(signals[SignalIndexes::kContextData3], SYNC_RATE_MS);
    if (!contextData3Signal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_ContextData3!" << LOG_NOOP;
        return false;
    }
    auto const contextData4Signal = registerRxSignal(signals[SignalIndexes::kContextData4], SYNC_RATE_MS);
    if (!contextData4Signal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_ContextData4!" << LOG_NOOP;
        return false;
    }
    auto const contextData5Signal = registerRxSignal(signals[SignalIndexes::kContextData5], SYNC_RATE_MS);
    if (!contextData5Signal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_ContextData5!" << LOG_NOOP;
        return false;
    }
    auto const contextData6Signal = registerRxSignal(signals[SignalIndexes::kContextData6], SYNC_RATE_MS);
    if (!contextData6Signal)
    {
        LOG_DEBUG << "Failed to create received signal IdsSecurityEventCan_ContextData6!" << LOG_NOOP;
        return false;
    }
    // auto const signaturSignal = registerRxSignal(signals[SignalIndexes::kSignatur], SYNC_RATE_MS); // Not yet
    // supported in E³

    LOG_DEBUG << "Finished the registering signal group " << pduName << LOG_NOOP;

    auto signalGroupResult = m_signalClient->createReceivedSignalGroup(sci::Milliseconds(SYNC_RATE_MS),
                                                                       {timestampSignal,
                                                                        eventFrameSignal,
                                                                        contextData1Signal,
                                                                        contextData2Signal,
                                                                        contextData3Signal,
                                                                        contextData4Signal,
                                                                        contextData5Signal,
                                                                        contextData6Signal});
    if (!signalGroupResult)
    {
        LOG_ERROR << "Failed to create signal group " << pduName << LOG_NOOP;
        return false;
    }
    std::unique_ptr<sci::ReceivedSignalGroup> signalGroup = std::move(signalGroupResult.value());

    auto signalHandler = std::make_shared<SciSignalGroupHandler>(
        pduName,
        [this](std::string const& signalName,
               std::vector<sci::ReceivedSignal const*> const&
                   signals) {  // This callback will be called for each signaled group
            LOG_DEBUG << "Handling SCI signal " << signalName << LOG_NOOP;
            common::counters::IncreaseCounter(m_receivedSciSignal);

            m_groupSignalValues.clear();

            for (auto const& signal : signals)
            {
                auto const& sigName = signal->name();
                // received signal value changed event, get result
                auto signalValueResult = signal->getRawValue();
                if (signalValueResult)
                {
                    auto signalRawValue = signalValueResult.value();
                    LOG_DEBUG << "Received raw signal value " << signalRawValue << " for signal " << sigName
                              << LOG_NOOP;
                    m_groupSignalValues.push_back(signalRawValue);
                }
                else
                {
                    switch (signalValueResult.error())
                    {
                    case sci::Status::kNeverReceived:
                        LOG_ERROR << "Signal " << sigName << " was never received" << LOG_NOOP;
                        break;
                    case sci::Status::kTimeout: {
                        LOG_INFO << "Signal " << sigName << " has time out." << LOG_NOOP;
                    }
                    break;
                    default:
                        LOG_ERROR << "Signal " << sigName << " error on get request" << LOG_NOOP;
                        break;
                    }
                }
            }

            if (m_groupSignalValues.size()
                > SignalIndexes::kContextData6)  // make sure all the signals from a SACID sensor are updated
            {
                bool sdCreatedSuccessfully{};
                auto sd = std::make_unique<brain::sensor_data::SecurityEventSensorData>(m_groupSignalValues,
                                                                                        sdCreatedSuccessfully);
                if (sdCreatedSuccessfully)
                {
                    LOG_VERBOSE << "Created SCI SensorData" << LOG_NOOP;
                    sd->SetTag(SensorDataTag::SD_SACID_CAN_EVENT);
                    size_t const eventSize = m_groupSignalValues.size() * sizeof(uint64_t);
                    handle(std::move(sd), eventSize, true);
                }
                else if (sd)
                {
                    LOG_ERROR << "SCI SensorData not created" << LOG_NOOP;
                    SecurityEventsEngine::HandleDroppedSecurityEventExt(std::move(sd),
                                                                        DropReason::SacidCanEventCommunicator);
                }
            }
        });

    if (sci::Status::kOk != signalGroup->registerEventHandler(sci::EventType::kOnChange | sci::EventType::kTimeout, signalHandler))
    {
        LOG_ERROR << "Failed to register signal event handler for signal group " << pduName << LOG_NOOP;
        return false;
    }

    std::ignore = m_signalHandlers.insert({signalHandler, std::move(signalGroup)});
    return true;
}

std::shared_ptr<ReceivedSignal>
SciCommunicator::registerRxSignal(std::string const& signalName, uint32_t syncRateMs)
{
    LOG_DEBUG << "Registering SCI signal handler for '" << signalName << "' with sync rate " << syncRateMs << LOG_NOOP;

    if (sci::ExecutionState::kConnected != m_signalClient->getExecutionState())
    {
        return {};
    }

    auto signalResultFuture  = m_signalClient->createReceivedSignal(signalName, sci::Milliseconds(syncRateMs), true).get();
   	auto signalResult = std::move(*signalResultFuture);
    if (!signalResult)
    {
        LOG_ERROR << "Could not create signal '" << signalName << "' using the signal client" << LOG_NOOP;
        return {};
    }

    return signalResult;
}

void
SciCommunicator::Start()
{
    if (!initSignalClient())
    {
        LOG_ERROR << "Couldn't initialize SCI library or Failed to create Signal client" << LOG_NOOP;
        return;
    }

    if (!registerSignalHandling())
    {
        LOG_WARNING << "Registering handler to one or more signals has failed" << LOG_NOOP;
    }
}

bool
SciCommunicator::registerSignalHandling()
{
    bool signalGroupsRegistered = true;

    for (auto const& rxSignalGroup : SciCommunicator::m_sciRxSignalGroups)
    {
        signalGroupsRegistered
            = signalGroupsRegistered && registerRxSignalGroup(rxSignalGroup.first, rxSignalGroup.second);
    }

    return signalGroupsRegistered;
}

SciCommunicator::UPSensorData
SciCommunicator::FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData)
{
    auto filteredSd = Communicator::FilterIncomeSD(std::move(sd), eventSize, hasData);
    auto droppedSd  = GetDroppedSensorData();
    if (droppedSd)
    {
        SecurityEventsEngine::HandleDroppedSecurityEventExt(std::move(droppedSd), DropReason::SacidCanEventNoiseFilter);
    }
    return filteredSd;
}
