/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_skeleton.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/skeleton/method_defs.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace skeleton
      {
        template class Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::setCanSensorFeaturesElement0>;
        template class Method<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Methods::undefineCanSensorFeaturesElement0>;
        template class Skeleton<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor>;
      } // namespace skeleton
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

          namespace skeleton
          {
            IdsCanSensorSkeleton::IdsCanSensorSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , canSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setCanSensorFeaturesElement0{method_dispatcher()}
            , m_undefineCanSensorFeaturesElement0{method_dispatcher()}
            {
              m_setCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesSet const& element) { return setCanSensorFeaturesElement0(element); });

              m_undefineCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesUndefine const& element) { return undefineCanSensorFeaturesElement0(element); });

            }

            IdsCanSensorSkeleton::IdsCanSensorSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , canSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setCanSensorFeaturesElement0{method_dispatcher()}
            , m_undefineCanSensorFeaturesElement0{method_dispatcher()}
            {
              m_setCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesSet const& element) { return setCanSensorFeaturesElement0(element); });

              m_undefineCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesUndefine const& element) { return undefineCanSensorFeaturesElement0(element); });

            }

            IdsCanSensorSkeleton::IdsCanSensorSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , canSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setCanSensorFeaturesElement0{method_dispatcher()}
            , m_undefineCanSensorFeaturesElement0{method_dispatcher()}
            {
              m_setCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesSet const& element) { return setCanSensorFeaturesElement0(element); });

              m_undefineCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesUndefine const& element) { return undefineCanSensorFeaturesElement0(element); });

            }

            IdsCanSensorSkeleton::IdsCanSensorSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , canSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setCanSensorFeaturesElement0{std::move(token.setCanSensorFeaturesElement0)}
            , m_undefineCanSensorFeaturesElement0{std::move(token.undefineCanSensorFeaturesElement0)}
            {
              m_setCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesSet const& element) { return setCanSensorFeaturesElement0(element); });

              m_undefineCanSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesUndefine const& element) { return undefineCanSensorFeaturesElement0(element); });

            }

            ::ara::core::Result<IdsCanSensorSkeleton::ConstructionToken>
            IdsCanSensorSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instance, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            ::ara::core::Result<IdsCanSensorSkeleton::ConstructionToken>
            IdsCanSensorSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instance, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            ::ara::core::Result<IdsCanSensorSkeleton::ConstructionToken>
            IdsCanSensorSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instances, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            IdsCanSensorSkeleton::ConstructionToken::~ConstructionToken() = default;
            IdsCanSensorSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            IdsCanSensorSkeleton::ConstructionToken& IdsCanSensorSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            IdsCanSensorSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , canSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setCanSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineCanSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

            IdsCanSensorSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , canSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setCanSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineCanSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

            IdsCanSensorSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , canSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setCanSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineCanSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
