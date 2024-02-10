/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_skeleton.h"
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
        template class Event<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Events::event>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::addCampaign>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::estimateCampaign>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getCampaigns>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getData>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getInfo>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::removeCampaign>;
        template class Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::setData>;
        template class Skeleton<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge>;
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

        namespace odcagentcommonlarge
        {

          namespace skeleton
          {
            OdcAgentCommonLargeSkeleton::OdcAgentCommonLargeSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , event{port_link()}
            , m_addCampaign{method_dispatcher()}
            , m_estimateCampaign{method_dispatcher()}
            , m_getCampaigns{method_dispatcher()}
            , m_getData{method_dispatcher()}
            , m_getInfo{method_dispatcher()}
            , m_removeCampaign{method_dispatcher()}
            , m_setData{method_dispatcher()}
            {
              m_addCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const& request) { return addCampaign(request); });

              m_estimateCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const& campaign) { return estimateCampaign(campaign); });

              m_getCampaigns.set_function(
              [this]() { return getCampaigns(); });

              m_getData.set_function(
              [this](::ara::stdtypes::String const& resource) { return getData(resource); });

              m_getInfo.set_function(
              [this]() { return getInfo(); });

              m_removeCampaign.set_function(
              [this](::ara::stdtypes::String const& uuid) { return removeCampaign(uuid); });

              m_setData.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const& request) { return setData(request); });

            }

            OdcAgentCommonLargeSkeleton::OdcAgentCommonLargeSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , event{port_link()}
            , m_addCampaign{method_dispatcher()}
            , m_estimateCampaign{method_dispatcher()}
            , m_getCampaigns{method_dispatcher()}
            , m_getData{method_dispatcher()}
            , m_getInfo{method_dispatcher()}
            , m_removeCampaign{method_dispatcher()}
            , m_setData{method_dispatcher()}
            {
              m_addCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const& request) { return addCampaign(request); });

              m_estimateCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const& campaign) { return estimateCampaign(campaign); });

              m_getCampaigns.set_function(
              [this]() { return getCampaigns(); });

              m_getData.set_function(
              [this](::ara::stdtypes::String const& resource) { return getData(resource); });

              m_getInfo.set_function(
              [this]() { return getInfo(); });

              m_removeCampaign.set_function(
              [this](::ara::stdtypes::String const& uuid) { return removeCampaign(uuid); });

              m_setData.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const& request) { return setData(request); });

            }

            OdcAgentCommonLargeSkeleton::OdcAgentCommonLargeSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , event{port_link()}
            , m_addCampaign{method_dispatcher()}
            , m_estimateCampaign{method_dispatcher()}
            , m_getCampaigns{method_dispatcher()}
            , m_getData{method_dispatcher()}
            , m_getInfo{method_dispatcher()}
            , m_removeCampaign{method_dispatcher()}
            , m_setData{method_dispatcher()}
            {
              m_addCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const& request) { return addCampaign(request); });

              m_estimateCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const& campaign) { return estimateCampaign(campaign); });

              m_getCampaigns.set_function(
              [this]() { return getCampaigns(); });

              m_getData.set_function(
              [this](::ara::stdtypes::String const& resource) { return getData(resource); });

              m_getInfo.set_function(
              [this]() { return getInfo(); });

              m_removeCampaign.set_function(
              [this](::ara::stdtypes::String const& uuid) { return removeCampaign(uuid); });

              m_setData.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const& request) { return setData(request); });

            }

            OdcAgentCommonLargeSkeleton::OdcAgentCommonLargeSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , event{std::move(token.event)}
            , m_addCampaign{std::move(token.addCampaign)}
            , m_estimateCampaign{std::move(token.estimateCampaign)}
            , m_getCampaigns{std::move(token.getCampaigns)}
            , m_getData{std::move(token.getData)}
            , m_getInfo{std::move(token.getInfo)}
            , m_removeCampaign{std::move(token.removeCampaign)}
            , m_setData{std::move(token.setData)}
            {
              m_addCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const& request) { return addCampaign(request); });

              m_estimateCampaign.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const& campaign) { return estimateCampaign(campaign); });

              m_getCampaigns.set_function(
              [this]() { return getCampaigns(); });

              m_getData.set_function(
              [this](::ara::stdtypes::String const& resource) { return getData(resource); });

              m_getInfo.set_function(
              [this]() { return getInfo(); });

              m_removeCampaign.set_function(
              [this](::ara::stdtypes::String const& uuid) { return removeCampaign(uuid); });

              m_setData.set_function(
              [this](::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const& request) { return setData(request); });

            }

            ::ara::core::Result<OdcAgentCommonLargeSkeleton::ConstructionToken>
            OdcAgentCommonLargeSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
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

            ::ara::core::Result<OdcAgentCommonLargeSkeleton::ConstructionToken>
            OdcAgentCommonLargeSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
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

            ::ara::core::Result<OdcAgentCommonLargeSkeleton::ConstructionToken>
            OdcAgentCommonLargeSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
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

            OdcAgentCommonLargeSkeleton::ConstructionToken::~ConstructionToken() = default;
            OdcAgentCommonLargeSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            OdcAgentCommonLargeSkeleton::ConstructionToken& OdcAgentCommonLargeSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            OdcAgentCommonLargeSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , event{skeleton_impl->port_link()}
            , addCampaign{skeleton_impl->method_dispatcher()}
            , estimateCampaign{skeleton_impl->method_dispatcher()}
            , getCampaigns{skeleton_impl->method_dispatcher()}
            , getData{skeleton_impl->method_dispatcher()}
            , getInfo{skeleton_impl->method_dispatcher()}
            , removeCampaign{skeleton_impl->method_dispatcher()}
            , setData{skeleton_impl->method_dispatcher()}
            {
            }

            OdcAgentCommonLargeSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , event{skeleton_impl->port_link()}
            , addCampaign{skeleton_impl->method_dispatcher()}
            , estimateCampaign{skeleton_impl->method_dispatcher()}
            , getCampaigns{skeleton_impl->method_dispatcher()}
            , getData{skeleton_impl->method_dispatcher()}
            , getInfo{skeleton_impl->method_dispatcher()}
            , removeCampaign{skeleton_impl->method_dispatcher()}
            , setData{skeleton_impl->method_dispatcher()}
            {
            }

            OdcAgentCommonLargeSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , event{skeleton_impl->port_link()}
            , addCampaign{skeleton_impl->method_dispatcher()}
            , estimateCampaign{skeleton_impl->method_dispatcher()}
            , getCampaigns{skeleton_impl->method_dispatcher()}
            , getData{skeleton_impl->method_dispatcher()}
            , getInfo{skeleton_impl->method_dispatcher()}
            , removeCampaign{skeleton_impl->method_dispatcher()}
            , setData{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
