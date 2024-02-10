/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_skeleton.h"
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
        template class Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0>;
        template class Method<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0>;
        template class Skeleton<::vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor>;
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

        namespace idsipnetworksensor
        {

          namespace skeleton
          {
            IdsIpNetworkSensorSkeleton::IdsIpNetworkSensorSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , ethernetSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setEthernetSensorFeaturesElement0{method_dispatcher()}
            , m_undefineEthernetSensorFeaturesElement0{method_dispatcher()}
            {
              m_setEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesSet const& element) { return setEthernetSensorFeaturesElement0(element); });

              m_undefineEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesUndefine const& element) { return undefineEthernetSensorFeaturesElement0(element); });

            }

            IdsIpNetworkSensorSkeleton::IdsIpNetworkSensorSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , ethernetSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setEthernetSensorFeaturesElement0{method_dispatcher()}
            , m_undefineEthernetSensorFeaturesElement0{method_dispatcher()}
            {
              m_setEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesSet const& element) { return setEthernetSensorFeaturesElement0(element); });

              m_undefineEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesUndefine const& element) { return undefineEthernetSensorFeaturesElement0(element); });

            }

            IdsIpNetworkSensorSkeleton::IdsIpNetworkSensorSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , ethernetSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setEthernetSensorFeaturesElement0{method_dispatcher()}
            , m_undefineEthernetSensorFeaturesElement0{method_dispatcher()}
            {
              m_setEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesSet const& element) { return setEthernetSensorFeaturesElement0(element); });

              m_undefineEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesUndefine const& element) { return undefineEthernetSensorFeaturesElement0(element); });

            }

            IdsIpNetworkSensorSkeleton::IdsIpNetworkSensorSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , ethernetSensorFeaturesElement0{method_dispatcher(), field_validator()}
            , periodicSignalElement0{method_dispatcher(), field_validator()}
            , m_setEthernetSensorFeaturesElement0{std::move(token.setEthernetSensorFeaturesElement0)}
            , m_undefineEthernetSensorFeaturesElement0{std::move(token.undefineEthernetSensorFeaturesElement0)}
            {
              m_setEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesSet const& element) { return setEthernetSensorFeaturesElement0(element); });

              m_undefineEthernetSensorFeaturesElement0.set_function(
              [this](::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesUndefine const& element) { return undefineEthernetSensorFeaturesElement0(element); });

            }

            ::ara::core::Result<IdsIpNetworkSensorSkeleton::ConstructionToken>
            IdsIpNetworkSensorSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
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

            ::ara::core::Result<IdsIpNetworkSensorSkeleton::ConstructionToken>
            IdsIpNetworkSensorSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
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

            ::ara::core::Result<IdsIpNetworkSensorSkeleton::ConstructionToken>
            IdsIpNetworkSensorSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
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

            IdsIpNetworkSensorSkeleton::ConstructionToken::~ConstructionToken() = default;
            IdsIpNetworkSensorSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            IdsIpNetworkSensorSkeleton::ConstructionToken& IdsIpNetworkSensorSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            IdsIpNetworkSensorSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , ethernetSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setEthernetSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineEthernetSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

            IdsIpNetworkSensorSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , ethernetSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setEthernetSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineEthernetSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

            IdsIpNetworkSensorSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , ethernetSensorFeaturesElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , periodicSignalElement0{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , setEthernetSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            , undefineEthernetSensorFeaturesElement0{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
