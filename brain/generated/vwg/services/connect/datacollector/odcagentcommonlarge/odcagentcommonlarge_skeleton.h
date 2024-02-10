/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_ODCAGENTCOMMONLARGE_SKELETON_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_ODCAGENTCOMMONLARGE_SKELETON_H

#include "vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_common.h"

#include <memory>
#include "ac/com/cpp_binding/skeleton/event.hpp"
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

      namespace datacollector
      {

        namespace odcagentcommonlarge
        {

          namespace skeleton
          {
            namespace events
            {
              using event = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Events::event>;
            } // namespace events

            namespace methods
            {
              using addCampaign = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::addCampaign>;
              using estimateCampaign = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::estimateCampaign>;
              using getCampaigns = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getCampaigns>;
              using getData = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getData>;
              using getInfo = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getInfo>;
              using removeCampaign = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::removeCampaign>;
              using setData = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::setData>;
            } // namespace methods

            class OdcAgentCommonLargeSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<OdcAgentCommonLarge>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                events::event event;

                methods::addCampaign addCampaign;
                methods::estimateCampaign estimateCampaign;
                methods::getCampaigns getCampaigns;
                methods::getData getData;
                methods::getInfo getInfo;
                methods::removeCampaign removeCampaign;
                methods::setData setData;

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

              explicit OdcAgentCommonLargeSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit OdcAgentCommonLargeSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit OdcAgentCommonLargeSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit OdcAgentCommonLargeSkeleton(ConstructionToken&& token) noexcept;

              using addCampaignOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::addCampaign::Output;
              virtual ::ara::core::Future<addCampaignOutput>
              addCampaign(::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const& request) = 0;

              using estimateCampaignOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::estimateCampaign::Output;
              virtual ::ara::core::Future<estimateCampaignOutput>
              estimateCampaign(::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const& campaign) = 0;

              using getCampaignsOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getCampaigns::Output;
              virtual ::ara::core::Future<getCampaignsOutput>
              getCampaigns() = 0;

              using getDataOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getData::Output;
              virtual ::ara::core::Future<getDataOutput>
              getData(::ara::stdtypes::String const& resource) = 0;

              using getInfoOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::getInfo::Output;
              virtual ::ara::core::Future<getInfoOutput>
              getInfo() = 0;

              using removeCampaignOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::removeCampaign::Output;
              virtual ::ara::core::Future<removeCampaignOutput>
              removeCampaign(::ara::stdtypes::String const& uuid) = 0;

              using setDataOutput = ::vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge::Methods::setData::Output;
              virtual ::ara::core::Future<setDataOutput>
              setData(::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const& request) = 0;

              events::event event;

              methods::addCampaign m_addCampaign;
              methods::estimateCampaign m_estimateCampaign;
              methods::getCampaigns m_getCampaigns;
              methods::getData m_getData;
              methods::getInfo m_getInfo;
              methods::removeCampaign m_removeCampaign;
              methods::setData m_setData;

            };
          } // namespace skeleton
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
