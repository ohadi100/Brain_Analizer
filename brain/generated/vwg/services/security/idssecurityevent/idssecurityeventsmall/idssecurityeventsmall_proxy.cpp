/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_proxy.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/proxy/event_defs.hpp"
#include "ac/com/cpp_binding/proxy/proxy_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace proxy
      {
        template class Event<::vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall::Events::securityEvent>;
        template class Proxy<::vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall>;
      } // namespace proxy
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

        namespace idssecurityeventsmall
        {

          namespace proxy
          {
            IDSSecurityEventSmallProxy::IDSSecurityEventSmallProxy(HandleType const& handle)
            : Proxy<IDSSecurityEventSmall>{handle}
            , securityEvent{port_link()}
            {
            }

            IDSSecurityEventSmallProxy::~IDSSecurityEventSmallProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<IDSSecurityEventSmall>::close();
            }

            IDSSecurityEventSmallProxy::IDSSecurityEventSmallProxy(IDSSecurityEventSmallProxy&& /*other*/) noexcept = default;
            IDSSecurityEventSmallProxy& IDSSecurityEventSmallProxy::operator=(IDSSecurityEventSmallProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<IDSSecurityEventSmallProxy::ConstructionToken>
            IDSSecurityEventSmallProxy::Preconstruct(HandleType const& handle) noexcept
            {
              try
              {
                return ConstructionToken{handle};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

          } // namespace proxy
        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
