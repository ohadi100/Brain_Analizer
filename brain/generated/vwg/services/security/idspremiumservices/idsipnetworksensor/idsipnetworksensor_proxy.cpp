/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_proxy.h"
#include <utility>
#include "ara/com/com_error_domain.h"
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
        template class Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0>;
        template class Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0>;
        template class Proxy<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor>;
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

      namespace idspremiumservices
      {

        namespace idsipnetworksensor
        {

          namespace proxy
          {
            IdsIpNetworkSensorProxy::IdsIpNetworkSensorProxy(HandleType const& handle)
            : Proxy<IdsIpNetworkSensor>{handle}
            , setEthernetSensorFeaturesElement0{port_link()}
            , undefineEthernetSensorFeaturesElement0{port_link()}
            , ethernetSensorFeaturesElement0{port_link()}
            , periodicSignalElement0{port_link()}
            {
            }

            IdsIpNetworkSensorProxy::~IdsIpNetworkSensorProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<IdsIpNetworkSensor>::close();
            }

            IdsIpNetworkSensorProxy::IdsIpNetworkSensorProxy(IdsIpNetworkSensorProxy&& /*other*/) noexcept = default;
            IdsIpNetworkSensorProxy& IdsIpNetworkSensorProxy::operator=(IdsIpNetworkSensorProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<IdsIpNetworkSensorProxy::ConstructionToken>
            IdsIpNetworkSensorProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
