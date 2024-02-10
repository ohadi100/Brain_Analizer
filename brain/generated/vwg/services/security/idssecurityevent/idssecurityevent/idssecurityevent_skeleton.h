/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IDSSECURITYEVENT_SKELETON_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IDSSECURITYEVENT_SKELETON_H

#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_common.h"

#include <memory>
#include "ac/com/cpp_binding/skeleton/event.hpp"
#include "ac/com/cpp_binding/skeleton/method.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton.hpp"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

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
            namespace events
            {
              using securityEventEvent = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Events::securityEventEvent>;
            } // namespace events

            namespace methods
            {
              using getSecurityEventElementByKey = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElementByKey>;
              using getSecurityEventElements = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElements>;
              using subscribeSecurityEvent = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEvent>;
              using subscribeSecurityEventByKey = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEventByKey>;
              using unsubscribeSecurityEvent = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::unsubscribeSecurityEvent>;
            } // namespace methods

            class IDSSecurityEventSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<IDSSecurityEvent>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                events::securityEventEvent securityEventEvent;

                methods::getSecurityEventElementByKey getSecurityEventElementByKey;
                methods::getSecurityEventElements getSecurityEventElements;
                methods::subscribeSecurityEvent subscribeSecurityEvent;
                methods::subscribeSecurityEventByKey subscribeSecurityEventByKey;
                methods::unsubscribeSecurityEvent unsubscribeSecurityEvent;

                ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances, ::ara::com::MethodCallProcessingMode mode);
                ConstructionToken(::ara::com::InstanceIdentifier const& instance, ::ara::com::MethodCallProcessingMode mode);
                ConstructionToken(::ara::core::InstanceSpecifier instance, ::ara::com::MethodCallProcessingMode mode);
                ~ConstructionToken();
                ConstructionToken(ConstructionToken&& /*unused*/) noexcept;
                ConstructionToken& operator=(ConstructionToken&& /*unused*/) & noexcept;

                ConstructionToken(ConstructionToken const&) = delete;
                ConstructionToken& operator=(ConstructionToken const&) = delete;
              };

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::com::InstanceIdentifierContainer const& /*instances*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::com::InstanceIdentifier const& /*instance*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::core::InstanceSpecifier /*instance*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              explicit IDSSecurityEventSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IDSSecurityEventSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IDSSecurityEventSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IDSSecurityEventSkeleton(ConstructionToken&& token) noexcept;

              using getSecurityEventElementByKeyOutput = ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElementByKey::Output;
              virtual ::ara::core::Future<getSecurityEventElementByKeyOutput>
              getSecurityEventElementByKey(::vwg::stdtypes::DT_uuid const& key) = 0;

              using getSecurityEventElementsOutput = ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElements::Output;
              virtual ::ara::core::Future<getSecurityEventElementsOutput>
              getSecurityEventElements() = 0;

              using subscribeSecurityEventOutput = ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEvent::Output;
              virtual ::ara::core::Future<subscribeSecurityEventOutput>
              subscribeSecurityEvent(::ara::stdtypes::Boolean initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) = 0;

              using subscribeSecurityEventByKeyOutput = ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEventByKey::Output;
              virtual ::ara::core::Future<subscribeSecurityEventByKeyOutput>
              subscribeSecurityEventByKey(::vwg::stdtypes::DT_uuid const& key, ::ara::stdtypes::Boolean initialEventRequired, ::vwg::stdtypes::DT_uuid const& consumerId) = 0;

              using unsubscribeSecurityEventOutput = ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::unsubscribeSecurityEvent::Output;
              virtual ::ara::core::Future<unsubscribeSecurityEventOutput>
              unsubscribeSecurityEvent(::ara::stdtypes::UInt32 subscriptionId, ::vwg::stdtypes::DT_uuid const& consumerId) = 0;

              events::securityEventEvent securityEventEvent;

              methods::getSecurityEventElementByKey m_getSecurityEventElementByKey;
              methods::getSecurityEventElements m_getSecurityEventElements;
              methods::subscribeSecurityEvent m_subscribeSecurityEvent;
              methods::subscribeSecurityEventByKey m_subscribeSecurityEventByKey;
              methods::unsubscribeSecurityEvent m_unsubscribeSecurityEvent;

            };
          } // namespace skeleton
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
