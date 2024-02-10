/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_SKELETON_H
#define INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_SKELETON_H

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_common.h"
#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_skeleton_fields.h"

#include <memory>
#include "ac/com/cpp_binding/skeleton/event.hpp"
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

    namespace connect
    {

      namespace gsdp
      {

        namespace healthincidentprovider
        {

          namespace skeleton
          {
            namespace events
            {
              using incident = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Events::incident>;
            } // namespace events

            namespace methods
            {
              using configureIncidentEvent = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::configureIncidentEvent>;
              using getLastIncidents = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::getLastIncidents>;
              using requestIncidents = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::requestIncidents>;
            } // namespace methods

            class HealthIncidentProviderSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<HealthIncidentProvider>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                events::incident incident;

                fields::openIncidents openIncidents;

                methods::configureIncidentEvent configureIncidentEvent;
                methods::getLastIncidents getLastIncidents;
                methods::requestIncidents requestIncidents;

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

              explicit HealthIncidentProviderSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit HealthIncidentProviderSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit HealthIncidentProviderSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit HealthIncidentProviderSkeleton(ConstructionToken&& token) noexcept;

              using configureIncidentEventOutput = ::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::configureIncidentEvent::Output;
              virtual ::ara::core::Future<configureIncidentEventOutput>
              configureIncidentEvent(::ara::stdtypes::String const& query) = 0;

              using getLastIncidentsOutput = ::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::getLastIncidents::Output;
              virtual ::ara::core::Future<getLastIncidentsOutput>
              getLastIncidents(::vwg::stdtypes::DT_uuid const& lastIncidentId) = 0;

              using requestIncidentsOutput = ::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Methods::requestIncidents::Output;
              virtual ::ara::core::Future<requestIncidentsOutput>
              requestIncidents(::ara::stdtypes::String const& query) = 0;

              events::incident incident;

              fields::openIncidents openIncidents;

              methods::configureIncidentEvent m_configureIncidentEvent;
              methods::getLastIncidents m_getLastIncidents;
              methods::requestIncidents m_requestIncidents;

            };
          } // namespace skeleton
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
