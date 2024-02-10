/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IDSHOSTSENSOR_PROXY_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IDSHOSTSENSOR_PROXY_H

#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_common.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_proxy_fields.h"

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

        namespace idshostsensor
        {

          namespace proxy
          {

            namespace methods
            {
              using setHostSensorFeaturesElement0 = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::setHostSensorFeaturesElement0>;
              using undefineHostSensorFeaturesElement0 = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::undefineHostSensorFeaturesElement0>;
            } // namespace methods

            class IdsHostSensorProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<IdsHostSensor>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<IdsHostSensor>::HandleType;

              using ConstructionToken = IdsHostSensorProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit IdsHostSensorProxy(HandleType const& handle);

              ~IdsHostSensorProxy() noexcept;

              IdsHostSensorProxy(IdsHostSensorProxy&& /*other*/) noexcept;
              IdsHostSensorProxy& operator=(IdsHostSensorProxy&& /*other*/) & noexcept;
              IdsHostSensorProxy(IdsHostSensorProxy const&) = delete;
              IdsHostSensorProxy& operator=(IdsHostSensorProxy const&) = delete;

              methods::setHostSensorFeaturesElement0 setHostSensorFeaturesElement0;
              methods::undefineHostSensorFeaturesElement0 undefineHostSensorFeaturesElement0;
              fields::hostSensorFeaturesElement0 hostSensorFeaturesElement0;
              fields::periodicSignalElement0 periodicSignalElement0;
            };
          } // namespace proxy
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
