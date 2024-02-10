/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_skeleton.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/skeleton/event_defs.hpp"
#include "ac/com/cpp_binding/skeleton/method_defs.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace skeleton
      {
        template class Event<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Events::securityEventEvent>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElementByKey>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElements>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEvent>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEventByKey>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::unsubscribeSecurityEvent>;
        template class Skeleton<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent>;
      } // namespace skeleton
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idssecurityevent
      {

        namespace idssecurityevent
        {

          namespace skeleton
          {
            IDSSecurityEventSkeleton::IDSSecurityEventSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , securityEventEvent{port_link()}
            , m_getSecurityEventElementByKey{method_dispatcher()}
            , m_getSecurityEventElements{method_dispatcher()}
            , m_subscribeSecurityEvent{method_dispatcher()}
            , m_subscribeSecurityEventByKey{method_dispatcher()}
            , m_unsubscribeSecurityEvent{method_dispatcher()}
            {
              m_getSecurityEventElementByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key) { return getSecurityEventElementByKey(key); });

              m_getSecurityEventElements.set_function(
              [this]() { return getSecurityEventElements(); });

              m_subscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEvent(initialEventRequired, consumerId); });

              m_subscribeSecurityEventByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key, ::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEventByKey(key, initialEventRequired, consumerId); });

              m_unsubscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::UInt32 const& subscriptionId, ::vwg::stdtypes::DT_uuid const& consumerId) { return unsubscribeSecurityEvent(subscriptionId, consumerId); });

            }

            IDSSecurityEventSkeleton::IDSSecurityEventSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , securityEventEvent{port_link()}
            , m_getSecurityEventElementByKey{method_dispatcher()}
            , m_getSecurityEventElements{method_dispatcher()}
            , m_subscribeSecurityEvent{method_dispatcher()}
            , m_subscribeSecurityEventByKey{method_dispatcher()}
            , m_unsubscribeSecurityEvent{method_dispatcher()}
            {
              m_getSecurityEventElementByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key) { return getSecurityEventElementByKey(key); });

              m_getSecurityEventElements.set_function(
              [this]() { return getSecurityEventElements(); });

              m_subscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEvent(initialEventRequired, consumerId); });

              m_subscribeSecurityEventByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key, ::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEventByKey(key, initialEventRequired, consumerId); });

              m_unsubscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::UInt32 const& subscriptionId, ::vwg::stdtypes::DT_uuid const& consumerId) { return unsubscribeSecurityEvent(subscriptionId, consumerId); });

            }

            IDSSecurityEventSkeleton::IDSSecurityEventSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , securityEventEvent{port_link()}
            , m_getSecurityEventElementByKey{method_dispatcher()}
            , m_getSecurityEventElements{method_dispatcher()}
            , m_subscribeSecurityEvent{method_dispatcher()}
            , m_subscribeSecurityEventByKey{method_dispatcher()}
            , m_unsubscribeSecurityEvent{method_dispatcher()}
            {
              m_getSecurityEventElementByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key) { return getSecurityEventElementByKey(key); });

              m_getSecurityEventElements.set_function(
              [this]() { return getSecurityEventElements(); });

              m_subscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEvent(initialEventRequired, consumerId); });

              m_subscribeSecurityEventByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key, ::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEventByKey(key, initialEventRequired, consumerId); });

              m_unsubscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::UInt32 const& subscriptionId, ::vwg::stdtypes::DT_uuid const& consumerId) { return unsubscribeSecurityEvent(subscriptionId, consumerId); });

            }

            IDSSecurityEventSkeleton::IDSSecurityEventSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , securityEventEvent{std::move(token.securityEventEvent)}
            , m_getSecurityEventElementByKey{std::move(token.getSecurityEventElementByKey)}
            , m_getSecurityEventElements{std::move(token.getSecurityEventElements)}
            , m_subscribeSecurityEvent{std::move(token.subscribeSecurityEvent)}
            , m_subscribeSecurityEventByKey{std::move(token.subscribeSecurityEventByKey)}
            , m_unsubscribeSecurityEvent{std::move(token.unsubscribeSecurityEvent)}
            {
              m_getSecurityEventElementByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key) { return getSecurityEventElementByKey(key); });

              m_getSecurityEventElements.set_function(
              [this]() { return getSecurityEventElements(); });

              m_subscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEvent(initialEventRequired, consumerId); });

              m_subscribeSecurityEventByKey.set_function(
              [this](::vwg::stdtypes::DT_uuid const& key, ::ara::stdtypes::Boolean const& initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) { return subscribeSecurityEventByKey(key, initialEventRequired, consumerId); });

              m_unsubscribeSecurityEvent.set_function(
              [this](::ara::stdtypes::UInt32 const& subscriptionId, ::vwg::stdtypes::DT_uuid const& consumerId) { return unsubscribeSecurityEvent(subscriptionId, consumerId); });

            }

            ::ara::core::Result<IDSSecurityEventSkeleton::ConstructionToken>
            IDSSecurityEventSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instance, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            ::ara::core::Result<IDSSecurityEventSkeleton::ConstructionToken>
            IDSSecurityEventSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instance, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            ::ara::core::Result<IDSSecurityEventSkeleton::ConstructionToken>
            IDSSecurityEventSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instances, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            IDSSecurityEventSkeleton::ConstructionToken::~ConstructionToken() = default;
            IDSSecurityEventSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            IDSSecurityEventSkeleton::ConstructionToken& IDSSecurityEventSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            IDSSecurityEventSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , securityEventEvent{skeleton_impl->port_link()}
            , getSecurityEventElementByKey{skeleton_impl->method_dispatcher()}
            , getSecurityEventElements{skeleton_impl->method_dispatcher()}
            , subscribeSecurityEvent{skeleton_impl->method_dispatcher()}
            , subscribeSecurityEventByKey{skeleton_impl->method_dispatcher()}
            , unsubscribeSecurityEvent{skeleton_impl->method_dispatcher()}
            {
            }

            IDSSecurityEventSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , securityEventEvent{skeleton_impl->port_link()}
            , getSecurityEventElementByKey{skeleton_impl->method_dispatcher()}
            , getSecurityEventElements{skeleton_impl->method_dispatcher()}
            , subscribeSecurityEvent{skeleton_impl->method_dispatcher()}
            , subscribeSecurityEventByKey{skeleton_impl->method_dispatcher()}
            , unsubscribeSecurityEvent{skeleton_impl->method_dispatcher()}
            {
            }

            IDSSecurityEventSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , securityEventEvent{skeleton_impl->port_link()}
            , getSecurityEventElementByKey{skeleton_impl->method_dispatcher()}
            , getSecurityEventElements{skeleton_impl->method_dispatcher()}
            , subscribeSecurityEvent{skeleton_impl->method_dispatcher()}
            , subscribeSecurityEventByKey{skeleton_impl->method_dispatcher()}
            , unsubscribeSecurityEvent{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
