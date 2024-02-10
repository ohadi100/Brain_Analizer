/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_proxy.h"
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
        template class Event<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Events::event>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::addCampaign>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::estimateCampaign>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getCampaigns>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getData>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getInfo>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::removeCampaign>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::setData>;
        template class Proxy<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge>;
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

        namespace odcagentcommonlarge
        {

          namespace proxy
          {
            OdcAgentCommonLargeProxy::OdcAgentCommonLargeProxy(HandleType const& handle)
            : Proxy<OdcAgentCommonLarge>{handle}
            , event{port_link()}
            , addCampaign{port_link()}
            , estimateCampaign{port_link()}
            , getCampaigns{port_link()}
            , getData{port_link()}
            , getInfo{port_link()}
            , removeCampaign{port_link()}
            , setData{port_link()}
            {
            }

            OdcAgentCommonLargeProxy::~OdcAgentCommonLargeProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<OdcAgentCommonLarge>::close();
            }

            OdcAgentCommonLargeProxy::OdcAgentCommonLargeProxy(OdcAgentCommonLargeProxy&& /*other*/) noexcept = default;
            OdcAgentCommonLargeProxy& OdcAgentCommonLargeProxy::operator=(OdcAgentCommonLargeProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<OdcAgentCommonLargeProxy::ConstructionToken>
            OdcAgentCommonLargeProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
