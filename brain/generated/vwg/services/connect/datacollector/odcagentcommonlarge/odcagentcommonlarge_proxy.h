/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_ODCAGENTCOMMONLARGE_PROXY_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_ODCAGENTCOMMONLARGE_PROXY_H

#include "vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_common.h"

#include "ac/com/cpp_binding/proxy/event.hpp"
#include "ac/com/cpp_binding/proxy/method.hpp"
#include "ac/com/cpp_binding/proxy/proxy.hpp"
#include "ara/core/result.h"
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

            namespace events
            {
              using event = ::ac::com::cpp_binding::proxy::Event<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Events::event>;
            } // namespace events

            namespace methods
            {
              using addCampaign = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::addCampaign>;
              using estimateCampaign = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::estimateCampaign>;
              using getCampaigns = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getCampaigns>;
              using getData = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getData>;
              using getInfo = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getInfo>;
              using removeCampaign = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::removeCampaign>;
              using setData = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::setData>;
            } // namespace methods

            class OdcAgentCommonLargeProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<OdcAgentCommonLarge>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<OdcAgentCommonLarge>::HandleType;

              using ConstructionToken = OdcAgentCommonLargeProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit OdcAgentCommonLargeProxy(HandleType const& handle);

              ~OdcAgentCommonLargeProxy() noexcept;

              OdcAgentCommonLargeProxy(OdcAgentCommonLargeProxy&& /*other*/) noexcept;
              OdcAgentCommonLargeProxy& operator=(OdcAgentCommonLargeProxy&& /*other*/) & noexcept;
              OdcAgentCommonLargeProxy(OdcAgentCommonLargeProxy const&) = delete;
              OdcAgentCommonLargeProxy& operator=(OdcAgentCommonLargeProxy const&) = delete;

              events::event event;
              methods::addCampaign addCampaign;
              methods::estimateCampaign estimateCampaign;
              methods::getCampaigns getCampaigns;
              methods::getData getData;
              methods::getInfo getInfo;
              methods::removeCampaign removeCampaign;
              methods::setData setData;
            };
          } // namespace proxy
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
