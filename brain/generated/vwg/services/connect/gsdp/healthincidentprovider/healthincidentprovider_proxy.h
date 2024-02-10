/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_PROXY_H
#define INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_PROXY_H

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_common.h"
#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_proxy_fields.h"

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

      namespace gsdp
      {

        namespace healthincidentprovider
        {

          namespace proxy
          {

            namespace events
            {
              using incident = ::ac::com::cpp_binding::proxy::Event<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Events::incident>;
            } // namespace events

            namespace methods
            {
              using configureIncidentEvent = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::configureIncidentEvent>;
              using getLastIncidents = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::getLastIncidents>;
              using requestIncidents = ::ac::com::cpp_binding::proxy::Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::requestIncidents>;
            } // namespace methods

            class HealthIncidentProviderProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<HealthIncidentProvider>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<HealthIncidentProvider>::HandleType;

              using ConstructionToken = HealthIncidentProviderProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit HealthIncidentProviderProxy(HandleType const& handle);

              ~HealthIncidentProviderProxy() noexcept;

              HealthIncidentProviderProxy(HealthIncidentProviderProxy&& /*other*/) noexcept;
              HealthIncidentProviderProxy& operator=(HealthIncidentProviderProxy&& /*other*/) & noexcept;
              HealthIncidentProviderProxy(HealthIncidentProviderProxy const&) = delete;
              HealthIncidentProviderProxy& operator=(HealthIncidentProviderProxy const&) = delete;

              events::incident incident;
              methods::configureIncidentEvent configureIncidentEvent;
              methods::getLastIncidents getLastIncidents;
              methods::requestIncidents requestIncidents;
              fields::openIncidents openIncidents;
            };
          } // namespace proxy
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
