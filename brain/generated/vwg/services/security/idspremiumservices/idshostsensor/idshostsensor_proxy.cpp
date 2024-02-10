/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_proxy.h"
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
        template class Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::setHostSensorFeaturesElement0>;
        template class Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::undefineHostSensorFeaturesElement0>;
        template class Proxy<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor>;
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

        namespace idshostsensor
        {

          namespace proxy
          {
            IdsHostSensorProxy::IdsHostSensorProxy(HandleType const& handle)
            : Proxy<IdsHostSensor>{handle}
            , setHostSensorFeaturesElement0{port_link()}
            , undefineHostSensorFeaturesElement0{port_link()}
            , hostSensorFeaturesElement0{port_link()}
            , periodicSignalElement0{port_link()}
            {
            }

            IdsHostSensorProxy::~IdsHostSensorProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<IdsHostSensor>::close();
            }

            IdsHostSensorProxy::IdsHostSensorProxy(IdsHostSensorProxy&& /*other*/) noexcept = default;
            IdsHostSensorProxy& IdsHostSensorProxy::operator=(IdsHostSensorProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<IdsHostSensorProxy::ConstructionToken>
            IdsHostSensorProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
