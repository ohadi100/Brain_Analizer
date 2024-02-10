/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_proxy.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/proxy/event_defs.hpp"
#include "ac/com/cpp_binding/proxy/method_defs.hpp"
#include "ac/com/cpp_binding/proxy/proxy_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace proxy
      {
        template class Event<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Events::securityEventEvent>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElementByKey>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::getSecurityEventElements>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEvent>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::subscribeSecurityEventByKey>;
        template class Method<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent::Methods::unsubscribeSecurityEvent>;
        template class Proxy<::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent>;
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

        namespace idssecurityevent
        {

          namespace proxy
          {
            IDSSecurityEventProxy::IDSSecurityEventProxy(HandleType const& handle)
            : Proxy<IDSSecurityEvent>{handle}
            , securityEventEvent{port_link()}
            , getSecurityEventElementByKey{port_link()}
            , getSecurityEventElements{port_link()}
            , subscribeSecurityEvent{port_link()}
            , subscribeSecurityEventByKey{port_link()}
            , unsubscribeSecurityEvent{port_link()}
            {
            }

            IDSSecurityEventProxy::~IDSSecurityEventProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<IDSSecurityEvent>::close();
            }

            IDSSecurityEventProxy::IDSSecurityEventProxy(IDSSecurityEventProxy&& /*other*/) noexcept = default;
            IDSSecurityEventProxy& IDSSecurityEventProxy::operator=(IDSSecurityEventProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<IDSSecurityEventProxy::ConstructionToken>
            IDSSecurityEventProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
