/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_SKELETON_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_SKELETON_H

#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_common.h"
#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_skeleton_fields.h"

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

        namespace idscansensor
        {

          namespace skeleton
          {

            namespace methods
            {
              using setCanSensorFeaturesElement0 = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::setCanSensorFeaturesElement0>;
              using undefineCanSensorFeaturesElement0 = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::undefineCanSensorFeaturesElement0>;
            } // namespace methods

            class IdsCanSensorSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<IdsCanSensor>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                fields::canSensorFeaturesElement0 canSensorFeaturesElement0;
                fields::periodicSignalElement0 periodicSignalElement0;

                methods::setCanSensorFeaturesElement0 setCanSensorFeaturesElement0;
                methods::undefineCanSensorFeaturesElement0 undefineCanSensorFeaturesElement0;

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

              explicit IdsCanSensorSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsCanSensorSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsCanSensorSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IdsCanSensorSkeleton(ConstructionToken&& token) noexcept;

              using setCanSensorFeaturesElement0Output = ::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::setCanSensorFeaturesElement0::Output;
              virtual ::ara::core::Future<setCanSensorFeaturesElement0Output>
              setCanSensorFeaturesElement0(::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesSet const& element) = 0;

              using undefineCanSensorFeaturesElement0Output = ::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::Output;
              virtual ::ara::core::Future<undefineCanSensorFeaturesElement0Output>
              undefineCanSensorFeaturesElement0(::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesUndefine const& element) = 0;

              fields::canSensorFeaturesElement0 canSensorFeaturesElement0;
              fields::periodicSignalElement0 periodicSignalElement0;

              methods::setCanSensorFeaturesElement0 m_setCanSensorFeaturesElement0;
              methods::undefineCanSensorFeaturesElement0 m_undefineCanSensorFeaturesElement0;

            };
          } // namespace skeleton
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
