/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/datacollector/odcagentgenerichuge/odcagentgenerichuge_proxy.h"
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
        template class Event<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Events::data>;
        template class FireAndForgetMethod<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Methods::control>;
        template class Proxy<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge>;
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

        namespace odcagentgenerichuge
        {

          namespace proxy
          {
            OdcAgentGenericHugeProxy::OdcAgentGenericHugeProxy(HandleType const& handle)
            : Proxy<OdcAgentGenericHuge>{handle}
            , data{port_link()}
            , control{port_link()}
            {
            }

            OdcAgentGenericHugeProxy::~OdcAgentGenericHugeProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<OdcAgentGenericHuge>::close();
            }

            OdcAgentGenericHugeProxy::OdcAgentGenericHugeProxy(OdcAgentGenericHugeProxy&& /*other*/) noexcept = default;
            OdcAgentGenericHugeProxy& OdcAgentGenericHugeProxy::operator=(OdcAgentGenericHugeProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<OdcAgentGenericHugeProxy::ConstructionToken>
            OdcAgentGenericHugeProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
