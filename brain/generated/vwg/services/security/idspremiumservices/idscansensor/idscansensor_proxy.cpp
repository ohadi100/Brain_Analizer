/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_proxy.h"
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
        template class Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::setCanSensorFeaturesElement0>;
        template class Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::undefineCanSensorFeaturesElement0>;
        template class Proxy<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor>;
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

        namespace idscansensor
        {

          namespace proxy
          {
            IdsCanSensorProxy::IdsCanSensorProxy(HandleType const& handle)
            : Proxy<IdsCanSensor>{handle}
            , setCanSensorFeaturesElement0{port_link()}
            , undefineCanSensorFeaturesElement0{port_link()}
            , canSensorFeaturesElement0{port_link()}
            , periodicSignalElement0{port_link()}
            {
            }

            IdsCanSensorProxy::~IdsCanSensorProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<IdsCanSensor>::close();
            }

            IdsCanSensorProxy::IdsCanSensorProxy(IdsCanSensorProxy&& /*other*/) noexcept = default;
            IdsCanSensorProxy& IdsCanSensorProxy::operator=(IdsCanSensorProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<IdsCanSensorProxy::ConstructionToken>
            IdsCanSensorProxy::Preconstruct(HandleType const& handle) noexcept
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
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
