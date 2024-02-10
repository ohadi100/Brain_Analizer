/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_DIAGDATA_SKELETON_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_DIAGDATA_SKELETON_H

#include "vwg/services/diagnostic/diagdata/diagdata/diagdata_common.h"

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

    namespace diagnostic
    {

      namespace diagdata
      {

        namespace diagdata
        {

          namespace skeleton
          {
            namespace events
            {
              using assemblyStatusReady = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::assemblyStatusReady>;
              using assemblyStatusUpdate = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::assemblyStatusUpdate>;
              using responseReady = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::responseReady>;
              using sendDiagControlCommandResponse = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::sendDiagControlCommandResponse>;
              using updateAvailable = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::updateAvailable>;
            } // namespace events

            namespace methods
            {
              using cancelRequest = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::cancelRequest>;
              using getDiagAssemblyStatus = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatus>;
              using getDiagAssemblyStatusHash = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatusHash>;
              using getDiagDataByGroups = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByGroups>;
              using getDiagDataByKeys = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys>;
              using readRequestedResults = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::readRequestedResults>;
              using refreshAssemblyStatus = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::refreshAssemblyStatus>;
              using requestDiagAssemblyStatusOnChange = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagAssemblyStatusOnChange>;
              using requestDiagDataByGroups = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByGroups>;
              using requestDiagDataByKeys = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByKeys>;
              using requestDiagDataOnChange = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnChange>;
              using requestDiagDataOnThreshold = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnThreshold>;
              using requestSampledDiagData = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSampledDiagData>;
              using requestSetDiagData = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSetDiagData>;
              using sendDiagControlCommandRequest = ::ac::com::cpp_binding::skeleton::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::sendDiagControlCommandRequest>;
            } // namespace methods

            class DiagDataSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<DiagData>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                events::assemblyStatusReady assemblyStatusReady;
                events::assemblyStatusUpdate assemblyStatusUpdate;
                events::responseReady responseReady;
                events::sendDiagControlCommandResponse sendDiagControlCommandResponse;
                events::updateAvailable updateAvailable;

                methods::cancelRequest cancelRequest;
                methods::getDiagAssemblyStatus getDiagAssemblyStatus;
                methods::getDiagAssemblyStatusHash getDiagAssemblyStatusHash;
                methods::getDiagDataByGroups getDiagDataByGroups;
                methods::getDiagDataByKeys getDiagDataByKeys;
                methods::readRequestedResults readRequestedResults;
                methods::refreshAssemblyStatus refreshAssemblyStatus;
                methods::requestDiagAssemblyStatusOnChange requestDiagAssemblyStatusOnChange;
                methods::requestDiagDataByGroups requestDiagDataByGroups;
                methods::requestDiagDataByKeys requestDiagDataByKeys;
                methods::requestDiagDataOnChange requestDiagDataOnChange;
                methods::requestDiagDataOnThreshold requestDiagDataOnThreshold;
                methods::requestSampledDiagData requestSampledDiagData;
                methods::requestSetDiagData requestSetDiagData;
                methods::sendDiagControlCommandRequest sendDiagControlCommandRequest;

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

              explicit DiagDataSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit DiagDataSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit DiagDataSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit DiagDataSkeleton(ConstructionToken&& token) noexcept;

              using cancelRequestOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::cancelRequest::Output;
              virtual ::ara::core::Future<cancelRequestOutput>
              cancelRequest(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) = 0;

              using getDiagAssemblyStatusOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatus::Output;
              virtual ::ara::core::Future<getDiagAssemblyStatusOutput>
              getDiagAssemblyStatus(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) = 0;

              using getDiagAssemblyStatusHashOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatusHash::Output;
              virtual ::ara::core::Future<getDiagAssemblyStatusHashOutput>
              getDiagAssemblyStatusHash(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) = 0;

              using getDiagDataByGroupsOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByGroups::Output;
              virtual ::ara::core::Future<getDiagDataByGroupsOutput>
              getDiagDataByGroups(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 timeout) = 0;

              using getDiagDataByKeysOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys::Output;
              virtual ::ara::core::Future<getDiagDataByKeysOutput>
              getDiagDataByKeys(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 timeout) = 0;

              using readRequestedResultsOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::readRequestedResults::Output;
              virtual ::ara::core::Future<readRequestedResultsOutput>
              readRequestedResults(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) = 0;

              using refreshAssemblyStatusOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::refreshAssemblyStatus::Output;
              virtual ::ara::core::Future<refreshAssemblyStatusOutput>
              refreshAssemblyStatus(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::refreshAssemblyStatus_diagNodes const& diagNodes) = 0;

              using requestDiagAssemblyStatusOnChangeOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagAssemblyStatusOnChange::Output;
              virtual ::ara::core::Future<requestDiagAssemblyStatusOnChangeOutput>
              requestDiagAssemblyStatusOnChange(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) = 0;

              using requestDiagDataByGroupsOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByGroups::Output;
              virtual ::ara::core::Future<requestDiagDataByGroupsOutput>
              requestDiagDataByGroups(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) = 0;

              using requestDiagDataByKeysOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByKeys::Output;
              virtual ::ara::core::Future<requestDiagDataByKeysOutput>
              requestDiagDataByKeys(::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) = 0;

              using requestDiagDataOnChangeOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnChange::Output;
              virtual ::ara::core::Future<requestDiagDataOnChangeOutput>
              requestDiagDataOnChange(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 minDeltaTriggerTime, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) = 0;

              using requestDiagDataOnThresholdOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnThreshold::Output;
              virtual ::ara::core::Future<requestDiagDataOnThresholdOutput>
              requestDiagDataOnThreshold(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 minDeltaTriggerTime, ::ara::stdtypes::Int64 upperThreshold, ::ara::stdtypes::Int64 lowerThreshold, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) = 0;

              using requestSampledDiagDataOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSampledDiagData::Output;
              virtual ::ara::core::Future<requestSampledDiagDataOutput>
              requestSampledDiagData(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 minDeltaTriggerTime, ::ara::stdtypes::UInt32 measurementPeriod, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) = 0;

              using requestSetDiagDataOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSetDiagData::Output;
              virtual ::ara::core::Future<requestSetDiagDataOutput>
              requestSetDiagData(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataItems, ::vwg::services::diagnostic::diagdata::diagdata::SetOptions const& setOptions) = 0;

              using sendDiagControlCommandRequestOutput = ::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::sendDiagControlCommandRequest::Output;
              virtual ::ara::core::Future<sendDiagControlCommandRequestOutput>
              sendDiagControlCommandRequest(::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& controlCommand, ::ara::stdtypes::String const& controlMessage) = 0;

              events::assemblyStatusReady assemblyStatusReady;
              events::assemblyStatusUpdate assemblyStatusUpdate;
              events::responseReady responseReady;
              events::sendDiagControlCommandResponse sendDiagControlCommandResponse;
              events::updateAvailable updateAvailable;

              methods::cancelRequest m_cancelRequest;
              methods::getDiagAssemblyStatus m_getDiagAssemblyStatus;
              methods::getDiagAssemblyStatusHash m_getDiagAssemblyStatusHash;
              methods::getDiagDataByGroups m_getDiagDataByGroups;
              methods::getDiagDataByKeys m_getDiagDataByKeys;
              methods::readRequestedResults m_readRequestedResults;
              methods::refreshAssemblyStatus m_refreshAssemblyStatus;
              methods::requestDiagAssemblyStatusOnChange m_requestDiagAssemblyStatusOnChange;
              methods::requestDiagDataByGroups m_requestDiagDataByGroups;
              methods::requestDiagDataByKeys m_requestDiagDataByKeys;
              methods::requestDiagDataOnChange m_requestDiagDataOnChange;
              methods::requestDiagDataOnThreshold m_requestDiagDataOnThreshold;
              methods::requestSampledDiagData m_requestSampledDiagData;
              methods::requestSetDiagData m_requestSetDiagData;
              methods::sendDiagControlCommandRequest m_sendDiagControlCommandRequest;

            };
          } // namespace skeleton
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg
#endif
