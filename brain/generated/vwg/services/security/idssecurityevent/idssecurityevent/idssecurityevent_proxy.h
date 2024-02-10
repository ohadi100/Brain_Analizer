/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IDSSECURITYEVENT_PROXY_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IDSSECURITYEVENT_PROXY_H

#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_common.h"

#include "ac/com/cpp_binding/proxy/event.hpp"
#include "ac/com/cpp_binding/proxy/method.hpp"
#include "ac/com/cpp_binding/proxy/proxy.hpp"
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

          namespace proxy
          {

            namespace events
            {
              using securityEventEvent = ::ac::com::cpp_binding::proxy::Event<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Events::securityEventEvent>;
            } // namespace events

            namespace methods
            {
              using getSecurityEventElementByKey = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElementByKey>;
              using getSecurityEventElements = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElements>;
              using subscribeSecurityEvent = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEvent>;
              using subscribeSecurityEventByKey = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEventByKey>;
              using unsubscribeSecurityEvent = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::unsubscribeSecurityEvent>;
            } // namespace methods

            class IDSSecurityEventProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<IDSSecurityEvent>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<IDSSecurityEvent>::HandleType;

              using ConstructionToken = IDSSecurityEventProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit IDSSecurityEventProxy(HandleType const& handle);

              ~IDSSecurityEventProxy() noexcept;

              IDSSecurityEventProxy(IDSSecurityEventProxy&& /*other*/) noexcept;
              IDSSecurityEventProxy& operator=(IDSSecurityEventProxy&& /*other*/) & noexcept;
              IDSSecurityEventProxy(IDSSecurityEventProxy const&) = delete;
              IDSSecurityEventProxy& operator=(IDSSecurityEventProxy const&) = delete;

              events::securityEventEvent securityEventEvent;
              methods::getSecurityEventElementByKey getSecurityEventElementByKey;
              methods::getSecurityEventElements getSecurityEventElements;
              methods::subscribeSecurityEvent subscribeSecurityEvent;
              methods::subscribeSecurityEventByKey subscribeSecurityEventByKey;
              methods::unsubscribeSecurityEvent unsubscribeSecurityEvent;
            };
          } // namespace proxy
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
