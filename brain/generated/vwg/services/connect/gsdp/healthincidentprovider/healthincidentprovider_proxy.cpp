/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_proxy.h"
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
        template class Event<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Events::incident>;
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::configureIncidentEvent>;
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::getLastIncidents>;
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::requestIncidents>;
        template class Proxy<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider>;
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

      namespace gsdp
      {

        namespace healthincidentprovider
        {

          namespace proxy
          {
            HealthIncidentProviderProxy::HealthIncidentProviderProxy(HandleType const& handle)
            : Proxy<HealthIncidentProvider>{handle}
            , incident{port_link()}
            , configureIncidentEvent{port_link()}
            , getLastIncidents{port_link()}
            , requestIncidents{port_link()}
            , openIncidents{port_link()}
            {
            }

            HealthIncidentProviderProxy::~HealthIncidentProviderProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<HealthIncidentProvider>::close();
            }

            HealthIncidentProviderProxy::HealthIncidentProviderProxy(HealthIncidentProviderProxy&& /*other*/) noexcept = default;
            HealthIncidentProviderProxy& HealthIncidentProviderProxy::operator=(HealthIncidentProviderProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<HealthIncidentProviderProxy::ConstructionToken>
            HealthIncidentProviderProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
