/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_skeleton.h"
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
        template class Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::setHostSensorFeaturesElement0>;
        template class Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Methods::undefineHostSensorFeaturesElement0>;
        template class Skeleton<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor>;
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

        namespace idshostsensor
        {

          namespace skeleton
          {
            IdsHostSensorSkeleton::IdsHostSensorSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , hostSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setHostSensorFeaturesElement0{method_dispatcher()}
            , m_undefineHostSensorFeaturesElement0{method_dispatcher()}
            {
              m_setHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesSet const& element) { return setHostSensorFeaturesElement0(element); });

              m_undefineHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesUndefine const& element) { return undefineHostSensorFeaturesElement0(element); });

            }

            IdsHostSensorSkeleton::IdsHostSensorSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , hostSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setHostSensorFeaturesElement0{method_dispatcher()}
            , m_undefineHostSensorFeaturesElement0{method_dispatcher()}
            {
              m_setHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesSet const& element) { return setHostSensorFeaturesElement0(element); });

              m_undefineHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesUndefine const& element) { return undefineHostSensorFeaturesElement0(element); });

            }

            IdsHostSensorSkeleton::IdsHostSensorSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , hostSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setHostSensorFeaturesElement0{method_dispatcher()}
            , m_undefineHostSensorFeaturesElement0{method_dispatcher()}
            {
              m_setHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesSet const& element) { return setHostSensorFeaturesElement0(element); });

              m_undefineHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesUndefine const& element) { return undefineHostSensorFeaturesElement0(element); });

            }

            IdsHostSensorSkeleton::IdsHostSensorSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , hostSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setHostSensorFeaturesElement0{std::move(token.setHostSensorFeaturesElement0)}
            , m_undefineHostSensorFeaturesElement0{std::move(token.undefineHostSensorFeaturesElement0)}
            {
              m_setHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesSet const& element) { return setHostSensorFeaturesElement0(element); });

              m_undefineHostSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idshostsensor::HostSensorFeaturesUndefine const& element) { return undefineHostSensorFeaturesElement0(element); });

            }

            ::ara::core::Result<IdsHostSensorSkeleton::ConstructionToken>
            IdsHostSensorSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
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

            ::ara::core::Result<IdsHostSensorSkeleton::ConstructionToken>
            IdsHostSensorSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
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

            ::ara::core::Result<IdsHostSensorSkeleton::ConstructionToken>
            IdsHostSensorSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
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

            IdsHostSensorSkeleton::ConstructionToken::~ConstructionToken() = default;
            IdsHostSensorSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            IdsHostSensorSkeleton::ConstructionToken& IdsHostSensorSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            IdsHostSensorSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , hostSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setHostSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineHostSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

            IdsHostSensorSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , hostSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setHostSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineHostSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

            IdsHostSensorSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , hostSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setHostSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineHostSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
