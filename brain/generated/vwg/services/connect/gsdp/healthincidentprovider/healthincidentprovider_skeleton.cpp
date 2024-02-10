/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_skeleton.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/skeleton/event_defs.hpp"
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
        template class Event<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Events::incident>;
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::configureIncidentEvent>;
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::getLastIncidents>;
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::requestIncidents>;
        template class Skeleton<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider>;
      } // namespace skeleton
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace gsdp
      {

        namespace healthincidentprovider
        {

          namespace skeleton
          {
            HealthIncidentProviderSkeleton::HealthIncidentProviderSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , incident{port_link()}
            , openIncidents{method_dispatcher(), field_validator()}
            , m_configureIncidentEvent{method_dispatcher()}
            , m_getLastIncidents{method_dispatcher()}
            , m_requestIncidents{method_dispatcher()}
            {
              m_configureIncidentEvent.set_function(
              [this](::ara::stdtypes::String const& query) { return configureIncidentEvent(query); });

              m_getLastIncidents.set_function(
              [this](::vwg::stdtypes::DT_uuid const& lastIncidentId) { return getLastIncidents(lastIncidentId); });

              m_requestIncidents.set_function(
              [this](::ara::stdtypes::String const& query) { return requestIncidents(query); });

            }

            HealthIncidentProviderSkeleton::HealthIncidentProviderSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , incident{port_link()}
            , openIncidents{method_dispatcher(), field_validator()}
            , m_configureIncidentEvent{method_dispatcher()}
            , m_getLastIncidents{method_dispatcher()}
            , m_requestIncidents{method_dispatcher()}
            {
              m_configureIncidentEvent.set_function(
              [this](::ara::stdtypes::String const& query) { return configureIncidentEvent(query); });

              m_getLastIncidents.set_function(
              [this](::vwg::stdtypes::DT_uuid const& lastIncidentId) { return getLastIncidents(lastIncidentId); });

              m_requestIncidents.set_function(
              [this](::ara::stdtypes::String const& query) { return requestIncidents(query); });

            }

            HealthIncidentProviderSkeleton::HealthIncidentProviderSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , incident{port_link()}
            , openIncidents{method_dispatcher(), field_validator()}
            , m_configureIncidentEvent{method_dispatcher()}
            , m_getLastIncidents{method_dispatcher()}
            , m_requestIncidents{method_dispatcher()}
            {
              m_configureIncidentEvent.set_function(
              [this](::ara::stdtypes::String const& query) { return configureIncidentEvent(query); });

              m_getLastIncidents.set_function(
              [this](::vwg::stdtypes::DT_uuid const& lastIncidentId) { return getLastIncidents(lastIncidentId); });

              m_requestIncidents.set_function(
              [this](::ara::stdtypes::String const& query) { return requestIncidents(query); });

            }

            HealthIncidentProviderSkeleton::HealthIncidentProviderSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , incident{std::move(token.incident)}
            , openIncidents{method_dispatcher(), field_validator()}
            , m_configureIncidentEvent{std::move(token.configureIncidentEvent)}
            , m_getLastIncidents{std::move(token.getLastIncidents)}
            , m_requestIncidents{std::move(token.requestIncidents)}
            {
              m_configureIncidentEvent.set_function(
              [this](::ara::stdtypes::String const& query) { return configureIncidentEvent(query); });

              m_getLastIncidents.set_function(
              [this](::vwg::stdtypes::DT_uuid const& lastIncidentId) { return getLastIncidents(lastIncidentId); });

              m_requestIncidents.set_function(
              [this](::ara::stdtypes::String const& query) { return requestIncidents(query); });

            }

            ::ara::core::Result<HealthIncidentProviderSkeleton::ConstructionToken>
            HealthIncidentProviderSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
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

            ::ara::core::Result<HealthIncidentProviderSkeleton::ConstructionToken>
            HealthIncidentProviderSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
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

            ::ara::core::Result<HealthIncidentProviderSkeleton::ConstructionToken>
            HealthIncidentProviderSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
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

            HealthIncidentProviderSkeleton::ConstructionToken::~ConstructionToken() = default;
            HealthIncidentProviderSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            HealthIncidentProviderSkeleton::ConstructionToken& HealthIncidentProviderSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            HealthIncidentProviderSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , incident{skeleton_impl->port_link()}
            , openIncidents{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , configureIncidentEvent{skeleton_impl->method_dispatcher()}
            , getLastIncidents{skeleton_impl->method_dispatcher()}
            , requestIncidents{skeleton_impl->method_dispatcher()}
            {
            }

            HealthIncidentProviderSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , incident{skeleton_impl->port_link()}
            , openIncidents{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , configureIncidentEvent{skeleton_impl->method_dispatcher()}
            , getLastIncidents{skeleton_impl->method_dispatcher()}
            , requestIncidents{skeleton_impl->method_dispatcher()}
            {
            }

            HealthIncidentProviderSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , incident{skeleton_impl->port_link()}
            , openIncidents{skeleton_impl->method_dispatcher(), skeleton_impl->field_validator()}
            , configureIncidentEvent{skeleton_impl->method_dispatcher()}
            , getLastIncidents{skeleton_impl->method_dispatcher()}
            , requestIncidents{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
