/**
 * @file
 * @brief     The IDSSecurityEventNormal communicator class for SOME/IP
 */
#ifndef SECURITYEVENTNORMAL_COMMUNICATOR_HPP
#define SECURITYEVENTNORMAL_COMMUNICATOR_HPP

#include <memory>
#include <array>
#include <chrono>
#include "common/sensor_data/SensorData.hpp"
#include "SomeIPCommunicator.hpp"
#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_proxy.h"

namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace idssecurityeventnormal
{

using IDSSecurityEventNormalProxy = vwg::services::security::idssecurityevent::idssecurityevent::proxy::IDSSecurityEventProxy;

/**
 * @class   IDSSecurityEventNormalCommunicator
 * @brief   The IDSSecurityEventNormal communicator class for SOME/IP
 */
class IDSSecurityEventNormalCommunicator : public SomeIPCommunicator<IDSSecurityEventNormalProxy>
{
public:
    using UPSensorData = Communicator::UPSensorData;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using SensorDataQueuesManagerPtr = Communicator::SensorDataQueuesManagerPtr;
    using SecurityEventNormalDataType = ::vwg::services::security::idssecurityevent::idssecurityevent::SecurityEventEvent;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

public:
    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr  queuesManager
     * @param   CounterManagerPtr debugCounters
     * @param   uint32_t flushThreshold
     * @param   NoiseFilterPtr sensorNoiseFilter
     * @param   DiagnosticsManagerPtr diagnosticsManager,
     * @param   const std::vector<uint32_t>& enabledInstances enabled instance IDs for the Communicator to register
     * if the list is empty, then Communicator will be registered to all instances IDs
     * @param   NoiseFilterPtr sensorNoiseFilter
     */
    IDSSecurityEventNormalCommunicator(SensorDataQueuesManagerPtr   queuesManager,
                                       CounterManagerPtr            debugCounters,
                                       uint32_t                     flushThreshold,
                                       DiagnosticsManagerPtr        diagnosticsManager,
                                       const std::vector<uint32_t>& enabledInstances  = {},
                                       NoiseFilterPtr               sensorNoiseFilter = nullptr)
      : SomeIPCommunicator<IDSSecurityEventNormalProxy>(queuesManager,
                                                        debugCounters,
                                                        flushThreshold,
                                                        diagnosticsManager,
                                                        CommunicatorId::SECURITY_EVENT,
                                                        sensorNoiseFilter)
    {
        if (!enabledInstances.empty())
        {
            m_enabledInstances = {enabledInstances.begin(), enabledInstances.end()};
        }
    }

    ~IDSSecurityEventNormalCommunicator()
    {
        try
        {
            Stop();
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (std::exception const& /*e*/)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "destruction of the IDSSecurityEventNormalCommunicator failed and got exception." << LOG_NOOP;
        }  // only for parasoft violations
    }

    /**
     * @brief    default copy constructor
     */
    IDSSecurityEventNormalCommunicator(const IDSSecurityEventNormalCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    IDSSecurityEventNormalCommunicator(IDSSecurityEventNormalCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    IDSSecurityEventNormalCommunicator& operator=(IDSSecurityEventNormalCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    IDSSecurityEventNormalCommunicator& operator=(IDSSecurityEventNormalCommunicator&&) = delete;

private:
    virtual UPSensorData FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData) override;

    /**
     * @brief   Factory functions to register with the correct field
     * @param   IDSSecurityEventNormalProxy obj - obj to extract NotificationType field from
     */
    virtual void registerFactory(IDSSecurityEventNormalProxy& obj) override;

    /**
     * @brief   Factory functions to dergister from the correct field
     * @param   IDSSecurityEventNormalProxy obj - obj to extract NotificationType field from
     */
    virtual void deregisterFactory(IDSSecurityEventNormalProxy& obj) override;

    /**
     * @brief   Generate sensor data from incoming SecurityEvent notification
     * @param   SecurityEventNormalDataType field - obj to extract NotificationType field from
     */
    static UPSensorDataVectorPtr generateSecurityEventNormalSD(const SecurityEventNormalDataType& field);
};

} // namespace idssecurityeventnormal
} // namespace someip
} // namespace brain_communicator
} // namespace brain

#endif /* SECURITYEVENTNORMAL_COMMUNICATOR_HPP */