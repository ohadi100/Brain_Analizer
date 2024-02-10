/**
 * @file
 * @brief     The IDSSecurityEventSmallCommunicator is a communicator class for SOME/IP
*/
#ifndef SECURITYEVENTSMALL_COMMUNICATOR_HPP
#define SECURITYEVENTSMALL_COMMUNICATOR_HPP

#include <memory>
#include <array>
#include <chrono>
// SOME/IP services
#include "SomeIPCommunicator.hpp"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_proxy.h"


namespace brain
{
namespace brain_communicator
{
namespace someip
{
namespace idssecurityeventsmall
{

using IDSSecurityEventSmallProxy = vwg::services::security::idssecurityevent::idssecurityeventsmall::proxy::IDSSecurityEventSmallProxy;

/**
 * @class   IDSSecurityEventSmallCommunicator
 * @brief   The IDSSecurityEventSmallCommunicator is a communicator class for SOME/IP
 */
class IDSSecurityEventSmallCommunicator : public SomeIPCommunicator<IDSSecurityEventSmallProxy>
{
public:
    using UPSensorData               = Communicator::UPSensorData;
    using CounterManagerPtr          = std::shared_ptr<common::counters::CounterManager>;
    using SensorDataQueuesManagerPtr = Communicator::SensorDataQueuesManagerPtr;
    using NoiseFilterPtr             = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;
    using SecurityEventSmallDataType
        = ::vwg::services::security::idssecurityevent::idssecurityeventsmall::SecurityEventStruct;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr  queuesManager
     * @param   CounterManagerPtr debugCounters
     * @param   uint32_t flushThreshold
     * @param   const std::vector<uint32_t>& enabledInstances enabled instance IDs for the Communicator to register
     * if the list is empty, then Communicator will be registered to all instances IDs
     * @param   NoiseFilterPtr sensorNoiseFilter
     */
    IDSSecurityEventSmallCommunicator(SensorDataQueuesManagerPtr   queuesManager,
                                      CounterManagerPtr            debugCounters,
                                      uint32_t                     flushThreshold,
                                      DiagnosticsManagerPtr        diagnosticsManager,
                                      const std::vector<uint32_t>& enabledInstances  = {},
                                      NoiseFilterPtr               sensorNoiseFilter = nullptr)
      : SomeIPCommunicator<IDSSecurityEventSmallProxy>(queuesManager,
                                                       debugCounters,
                                                       flushThreshold,
                                                       diagnosticsManager,
                                                       CommunicatorId::SECURITY_EVENT_SMALL,
                                                       sensorNoiseFilter)
    {
        if (!enabledInstances.empty())
        {
            m_enabledInstances = {enabledInstances.begin(), enabledInstances.end()};
        }
    }

    ~IDSSecurityEventSmallCommunicator()
    {
        try
        {
            Stop();
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (std::exception const& /*e*/)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "destruction of the IDSSecurityEventSmallCommunicator failed and got exception." << LOG_NOOP;
        }  // only for parasoft violations
    }

    /**
     * @brief    default copy constructor
     */
    IDSSecurityEventSmallCommunicator(const IDSSecurityEventSmallCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    IDSSecurityEventSmallCommunicator(IDSSecurityEventSmallCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    IDSSecurityEventSmallCommunicator& operator=(IDSSecurityEventSmallCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    IDSSecurityEventSmallCommunicator& operator=(IDSSecurityEventSmallCommunicator&&) = delete;

private:
    virtual UPSensorData FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData) override;

    /**
     * @brief   Factory functions to register with the correct field
     * @param   IDSSecurityEventSmallProxy obj - obj to extract NotificationType field from
     */
    virtual void registerFactory(IDSSecurityEventSmallProxy& obj) override;

    /**
     * @brief   Factory functions to dergister from the correct field
     * @param   IDSSecurityEventSmallProxy obj - obj to extract NotificationType field from
     */
    virtual void deregisterFactory(IDSSecurityEventSmallProxy& obj) override;

    static UPSensorDataVectorPtr registerSecurityEventSmallSD(const SecurityEventSmallDataType& field);
};

} // namespace idssecurityeventsmall
} // namespace someip
} // namespace brain_communicator
} // namespace brain

#endif /* SECURITYEVENTSMALL_COMMUNICATOR_HPP */