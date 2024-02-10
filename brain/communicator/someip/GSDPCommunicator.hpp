/**
 * @file
 * @brief     The GSDPCommunicator is a communicator class for SOME/IP
*/
#ifndef GSDP_COMMUNICATOR_HPP
#define GSDP_COMMUNICATOR_HPP

#include <memory>
#include <array>
#include <chrono>

#include "SomeIPCommunicator.hpp"
#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_proxy.h"


namespace brain
{
    namespace diagnostics
    {
        namespace diag_accessor
        {
            class DiagFeatureFlags;
        } // namespace diag_accessor
    } // namespace diagnostics
} // namespace brain

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace gsdp
{

using HealthIncidentProviderProxy = vwg::services::connect::gsdp::healthincidentprovider::proxy::HealthIncidentProviderProxy;

/**
 * @class   GSDPCommunicator
 * @brief   The GSDPCommunicator is a communicator class for SOME/IP
 */
class GSDPCommunicator : public SomeIPCommunicator<HealthIncidentProviderProxy>
{
public:
    using UPSensorData               = Communicator::UPSensorData;
    using CounterManagerPtr          = std::shared_ptr<common::counters::CounterManager>;
    using SensorDataQueuesManagerPtr = Communicator::SensorDataQueuesManagerPtr;
    using DiagnosticsManagerPtr      = brain::diagnostics::DiagnosticsManagerInterface::Pointer;
    using NoiseFilterPtr             = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;
    using IncidentSampleDatatype
        = vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Events::incident::SampleType;

public:
    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr  queuesManager
     * @param   CounterManagerPtr debugCounters
     * @param   uint32_t flushThreshold
     * @param   DiagnosticsManagerPtr diagnosticsManager
     * @param   NoiseFilterPtr sensorNoiseFilter
     */
    GSDPCommunicator(SensorDataQueuesManagerPtr queuesManager,
                     CounterManagerPtr          debugCounters,
                     uint32_t                   flushThreshold,
                     DiagnosticsManagerPtr      diagnosticsManager,
                     NoiseFilterPtr             sensorNoiseFilter = nullptr)
      : SomeIPCommunicator<HealthIncidentProviderProxy>(
          queuesManager, debugCounters, flushThreshold, diagnosticsManager, CommunicatorId::GSDP, sensorNoiseFilter)
      , m_diagManager(diagnosticsManager)
    {
        brain::sensor_data::SWPACSensorDataFactory::InitCounters(m_debugCounters);
    }

    ~GSDPCommunicator()
    {
        try
        {
            Stop();
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (std::exception const& /*e*/)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "destruction of the GSDPCommunicator failed and got exception." << LOG_NOOP;
        }  // only for parasoft violations
    }

    /**
     * @brief    default copy constructor
     */
    GSDPCommunicator(const GSDPCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    GSDPCommunicator(GSDPCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    GSDPCommunicator& operator=(GSDPCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    GSDPCommunicator& operator=(GSDPCommunicator&&) = delete;

#ifdef TESTS
#else 
private:
#endif
    virtual UPSensorData FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData) override;
    #if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
    virtual void handleQueueAddFailed(UPSensorData sd, DropReason dropReason) override;
    #endif

    /**
     * @brief   Factory functions to register with the correct field
     * @param   HealthIncidentProviderProxy obj - obj to extract NotificationType field from
     */
    virtual void registerFactory(HealthIncidentProviderProxy& obj) override;

    /**
     * @brief   Factory functions to dergister from the correct field
     * @param   HealthIncidentProviderProxy obj - obj to extract NotificationType field from
     */
    virtual void deregisterFactory(HealthIncidentProviderProxy& obj) override;

    UPSensorDataVectorPtr generateIncidentSD(const IncidentSampleDatatype& field);

    DiagnosticsManagerPtr m_diagManager;
};

} // namespace gsdp
} // namespace someip
} // namespace brain_communicator
} // namespace brain

#endif /* GSDP_COMMUNICATOR_HPP */
