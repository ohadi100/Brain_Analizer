/**
 * @file
 * @brief     The communicator of QLAH
 */
#ifndef UDS_COMMUNICATOR_HPP
#define UDS_COMMUNICATOR_HPP

#include "SocketCommunicator.hpp"
#include "brain/noise_filter/sensor_noise_filter/SensorNoiseFilter.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "common/counter_manager/CounterNames.hpp"

#ifdef TESTS
namespace tests_communicators
{
    class UDSCommunicatorTest;
}

namespace tests_mock
{
	class MockUnixDomainSocketCommAgentTest;
}

namespace tests_integration
{
    class IntegrationTest;
}
#endif

namespace brain
{
namespace brain_communicator
{
namespace uds
{


/**
 * @class   UDSCommunicator
 * @brief   Communicator of QLAH
 */
class UDSCommunicator : public SocketCommunicator
{
    using CounterManagerPtr     = std::shared_ptr<common::counters::CounterManager>;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using NoiseFilterPtr        = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;
    using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

public:
    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr queuesManager
     * @param   std::string const& udsPostfixName
     * @param   CounterManagerPtr debugCounters
     * @param   uint32_t flushThreshold
     * @param   DiagnosticsManagerPtr diagnosticsManager
     * @param   DtcServiceDiscoveryEvent& serviceDiscoveryDtc
     * @param   NoiseFilterPtr sensorNoiseFilter=nullptr
     */
    UDSCommunicator(SensorDataQueuesManagerPtr queuesManager,
                    std::string const&         udsPathName,
                    CounterManagerPtr          debugCounters,
                    uint32_t                   flushThreshold,
                    DiagnosticsManagerPtr      diagnosticsManager,
                    NoiseFilterPtr             sensorNoiseFilter = nullptr);

    /**
     * @brief   Parses the qlah sensor data and chunks it
     * @param   char const* incidents
     * @param   uint32_t buflen
     * @return  true / false - indicates whether SDs were found in the buffer.
     */
    bool parseSensorData(char const* incidents, size_t const length) override;

#ifdef TESTS
    UDSCommunicator(SensorDataQueuesManagerPtr                       queuesManager,
                    std::unique_ptr<common::ids_socket::IBaseSocket> socket,
                    CounterManagerPtr                                debugCounters,
                    uint32_t                                         flushThreshold,
                    DiagnosticsManagerPtr                            diagnosticsManager,
                    NoiseFilterPtr                                   sensorNoiseFilter = nullptr)
      : SocketCommunicator(
          queuesManager, debugCounters, flushThreshold, diagnosticsManager, CommunicatorId::UDS, sensorNoiseFilter)
      , m_hostErrorMonitoringOn(
            diagnosticsManager->GetFeatureFlag(brain::adaptation_values_names::AdaptationId::HOST_ERROR_MONITORING_ON))
    {
        m_socket = std::move(socket);

        if (debugCounters)
        {
            m_EthsdCreatedCounter  = m_debugCounters->CreateCounter(common::counters::debug::ETH_SD_WAS_CREATED,
                                                                   EventCounterLevelType::COUNTER_DEBUG);
            m_hostSdCreatedCounter = m_debugCounters->CreateCounter(common::counters::debug::HOST_SD_WAS_CREATED,
                                                                    EventCounterLevelType::COUNTER_DEBUG);
        }
    }

    friend class tests_communicators::UDSCommunicatorTest;
    friend class tests_mock::MockUnixDomainSocketCommAgentTest;
    friend class tests_integration::IntegrationTest;
#endif

    std::atomic<bool>& m_hostErrorMonitoringOn;

    // counters
    std::shared_ptr<common::counters::EventCounter> m_EthsdCreatedCounter;
    std::shared_ptr<common::counters::EventCounter> m_hostSdCreatedCounter;
};

} // namespace uds
} // namespace brain_communicator
} // namespace brain

#endif /* UDS_COMMUNICATOR_HPP */
