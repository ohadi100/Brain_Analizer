/**
 * @file      legacySomeIPCommunicator.hpp
 * @brief     The legacySomeIPCommunicator is a communicator class for SOME/IP
 */
#ifndef LEGACY_SOME_IP_COMMUNICATOR_HPP
#define LEGACY_SOME_IP_COMMUNICATOR_HPP

#include <atomic>
#include <memory>
#include "Communicator.hpp"

#include <ara/com/types.h>
#include <ac/com/cpp_binding/types.hpp>
#include "Logger.hpp"

using ServiceHandle = ara::com::FindServiceHandle;

namespace brain
{
namespace brain_communicator
{
namespace someip
{
/**
 * @class   legacySomeIPCommunicator
 * @brief   The legacySomeIPCommunicator is a communicator class for SOME/IP
 */

template <typename Ptype>
class legacySomeIPCommunicator : public Communicator
{
public:
    /**
     * @fn      legacySomeIPCommunicator()
     * @brief   Ctor
     * @return  none
     */
    legacySomeIPCommunicator(const std::string&                       communicatorName,
                             Communicator::SensorDataQueuesManagerPtr queuesManager,
                             Communicator::NoiseFilterPtr             noiseFilters,
                             uint32_t const                           flushThreshold,
                             CommunicatorId const                     communicatorId)
      : Communicator(queuesManager, flushThreshold, communicatorId, noiseFilters)
      , m_communicatorName(communicatorName)
      , m_activatedOnce(false)
    {
    }

    // /**
    //  * @fn      legacySomeIPCommunicator()
    //  * @brief   Ctor for CAN communicator
    //  * @return  none
    //  */
    // legacySomeIPCommunicator(const std::string&                       communicatorName,
    //                          Communicator::SensorDataQueuesManagerPtr queuesManager)
    //   : m_communicatorName(communicatorName)
    //   , m_activatedOnce(false)
    // {
    // }

    /**
     * @fn      ~legacySomeIPCommunicator()
     * @brief   Dtor
     * @param   none
     * @return  none
     */
    virtual ~legacySomeIPCommunicator(){};

    /**
     * @fn      template<class HandleType, class SensorProxy> void InitService()
     * @brief   Initialize some ip communicator - after that call the communicator will be active if
     * @return  none
     */
    virtual void Start();

    /**
     * @fn      template<class HandleType, class SensorProxy> void InitService()
     * @brief   pure virtual functions that make sure that each communicator will start service with unique proxy.
     * @return  none
     */
    virtual void Stop();

    /**
     * @fn      IsActive
     * @return  is the communicator active (recieving messages from VW)
     */
    virtual bool
    IsActive() const
    {
        return m_proxy != nullptr;
    }

    /**
     * @fn      GetName
     * @return  the communicators name to identify in logging etc.
     */
    virtual const std::string&
    GetName() const
    {
        return m_communicatorName;
    }

protected:
    /**
     * @fn      template<class NotificationType> void RegisterSomeIP(NotificationType &field, const std::string &name)
     * @brief   Register a new Notification Handler thread for the specific Notification (i.e. for
     * trafficSampleFlowNotification). The thread reads a notification
     * @param   NotificationType& field - The field for which a registration is to be made
     * @param   std::string const& queueName - name of the sensor
     * @return  none
     */
    template <typename Notification>
    void RegisterSomeIP(Notification& field, const std::string& name);

    /** @fn     DeregisterSomeIp
     * @brief   Cancel registration to some ip service
     * @param   NotificationType& field - The field for which a registration is to be made
     * @return  none
     */
    template <typename Notification>
    void DeregisterSomeIp(Notification& field);

    /**
     * @fn      RegisterService()
     * @brief   pure virtual function that make sure that each communicator will start service with unique proxy.
     * @return  none
     */
    virtual void RegisterService() = 0;

    /**
     * @fn      DeregisterService()
     * @brief   pure virtual function that make sure that each communicator will stop service with unique proxy.
     * @return  none
     */
    virtual void DeregisterService() = 0;

    // /**
    //  * @fn      GenerateAndHandleSD()
    //  * @brief   call the successor to generate the sensor data first time before activating the chain link
    //  * @return  none
    //  */
    // virtual void GenerateAndHandleSD(const Sdata &data) = 0;

    std::string                    m_communicatorName;
    std::atomic<bool>              m_activatedOnce;
    std::unique_ptr<ServiceHandle> m_handler;
    std::unique_ptr<Ptype>         m_proxy;
};

/*
This is a template function that define callback for each sensor <according to proxy> to get notificationsץ
Each notification recived is passed to specivec sensor in order to generate sensor data and pass forward.
*/
template <typename Ptype>
template <typename Notification>
inline void
legacySomeIPCommunicator<Ptype>::RegisterSomeIP(Notification& field, const std::string& name)
{
    using VWGType = typename Notification::FieldType::value_type;

    if (::ac::com::cpp_binding::Subscription_state::subscribed == field.GetSubscriptionState())
    {
        LOG_INFO << name << " already subscribed" << LOG_NOOP;
        return;
    }

    LOG_INFO << "subscribing to: " << name << LOG_NOOP;

    field.SetReceiveHandler([this, &field, name]() {
        field.Update();

        const ara::com::SampleContainer<ara::com::SamplePtr<const typename Notification::FieldType>>& notification
            = field.GetCachedSamples();

        if (!notification.empty())
        {
            // notification is a SampleContainer, which we need to dereference.
            // *notification is ultimately a shared_ptr<vector<notification data type>>, which can be iterated upon.
            // U::value_type is a vector<notification data type>, which means U::value_type::value_type is of type
            // 'notification data type'.
            for (const VWGType& notification : *(*notification.begin()))
            {
                LOG_VERBOSE << "handle notification for: " << name << " communicator" << LOG_NOOP;
                (void)notification;
                // this->GenerateAndHandleSD(notification);
            }

            LOG_DEBUG << "Received: " << (*(*notification.begin())).size()
                      << " notification/s of type: " << typeid(*(*notification.begin())).name() << LOG_NOOP;
        }

        field.Cleanup();
    });

    // These logs will help us debug our crashes.
    LOG_VERBOSE << "RegisterSomeIP for: " << name << " finish SetReceiveHandler." << LOG_NOOP;
    field.Subscribe(ara::com::EventCacheUpdatePolicy::kNewestN, 20);
    LOG_VERBOSE << "RegisterSomeIP for: " << name << " finish Subscribe." << LOG_NOOP;
    field.Cleanup();  // empty ara's cache
    LOG_VERBOSE << "RegisterSomeIP for: " << name << " finish Cleanup." << LOG_NOOP;
}

template <typename Ptype>
template <typename Notification>
inline void
legacySomeIPCommunicator<Ptype>::DeregisterSomeIp(Notification& field)
{
    field.Cleanup();
    field.UnsetReceiveHandler();
    field.Unsubscribe();
}

template <typename Ptype>
inline void
legacySomeIPCommunicator<Ptype>::Start()
{
    ::ara::com::FindServiceHandler<typename Ptype::HandleType> const CallbackFunction
        = [this](ara::com::ServiceHandleContainer<typename Ptype::HandleType> const& handles) {
              if (false == handles.empty())
              {
                  LOG_INFO << "InitService called: proxy of type " << m_communicatorName
                           << " found, registering notifications" << LOG_NOOP;
                  typename Ptype::HandleType handleCopy = handles.front();
                  this->m_proxy                         = std::make_unique<Ptype>(handleCopy);
                  RegisterService();
                  LOG_INFO << "SELF_TEST - Communicator: " << m_communicatorName << " Activated" << LOG_NOOP;
              }
              else
              {
                  LOG_INFO << "InitService called: proxy of type: " << m_communicatorName << " not found" << LOG_NOOP;
              }
          };

    m_activatedOnce.store(true);
    ::ara::com::FindServiceHandle FSH = Ptype::StartFindService(CallbackFunction, ara::com::InstanceIdentifier::Any);
    this->m_handler                   = std::make_unique<::ara::com::FindServiceHandle>(FSH);
}

template <typename Ptype>
inline void
legacySomeIPCommunicator<Ptype>::Stop()
{
    if (m_activatedOnce)
    {
        Ptype::StopFindService(*this->m_handler);
        LOG_INFO << "Stopped find service of type " << m_communicatorName << LOG_NOOP;
    }
    else
    {
        LOG_INFO << "Stopped find service called on uninitiated " << m_communicatorName << LOG_NOOP;
    }
    if (m_proxy)
    {
        DeregisterService();
        LOG_INFO << "Deregistered service of type " << m_communicatorName << LOG_NOOP;

        /* Clean the proxy after stop service - it will be filled next time InitService will be called */
        m_proxy = nullptr;
    }
}

}  // namespace someip
}  // namespace brain_communicator
}  // namespace brain

#endif  // LEGACY_SOME_IP_COMMUNICATOR_HPP