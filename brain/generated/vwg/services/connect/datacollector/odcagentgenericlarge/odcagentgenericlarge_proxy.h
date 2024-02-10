/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_ODCAGENTGENERICLARGE_PROXY_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_ODCAGENTGENERICLARGE_PROXY_H

#include "vwg/services/connect/datacollector/odcagentgenericlarge/odcagentgenericlarge_common.h"

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

        namespace odcagentgenericlarge
        {

          namespace proxy
          {

            namespace events
            {
              using data = ::ac::com::cpp_binding::proxy::Event<::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge::Events::data>;
            } // namespace events

            namespace methods
            {
              using control = ::ac::com::cpp_binding::proxy::FireAndForgetMethod<::vwg::services::connect::datacollector::odcagentgenericlarge::OdcAgentGenericLarge::Methods::control>;
            } // namespace methods

            class OdcAgentGenericLargeProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<OdcAgentGenericLarge>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<OdcAgentGenericLarge>::HandleType;

              using ConstructionToken = OdcAgentGenericLargeProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit OdcAgentGenericLargeProxy(HandleType const& handle);

              ~OdcAgentGenericLargeProxy() noexcept;

              OdcAgentGenericLargeProxy(OdcAgentGenericLargeProxy&& /*other*/) noexcept;
              OdcAgentGenericLargeProxy& operator=(OdcAgentGenericLargeProxy&& /*other*/) & noexcept;
              OdcAgentGenericLargeProxy(OdcAgentGenericLargeProxy const&) = delete;
              OdcAgentGenericLargeProxy& operator=(OdcAgentGenericLargeProxy const&) = delete;

              events::data data;
              methods::control control;
            };
          } // namespace proxy
        } // namespace odcagentgenericlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
