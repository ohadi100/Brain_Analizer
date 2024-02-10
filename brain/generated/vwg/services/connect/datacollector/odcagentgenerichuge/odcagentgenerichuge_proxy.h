/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_ODCAGENTGENERICHUGE_PROXY_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_ODCAGENTGENERICHUGE_PROXY_H

#include "vwg/services/connect/datacollector/odcagentgenerichuge/odcagentgenerichuge_common.h"

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

        namespace odcagentgenerichuge
        {

          namespace proxy
          {

            namespace events
            {
              using data = ::ac::com::cpp_binding::proxy::Event<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Events::data>;
            } // namespace events

            namespace methods
            {
              using control = ::ac::com::cpp_binding::proxy::FireAndForgetMethod<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Methods::control>;
            } // namespace methods

            class OdcAgentGenericHugeProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<OdcAgentGenericHuge>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<OdcAgentGenericHuge>::HandleType;

              using ConstructionToken = OdcAgentGenericHugeProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit OdcAgentGenericHugeProxy(HandleType const& handle);

              ~OdcAgentGenericHugeProxy() noexcept;

              OdcAgentGenericHugeProxy(OdcAgentGenericHugeProxy&& /*other*/) noexcept;
              OdcAgentGenericHugeProxy& operator=(OdcAgentGenericHugeProxy&& /*other*/) & noexcept;
              OdcAgentGenericHugeProxy(OdcAgentGenericHugeProxy const&) = delete;
              OdcAgentGenericHugeProxy& operator=(OdcAgentGenericHugeProxy const&) = delete;

              events::data data;
              methods::control control;
            };
          } // namespace proxy
        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
