/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/datacollector/odcagentgenericlarge/odcagentgenericlarge_proxy.h"
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
        template class Event<::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge::Events::data>;
        template class FireAndForgetMethod<::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge::Methods::control>;
        template class Proxy<::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge>;
      } // namespace proxy
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace datacollector
      {

        namespace odcagentgenericlarge
        {

          namespace proxy
          {
            OdcAgentGenericLargeProxy::OdcAgentGenericLargeProxy(HandleType const& handle)
            : Proxy<OdcAgentGenericLarge>{handle}
            , data{port_link()}
            , control{port_link()}
            {
            }

            OdcAgentGenericLargeProxy::~OdcAgentGenericLargeProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<OdcAgentGenericLarge>::close();
            }

            OdcAgentGenericLargeProxy::OdcAgentGenericLargeProxy(OdcAgentGenericLargeProxy&& /*other*/) noexcept = default;
            OdcAgentGenericLargeProxy& OdcAgentGenericLargeProxy::operator=(OdcAgentGenericLargeProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<OdcAgentGenericLargeProxy::ConstructionToken>
            OdcAgentGenericLargeProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace odcagentgenericlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
