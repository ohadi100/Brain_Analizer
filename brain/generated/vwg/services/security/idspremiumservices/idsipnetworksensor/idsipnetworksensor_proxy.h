/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IDSIPNETWORKSENSOR_PROXY_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IDSIPNETWORKSENSOR_PROXY_H

#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_common.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_proxy_fields.h"

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

        namespace idsipnetworksensor
        {

          namespace proxy
          {

            namespace methods
            {
              using setEthernetSensorFeaturesElement0 = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0>;
              using undefineEthernetSensorFeaturesElement0 = ::ac::com::cpp_binding::proxy::Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0>;
            } // namespace methods

            class IdsIpNetworkSensorProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<IdsIpNetworkSensor>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<IdsIpNetworkSensor>::HandleType;

              using ConstructionToken = IdsIpNetworkSensorProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit IdsIpNetworkSensorProxy(HandleType const& handle);

              ~IdsIpNetworkSensorProxy() noexcept;

              IdsIpNetworkSensorProxy(IdsIpNetworkSensorProxy&& /*other*/) noexcept;
              IdsIpNetworkSensorProxy& operator=(IdsIpNetworkSensorProxy&& /*other*/) & noexcept;
              IdsIpNetworkSensorProxy(IdsIpNetworkSensorProxy const&) = delete;
              IdsIpNetworkSensorProxy& operator=(IdsIpNetworkSensorProxy const&) = delete;

              methods::setEthernetSensorFeaturesElement0 setEthernetSensorFeaturesElement0;
              methods::undefineEthernetSensorFeaturesElement0 undefineEthernetSensorFeaturesElement0;
              fields::ethernetSensorFeaturesElement0 ethernetSensorFeaturesElement0;
              fields::periodicSignalElement0 periodicSignalElement0;
            };
          } // namespace proxy
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
