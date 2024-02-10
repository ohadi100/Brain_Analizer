/**
 * @file
 * @brief     A communicator based on Unix Domain Socket (UDS). Used for QLAH.
 */
#include "brain/communicator/uds/UDSCommunicator.hpp"
#include "brain/sensor_data/qlah/EthSensorData.hpp"
#include "brain/sensor_data/qlah/HostSensorData.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include <cstring>

#if defined(EEE_PLATFORM)
#include "common/utils/socket/UnixDomainSocket.hpp"
using common::ids_socket::UnixDomainSocket;

#elif defined (SIMULATION)
#include "common/mocks/ids_socket/MockSocket.hpp"
using common::mocks::MockSocket;
#endif

using brain::brain_communicator::uds::UDSCommunicator;
using common::sensor_data::SensorDataTag;
using namespace common::sensor_data;

UDSCommunicator::UDSCommunicator(SensorDataQueuesManagerPtr queuesManager,
                                 std::string const&         udsPathName,
                                 CounterManagerPtr          debugCounters,
                                 uint32_t                   flushThreshold,
                                 DiagnosticsManagerPtr      diagnosticsManager,
                                 NoiseFilterPtr             sensorNoiseFilter)
  : SocketCommunicator(
      queuesManager, debugCounters, flushThreshold, diagnosticsManager, CommunicatorId::UDS, sensorNoiseFilter)
  , m_hostErrorMonitoringOn(
        diagnosticsManager->GetFeatureFlag(brain::adaptation_values_names::AdaptationId::HOST_ERROR_MONITORING_ON))
{
#if defined(EEE_PLATFORM)
    // Use a non blocking socket
    m_socket = std::make_unique<UnixDomainSocket>(udsPathName, debugCounters);
#elif defined(SIMULATION)
    m_socket = std::make_unique<MockSocket>();
    static_cast<void>(udsPathName);
#endif
    if (m_debugCounters)
    {
        m_EthsdCreatedCounter  = m_debugCounters->CreateCounter(common::counters::debug::ETH_SD_WAS_CREATED,
                                                               EventCounterLevelType::COUNTER_DEBUG);
        m_hostSdCreatedCounter = m_debugCounters->CreateCounter(common::counters::debug::HOST_SD_WAS_CREATED,
                                                                EventCounterLevelType::COUNTER_DEBUG);
    }
}

bool UDSCommunicator::parseSensorData(char const* incidents, size_t const length)
{
    bool hadData = false;
    bool success= false;
    rapidjson::Document incidentsJson;
    if (incidentsJson.Parse<rapidjson::kParseStopWhenDoneFlag>(incidents, length).HasParseError())
    {
        LOG_WARNING << "rapidjson failed to parse the incidents - [" << incidents << "]" << LOG_NOOP;
        return false;
    }

    if (incidentsJson.HasMember("ethSensor"))
    {
        rapidjson::Value incidentsEthernet;
        incidentsEthernet = incidentsJson["ethSensor"];

        // Calculate incident size
        static size_t const ETH_EVENT_PREFIX_SIZE = 17U;
        size_t const incidentsSize = (length > ETH_EVENT_PREFIX_SIZE) ? (length - ETH_EVENT_PREFIX_SIZE) : length;
        // Minus 2 for comma and space between events
        size_t const eventSize = (incidentsSize / incidentsEthernet.Size()) - 2 * (incidentsEthernet.Size() - 1);

        auto ethernetEvent = incidentsEthernet.Begin();       
        for (; ethernetEvent != incidentsEthernet.End(); ++ethernetEvent)
            {
                UPSensorData sd = std::make_unique<brain::sensor_data::EthSensorData>(*ethernetEvent, success);
                if (success)
                {
                    LOG_VERBOSE << "Created QLAH EthSensorData" << LOG_NOOP;
                    sd->SetTag(SensorDataTag::SD_QLAH_ETH);
                    
                    common::counters::IncreaseCounter(m_EthsdCreatedCounter);
                    hadData = true;
                    handle(std::move(sd), eventSize, true); // Prevent flush until parsing is completed
                }
            }

    }

    if (m_hostErrorMonitoringOn && incidentsJson.HasMember("hostSensor"))
    {
        rapidjson::Value incidentsHost;
        incidentsHost = incidentsJson["hostSensor"];

        // Calculate incident size
        static size_t const HOST_EVENT_PREFIX_SIZE = 18U;
        size_t const incidentsSize = (length > HOST_EVENT_PREFIX_SIZE) ? (length - HOST_EVENT_PREFIX_SIZE) : length;
        size_t const eventSize = (incidentsSize / incidentsHost.Size()) - 2 * (incidentsHost.Size() - 1);

        auto hostIncident = incidentsHost.Begin();
        for (; hostIncident != incidentsHost.End(); ++hostIncident)
        {
            UPSensorData sd = std::make_unique<brain::sensor_data::HostSensorData>(*hostIncident, success);
            if (success)
            {
                hadData = true;
                LOG_VERBOSE << "Created QLAH HostSensorData" << LOG_NOOP;
                sd->SetTag(SensorDataTag::SD_QLAH_HOST);
                common::counters::IncreaseCounter(m_hostSdCreatedCounter);
                handle(std::move(sd), eventSize, true); // Prevent flush until parsing is completed
            }
        }
    }

    flushAllChunks(false); // Only flush chunks if required
    return hadData;
}