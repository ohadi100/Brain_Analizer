/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IDSHOSTSENSOR_SKELETON_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IDSHOSTSENSOR_SKELETON_H

#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_common.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_skeleton_fields.h"

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

        namespace idshostsensor
        {

          namespace skeleton
          {

            namespace methods
            {
              using setHostSensorFeaturesElement0 = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::setHostSensorFeaturesElement0>;
              using undefineHostSensorFeaturesElement0 = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::undefineHostSensorFeaturesElement0>;
            } // namespace methods

            class IdsHostSensorSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<IdsHostSensor>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                fields::hostSensorFeaturesElement0 hostSensorFeaturesElement0;
                fields::periodicSignalElement0 periodicSignalElement0;

                methods::setHostSensorFeaturesElement0 setHostSensorFeaturesElement0;
                methods::undefineHostSensorFeaturesElement0 undefineHostSensorFeaturesElement0;

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

              explicit IdsHostSensorSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsHostSensorSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsHostSensorSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsHostSensorSkeleton(ConstructionToken&& token) noexcept;

              using setHostSensorFeaturesElement0Output = ::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::setHostSensorFeaturesElement0::Output;
              virtual ::ara::core::Future<setHostSensorFeaturesElement0Output>
              setHostSensorFeaturesElement0(::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesSet const& element) = 0;

              using undefineHostSensorFeaturesElement0Output = ::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::Output;
              virtual ::ara::core::Future<undefineHostSensorFeaturesElement0Output>
              undefineHostSensorFeaturesElement0(::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesUndefine const& element) = 0;

              fields::hostSensorFeaturesElement0 hostSensorFeaturesElement0;
              fields::periodicSignalElement0 periodicSignalElement0;

              methods::setHostSensorFeaturesElement0 m_setHostSensorFeaturesElement0;
              methods::undefineHostSensorFeaturesElement0 m_undefineHostSensorFeaturesElement0;

            };
          } // namespace skeleton
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
