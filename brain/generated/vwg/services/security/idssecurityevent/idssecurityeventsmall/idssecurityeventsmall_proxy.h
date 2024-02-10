/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IDSSECURITYEVENTSMALL_PROXY_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IDSSECURITYEVENTSMALL_PROXY_H

#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_common.h"

#include "ac/com/cpp_binding/proxy/event.hpp"
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

        namespace idssecurityeventsmall
        {

          namespace proxy
          {

            namespace events
            {
              using securityEvent = ::ac::com::cpp_binding::proxy::Event<::vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall::Events::securityEvent>;
            } // namespace events

            class IDSSecurityEventSmallProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<IDSSecurityEventSmall>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<IDSSecurityEventSmall>::HandleType;

              using ConstructionToken = IDSSecurityEventSmallProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit IDSSecurityEventSmallProxy(HandleType const& handle);

              ~IDSSecurityEventSmallProxy() noexcept;

              IDSSecurityEventSmallProxy(IDSSecurityEventSmallProxy&& /*other*/) noexcept;
              IDSSecurityEventSmallProxy& operator=(IDSSecurityEventSmallProxy&& /*other*/) & noexcept;
              IDSSecurityEventSmallProxy(IDSSecurityEventSmallProxy const&) = delete;
              IDSSecurityEventSmallProxy& operator=(IDSSecurityEventSmallProxy const&) = delete;

              events::securityEvent securityEvent;
            };
          } // namespace proxy
        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
