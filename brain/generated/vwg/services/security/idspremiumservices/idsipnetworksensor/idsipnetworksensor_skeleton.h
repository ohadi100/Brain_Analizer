/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IDSIPNETWORKSENSOR_SKELETON_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IDSIPNETWORKSENSOR_SKELETON_H

#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_common.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_skeleton_fields.h"

#include <memory>
#include "ac/com/cpp_binding/skeleton/field.hpp"
#include "ac/com/cpp_binding/skeleton/method.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton.hpp"
#include "ara/com/types.h"
#include "ara/core/future.h"
#include "ara/core/instance_specifier.h"
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

          namespace skeleton
          {

            namespace methods
            {
              using setEthernetSensorFeaturesElement0 = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0>;
              using undefineEthernetSensorFeaturesElement0 = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0>;
            } // namespace methods

            class IdsIpNetworkSensorSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<IdsIpNetworkSensor>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                fields::ethernetSensorFeaturesElement0 ethernetSensorFeaturesElement0;
                fields::periodicSignalElement0 periodicSignalElement0;

                methods::setEthernetSensorFeaturesElement0 setEthernetSensorFeaturesElement0;
                methods::undefineEthernetSensorFeaturesElement0 undefineEthernetSensorFeaturesElement0;

                ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances, ::ara::com::MethodCallProcessingMode mode);
                ConstructionToken(::ara::com::InstanceIdentifier const& instance, ::ara::com::MethodCallProcessingMode mode);
                ConstructionToken(::ara::core::InstanceSpecifier instance, ::ara::com::MethodCallProcessingMode mode);
                ~ConstructionToken();
                ConstructionToken(ConstructionToken&& /*unused*/) noexcept;
                ConstructionToken& operator=(ConstructionToken&& /*unused*/) & noexcept;

                ConstructionToken(ConstructionToken const&) = delete;
                ConstructionToken& operator=(ConstructionToken const&) = delete;
              };

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::com::InstanceIdentifierContainer const& /*instances*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::com::InstanceIdentifier const& /*instance*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::core::InstanceSpecifier /*instance*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              explicit IdsIpNetworkSensorSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsIpNetworkSensorSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsIpNetworkSensorSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsIpNetworkSensorSkeleton(ConstructionToken&& token) noexcept;

              using setEthernetSensorFeaturesElement0Output = ::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::Output;
              virtual ::ara::core::Future<setEthernetSensorFeaturesElement0Output>
              setEthernetSensorFeaturesElement0(::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesSet const& element) = 0;

              using undefineEthernetSensorFeaturesElement0Output = ::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::Output;
              virtual ::ara::core::Future<undefineEthernetSensorFeaturesElement0Output>
              undefineEthernetSensorFeaturesElement0(::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesUndefine const& element) = 0;

              fields::ethernetSensorFeaturesElement0 ethernetSensorFeaturesElement0;
              fields::periodicSignalElement0 periodicSignalElement0;

              methods::setEthernetSensorFeaturesElement0 m_setEthernetSensorFeaturesElement0;
              methods::undefineEthernetSensorFeaturesElement0 m_undefineEthernetSensorFeaturesElement0;

            };
          } // namespace skeleton
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
