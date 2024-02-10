/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_ODCAGENTGENERICHUGE_SKELETON_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_ODCAGENTGENERICHUGE_SKELETON_H

#include "vwg/services/connect/datacollector/odcagentgenerichuge/odcagentgenerichuge_common.h"

#include <memory>
#include "ac/com/cpp_binding/skeleton/event.hpp"
#include "ac/com/cpp_binding/skeleton/method.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton.hpp"
#include "ara/com/types.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace datacollector
      {

        namespace odcagentgenerichuge
        {

          namespace skeleton
          {
            namespace events
            {
              using data = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Events::data>;
            } // namespace events

            namespace methods
            {
              using control = ::ac::com::cpp_binding::skeleton::FireAndForgetMethod<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Methods::control>;
            } // namespace methods

            class OdcAgentGenericHugeSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<OdcAgentGenericHuge>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                events::data data;

                methods::control control;

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

              explicit OdcAgentGenericHugeSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit OdcAgentGenericHugeSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit OdcAgentGenericHugeSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit OdcAgentGenericHugeSkeleton(ConstructionToken&& token) noexcept;

              virtual void
              control(::vwg::services::connect::datacollector::odcagentgenerichuge::ControlInfo const& controlInfo) = 0;

              events::data data;

              methods::control m_control;

            };
          } // namespace skeleton
        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
