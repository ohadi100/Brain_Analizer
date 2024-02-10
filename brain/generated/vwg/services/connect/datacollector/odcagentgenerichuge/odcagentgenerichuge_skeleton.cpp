/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/connect/datacollector/odcagentgenerichuge/odcagentgenerichuge_skeleton.h"
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
        template class Event<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Events::data>;
        template class FireAndForgetMethod<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge::Methods::control>;
        template class Skeleton<::vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge>;
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

      namespace datacollector
      {

        namespace odcagentgenerichuge
        {

          namespace skeleton
          {
            OdcAgentGenericHugeSkeleton::OdcAgentGenericHugeSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , data{port_link()}
            , m_control{method_dispatcher()}
            {
              m_control.set_function(
              [this](::vwg::services::connect::datacollector::odcagentgenerichuge::ControlInfo const& controlInfo) { return control(controlInfo); });

            }

            OdcAgentGenericHugeSkeleton::OdcAgentGenericHugeSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , data{port_link()}
            , m_control{method_dispatcher()}
            {
              m_control.set_function(
              [this](::vwg::services::connect::datacollector::odcagentgenerichuge::ControlInfo const& controlInfo) { return control(controlInfo); });

            }

            OdcAgentGenericHugeSkeleton::OdcAgentGenericHugeSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , data{port_link()}
            , m_control{method_dispatcher()}
            {
              m_control.set_function(
              [this](::vwg::services::connect::datacollector::odcagentgenerichuge::ControlInfo const& controlInfo) { return control(controlInfo); });

            }

            OdcAgentGenericHugeSkeleton::OdcAgentGenericHugeSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , data{std::move(token.data)}
            , m_control{std::move(token.control)}
            {
              m_control.set_function(
              [this](::vwg::services::connect::datacollector::odcagentgenerichuge::ControlInfo const& controlInfo) { return control(controlInfo); });

            }

            ::ara::core::Result<OdcAgentGenericHugeSkeleton::ConstructionToken>
            OdcAgentGenericHugeSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
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

            ::ara::core::Result<OdcAgentGenericHugeSkeleton::ConstructionToken>
            OdcAgentGenericHugeSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
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

            ::ara::core::Result<OdcAgentGenericHugeSkeleton::ConstructionToken>
            OdcAgentGenericHugeSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
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

            OdcAgentGenericHugeSkeleton::ConstructionToken::~ConstructionToken() = default;
            OdcAgentGenericHugeSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            OdcAgentGenericHugeSkeleton::ConstructionToken& OdcAgentGenericHugeSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            OdcAgentGenericHugeSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , data{skeleton_impl->port_link()}
            , control{skeleton_impl->method_dispatcher()}
            {
            }

            OdcAgentGenericHugeSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , data{skeleton_impl->port_link()}
            , control{skeleton_impl->method_dispatcher()}
            {
            }

            OdcAgentGenericHugeSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , data{skeleton_impl->port_link()}
            , control{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
