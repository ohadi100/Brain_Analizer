/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_PROXY_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_PROXY_H

#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_common.h"
#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_proxy_fields.h"

#include "ac/com/cpp_binding/proxy/method.hpp"
#include "ac/com/cpp_binding/proxy/proxy.hpp"
#include "ara/core/result.h"
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

            namespace methods
            {
              using setCanSensorFeaturesElement0 = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::setCanSensorFeaturesElement0>;
              using undefineCanSensorFeaturesElement0 = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::undefineCanSensorFeaturesElement0>;
            } // namespace methods

            class IdsCanSensorProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<IdsCanSensor>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<IdsCanSensor>::HandleType;

              using ConstructionToken = IdsCanSensorProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit IdsCanSensorProxy(HandleType const& handle);

              ~IdsCanSensorProxy() noexcept;

              IdsCanSensorProxy(IdsCanSensorProxy&& /*other*/) noexcept;
              IdsCanSensorProxy& operator=(IdsCanSensorProxy&& /*other*/) & noexcept;
              IdsCanSensorProxy(IdsCanSensorProxy const&) = delete;
              IdsCanSensorProxy& operator=(IdsCanSensorProxy const&) = delete;

              methods::setCanSensorFeaturesElement0 setCanSensorFeaturesElement0;
              methods::undefineCanSensorFeaturesElement0 undefineCanSensorFeaturesElement0;
              fields::canSensorFeaturesElement0 canSensorFeaturesElement0;
              fields::periodicSignalElement0 periodicSignalElement0;
            };
          } // namespace proxy
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
