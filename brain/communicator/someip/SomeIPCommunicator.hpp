/**
 * @file
 * @brief     The SomeIPCommunicator is a communicator class for SOME/IP
*/
#ifndef SOMEIP_COMMUNICATOR_HPP
#define SOMEIP_COMMUNICATOR_HPP

#include <memory>
#include <typeindex>
#include "brain/communicator/Communicator.hpp"
#include "brain/noise_filter/sensor_noise_filter/SensorNoiseFilter.hpp"
#include "brain/sensor_data/swpac/SWPACSensorDataFactory.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include <ara/com/types.h>
#include <set>


namespace brain
{
namespace brain_communicator
{
namespace someip
{

/**
 * @class   SomeIPCommunicator
 * @brief   The SomeIPCommunicator is a communicator class for SOME/IP
 */
template<typename ProxyType>
class SomeIPCommunicator : public Communicator
{
public:
    using UPSensorData      = Communicator::UPSensorData;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using NoiseFilterPtr    = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;

    using EventCounter          = common::counters::EventCounter;
    using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
    using UPSensorDataVector    = std::vector<UPSensorData>;
    using UPSensorDataVectorPtr = std::shared_ptr<UPSensorDataVector>;
    using EnabledInstancesSet   = std::set<uint32_t>;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr queuesManager
     * @param   CounterManagerPtr debugCounters
     * @param   uint32_t flushThreshold
     * @param   DiagnosticsManagerPtr diagnosticsManager,
     * @param   CommunicatorId const communicatorId
     * @param   NoiseFilterPtr sensorNoiseFilter
     */
    SomeIPCommunicator(SensorDataQueuesManagerPtr queuesManager,
                       CounterManagerPtr          debugCounters,
                       uint32_t                   flushThreshold,
                       DiagnosticsManagerPtr      diagnosticsManager,
                       CommunicatorId const       communicatorId,
                       NoiseFilterPtr             sensorNoiseFilter = nullptr);
    /**
     * @brief    default constructor
     */
    SomeIPCommunicator() = default;

    /**
     * @brief    default copy constructor
     */
    SomeIPCommunicator(const SomeIPCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    SomeIPCommunicator(SomeIPCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    SomeIPCommunicator& operator=(SomeIPCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    SomeIPCommunicator& operator=(SomeIPCommunicator&&) = delete;

    /**
     * @brief   Dtor
     */
    virtual ~SomeIPCommunicator() = default;

    /**
     * @brief   Start communication with the sensor
     */
    virtual void Start() override;

    /**
     * @brief   Stop communication with the sensor
     */
    virtual void Stop() override;
    
    /**
     * @brief   Handles available samples for every registered field
     */
    virtual void HandleNewSamples() override;


#ifndef TESTS
protected:
#endif

    CounterManagerPtr m_debugCounters;
    std::shared_ptr<EventCounter> m_sdCreatedCounter;
    std::shared_ptr<EventCounter> m_failedCreatingSDCounter;
    std::vector<std::unique_ptr<ProxyType>> m_proxies;
    std::vector<std::unique_ptr<ara::com::FindServiceHandle>> m_findServiceHandles;
    DiagnosticsManagerPtr m_diagnosticManger;
    std::unordered_map<std::type_index, std::vector<std::function<void()>>> m_fieldHandlers;

    EnabledInstancesSet m_enabledInstances;

    /**
     * @brief   Register a new Notification Handler thread for sepcified Notification
     * @param   NotificationType& field - field to register
     */
    template<typename NotificationType, typename SDGenerationCallback>
    void registerSomeIP(NotificationType& field, SDGenerationCallback callback);

    /**
     * @brief   Deregister an existing subscriber of the specific Notification
     * @param   NotificationType& field - The field for which a deregister is to be made
     */
    template <typename NotificationType>
    void deregisterSomeIP(NotificationType& field);

#ifndef TESTS
private:
#endif

    void findServiceCallback(ara::com::ServiceHandleContainer<typename ProxyType::HandleType> handles, ara::com::FindServiceHandle /*handle*/);

    /**
     * @brief   Factory functions that make sure that registerSomeIP is called with the correct field
     * @param   ProxyType obj - obj to extract NotificationType field from
     */
    virtual void registerFactory(ProxyType& obj) = 0;

    /**
     * @brief   Factory function verifying deregisterSomeIP is invoked for the correct field
     * @param   ProxyType obj - obj to extract NotificationType field from
     */
    virtual void deregisterFactory(ProxyType& obj) = 0;

    /**
     * @brief   Subscription change handler, used to identify service registry status
     * @param   SubscriptionState state - updated subscription state
     */
    void subscriptionChangedHandler(::ara::com::SubscriptionState state);

    /**
     * @brief   return the instance id number from the instanceID string.
     * Assumed always instance ID number concated at the end. example: IdsHostSensor4 -> instanceID num is 4
     * @param   instanceIDStr - instance id string of a service
     * @return  instanceID number
     */
    uint32_t GetInstanceIdNum(std::string instanceIDStr)
    {
        size_t last_index = instanceIDStr.find_last_not_of("0123456789");
        std::string result = instanceIDStr.substr(last_index + 1);
        uint32_t id = result.empty() ? 0U : static_cast<uint32_t>(std::stoul(result));

        return id;
    }
};

template<typename ProxyType>
SomeIPCommunicator<ProxyType>::SomeIPCommunicator(
    SensorDataQueuesManagerPtr queuesManager,
    CounterManagerPtr debugCounters,
    uint32_t const flushThreshold,
    DiagnosticsManagerPtr diagnosticsManager,
    CommunicatorId const communicatorId,
    NoiseFilterPtr sensorNoiseFilter) :
    Communicator(queuesManager, flushThreshold, communicatorId, sensorNoiseFilter),
    m_debugCounters(debugCounters),
    m_proxies(0),
    m_findServiceHandles(0),
    m_diagnosticManger(diagnosticsManager),
    m_fieldHandlers({}),
    m_enabledInstances({})
{
    if (debugCounters
        && ((m_communicatorId > brain::brain_communicator::CommunicatorId::INVALID)
            && (m_communicatorId < brain::brain_communicator::CommunicatorId::COMMUNICATORS_COUNT)))
    {
        m_sdCreatedCounter = debugCounters->CreateCounter(common::counters::debug::SD_CREATED(communicatorId), EventCounterLevelType::COUNTER_DEBUG);
        m_failedCreatingSDCounter = debugCounters->CreateCounter(common::counters::warning::SD_WAS_NOT_CREATED(communicatorId), EventCounterLevelType::COUNTER_WARNING);
    }
}

template<typename ProxyType>
void SomeIPCommunicator<ProxyType>::Start()
{
    LOG_VERBOSE << "Start SomeIPCommunicator" << LOG_NOOP;
    if (!(m_findServiceHandles.empty()) || !(m_proxies.empty()))
    {
        LOG_ERROR << "Proxies/handlers still exist, has SomeIPCommunicator already started?" << LOG_NOOP;
        return;
    }

    m_findServiceHandles.emplace_back(std::make_unique<ara::com::FindServiceHandle>(ProxyType::StartFindService(
        std::bind(&SomeIPCommunicator::findServiceCallback, this, std::placeholders::_1, std::placeholders::_2))));
}

template<typename ProxyType>
void SomeIPCommunicator<ProxyType>::findServiceCallback(
    ara::com::ServiceHandleContainer<typename ProxyType::HandleType> handles, ara::com::FindServiceHandle /*handle*/)
{
    LOG_DEBUG << "FindServiceHandle callback invoked with " << static_cast<unsigned long int>(handles.size())
              << " handles" << LOG_NOOP;

    // Diag DTC - 0x600501 - ids_evt_EventIdsBackendCommunicationUnavailable
    m_diagnosticManger->UpdateServiceDiscoveryStatus(m_communicatorId, !handles.empty());
    if (handles.empty())
    {
        LOG_INFO << "Service callback found 0 handles communicator Id is : " << static_cast<uint8_t>(m_communicatorId)
                 << LOG_NOOP;  // The log means the IDS didn't find the service (ECU with some IP communication)
        return;
    }

    for (auto & handleCopy : handles)
    {
        LOG_INFO << "FindServiceHandle callback identified new handle: instance_id ["
                 << handleCopy.GetInstanceId().toString().data() << "]" << LOG_NOOP;

        auto proxy = std::make_unique<ProxyType>(handleCopy);
        std::string instanceIdStr = handleCopy.GetInstanceId().toString().data();
        uint32_t instanceId = GetInstanceIdNum(instanceIdStr);

        bool shouldRegisterInstance = m_enabledInstances.empty() or (m_enabledInstances.end() != m_enabledInstances.find(instanceId));
        if (shouldRegisterInstance)
        {
            try
            {
                LOG_INFO << "findServiceCallback registering instanceId = " << instanceIdStr << ",(" << instanceId
                         << ")" << LOG_NOOP;
                registerFactory(*proxy);
                m_proxies.emplace_back(std::move(proxy));
            }
            // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
            catch (const std::exception& e)
            // parasoft-end-suppress AUTOSAR-A15_3_4-a
            {
                LOG_ERROR << "FindServiceHandle callback failed at proxy initialization: " << e.what() << LOG_NOOP;
            }
        }
        else
        {
            LOG_DEBUG << "findServiceCallback disabled instanceId = " << instanceIdStr << ",(" << instanceId << ")"
                      << LOG_NOOP;
        }
    }
}

template<typename ProxyType>
void SomeIPCommunicator<ProxyType>::Stop()
{
    if (!m_proxies.empty())
    {
        for (auto & proxy : m_proxies)
        {
            deregisterFactory(*proxy);
    	}

	    m_proxies.clear();
    }

    if (!m_findServiceHandles.empty())
    {
        for (auto & handler : m_findServiceHandles)
        {
            ProxyType::StopFindService(*handler);
        }

	    m_findServiceHandles.clear();
    }
}

template<typename ProxyType>
template<typename NotificationType, typename SDGenerationCallback>
void SomeIPCommunicator<ProxyType>::registerSomeIP(NotificationType& field, SDGenerationCallback callback)
{
    if (::ac::com::cpp_binding::Subscription_state::subscribed == field.GetSubscriptionState())
    {
        LOG_INFO << "Already subscribed!" << LOG_NOOP;
        return;
    }

    std::function<void()> receiveHandler =
        [this, &field, callback = std::move(callback)]() {
            LOG_VERBOSE << "Entered Receive Handler!" << LOG_NOOP;
            const auto result = field.GetNewSamples([this, &callback](const auto& sample) {
                LOG_DEBUG << "Got new SOME/IP message" << LOG_NOOP;
                UPSensorDataVectorPtr sdVector = callback(*sample);

                if (nullptr == sdVector)
                {
                    LOG_VERBOSE << "Didn't generate SD" << LOG_NOOP;
                    common::counters::IncreaseCounter(m_failedCreatingSDCounter);
                    return;
                }

                for (auto& sd : *sdVector)
                {
                    if (!sd)
                    {
                        LOG_WARNING << "Received an invalid SD" << LOG_NOOP;
                        continue;
                    }

                    LOG_DEBUG << "Created SD from sample with tag=" << static_cast<long unsigned int>(sd->GetTag())
                              << ", Enqueuing" << LOG_NOOP;
                    common::counters::IncreaseCounter(m_sdCreatedCounter);
                    handle(std::move(sd), sizeof(*sample));
                }
            });

            LOG_DEBUG << "Receive Handler result=" << result.Value() << LOG_NOOP;
            if (!result)
            {
                auto errorString = std::string(result.Error().Message().begin(), result.Error().Message().end());
                LOG_ERROR << "sample's GetNewSamples Failed with error= " << errorString.c_str() << LOG_NOOP;
            }
        };

    // Maximum count of someIP samples per field per polling
    static constexpr std::size_t someIPSamplePollingCount = 100U;
    field.SetSubscriptionStateChangeHandler(std::bind(&SomeIPCommunicator<ProxyType>::subscriptionChangedHandler, this, std::placeholders::_1));
    field.Subscribe(someIPSamplePollingCount);

    auto const& fieldTypeId = typeid(field);
    m_fieldHandlers[fieldTypeId].emplace_back(receiveHandler);
}


template<typename ProxyType>
void SomeIPCommunicator<ProxyType>::HandleNewSamples()
{
    for (auto const& field : m_fieldHandlers)
    {
        for (auto const& fieldHandler: field.second)
        {
            fieldHandler();
        }
    }
}


template<typename ProxyType>
template <typename NotificationType>
void SomeIPCommunicator<ProxyType>::deregisterSomeIP(NotificationType & field)
{
    field.UnsetSubscriptionStateChangeHandler();
    field.UnsetReceiveHandler();
    field.Unsubscribe();
    std::ignore = m_fieldHandlers.erase(typeid(field));
}

template<typename ProxyType>
void SomeIPCommunicator<ProxyType>::subscriptionChangedHandler(::ara::com::SubscriptionState state)
{
    LOG_VERBOSE << "SomeIPCommunicator::subscriptionChangedHandler" << LOG_NOOP;

    switch(state) 
    {
	case ::ara::com::SubscriptionState::kSubscribed:
        m_diagnosticManger->UpdateServiceRegistyStatus(true);      // Diag DTC - 0x600502 - ids_service_registry_unavailable
        LOG_VERBOSE << "subscriptionChangedHandler = kSubscribed" << LOG_NOOP;
        break;
	case ::ara::com::SubscriptionState::kNotSubscribed:
        m_diagnosticManger->UpdateServiceRegistyStatus(false);     // Diag DTC - 0x600502 - ids_service_registry_unavailable
        LOG_VERBOSE << "subscriptionChangedHandler = kNotSubscribed" << LOG_NOOP;
        break;
	case ::ara::com::SubscriptionState::kSubscriptionPending:
            LOG_VERBOSE << "subscriptionChangedHandler = kSubscriptionPending" << LOG_NOOP;
            break;
    default:
        break;
	}
}

} // namespace someip
} // namespace brain_communicator
} // namespace brain

#endif /* SOMEIP_COMMUNICATOR_HPP */