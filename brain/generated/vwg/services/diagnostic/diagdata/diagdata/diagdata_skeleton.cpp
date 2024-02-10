/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/diagnostic/diagdata/diagdata/diagdata_skeleton.h"
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
        template class Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::assemblyStatusReady>;
        template class Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::assemblyStatusUpdate>;
        template class Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::responseReady>;
        template class Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::sendDiagControlCommandResponse>;
        template class Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::updateAvailable>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::cancelRequest>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatus>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatusHash>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByGroups>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::readRequestedResults>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::refreshAssemblyStatus>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagAssemblyStatusOnChange>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByGroups>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByKeys>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnChange>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnThreshold>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSampledDiagData>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSetDiagData>;
        template class Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::sendDiagControlCommandRequest>;
        template class Skeleton<::vwg::services::diagnostic::diagdata::diagdata::DiagData>;
      } // namespace skeleton
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

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
            DiagDataSkeleton::DiagDataSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , assemblyStatusReady{port_link()}
            , assemblyStatusUpdate{port_link()}
            , responseReady{port_link()}
            , sendDiagControlCommandResponse{port_link()}
            , updateAvailable{port_link()}
            , m_cancelRequest{method_dispatcher()}
            , m_getDiagAssemblyStatus{method_dispatcher()}
            , m_getDiagAssemblyStatusHash{method_dispatcher()}
            , m_getDiagDataByGroups{method_dispatcher()}
            , m_getDiagDataByKeys{method_dispatcher()}
            , m_readRequestedResults{method_dispatcher()}
            , m_refreshAssemblyStatus{method_dispatcher()}
            , m_requestDiagAssemblyStatusOnChange{method_dispatcher()}
            , m_requestDiagDataByGroups{method_dispatcher()}
            , m_requestDiagDataByKeys{method_dispatcher()}
            , m_requestDiagDataOnChange{method_dispatcher()}
            , m_requestDiagDataOnThreshold{method_dispatcher()}
            , m_requestSampledDiagData{method_dispatcher()}
            , m_requestSetDiagData{method_dispatcher()}
            , m_sendDiagControlCommandRequest{method_dispatcher()}
            {
              m_cancelRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return cancelRequest(accessID, requestID); });

              m_getDiagAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatus(accessID, requestOptions); });

              m_getDiagAssemblyStatusHash.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatusHash(accessID, requestOptions); });

              m_getDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions, timeout); });

              m_getDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByKeys(accessID, diagDataKeys, resultOptions, timeout); });

              m_readRequestedResults.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return readRequestedResults(accessID, requestID); });

              m_refreshAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::refreshAssemblyStatus_diagNodes const& diagNodes) { return refreshAssemblyStatus(accessID, diagNodes); });

              m_requestDiagAssemblyStatusOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return requestDiagAssemblyStatusOnChange(accessID, requestOptions); });

              m_requestDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions); });

              m_requestDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByKeys(accessID, diagDataKeys, resultOptions); });

              m_requestDiagDataOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnChange(accessID, diagDataKey, minDeltaTriggerTime, resultOptions); });

              m_requestDiagDataOnThreshold.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::Int64 const& upperThreshold, ::ara::stdtypes::Int64 const& lowerThreshold, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnThreshold(accessID, diagDataKey, minDeltaTriggerTime, upperThreshold, lowerThreshold, resultOptions); });

              m_requestSampledDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::UInt32 const& measurementPeriod, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestSampledDiagData(accessID, diagDataKey, minDeltaTriggerTime, measurementPeriod, resultOptions); });

              m_requestSetDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataItems, ::vwg::services::diagnostic::diagdata::diagdata::SetOptions const& setOptions) { return requestSetDiagData(accessID, diagDataItems, setOptions); });

              m_sendDiagControlCommandRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& controlCommand, ::ara::stdtypes::String const& controlMessage) { return sendDiagControlCommandRequest(accessID, controlCommand, controlMessage); });

            }

            DiagDataSkeleton::DiagDataSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , assemblyStatusReady{port_link()}
            , assemblyStatusUpdate{port_link()}
            , responseReady{port_link()}
            , sendDiagControlCommandResponse{port_link()}
            , updateAvailable{port_link()}
            , m_cancelRequest{method_dispatcher()}
            , m_getDiagAssemblyStatus{method_dispatcher()}
            , m_getDiagAssemblyStatusHash{method_dispatcher()}
            , m_getDiagDataByGroups{method_dispatcher()}
            , m_getDiagDataByKeys{method_dispatcher()}
            , m_readRequestedResults{method_dispatcher()}
            , m_refreshAssemblyStatus{method_dispatcher()}
            , m_requestDiagAssemblyStatusOnChange{method_dispatcher()}
            , m_requestDiagDataByGroups{method_dispatcher()}
            , m_requestDiagDataByKeys{method_dispatcher()}
            , m_requestDiagDataOnChange{method_dispatcher()}
            , m_requestDiagDataOnThreshold{method_dispatcher()}
            , m_requestSampledDiagData{method_dispatcher()}
            , m_requestSetDiagData{method_dispatcher()}
            , m_sendDiagControlCommandRequest{method_dispatcher()}
            {
              m_cancelRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return cancelRequest(accessID, requestID); });

              m_getDiagAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatus(accessID, requestOptions); });

              m_getDiagAssemblyStatusHash.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatusHash(accessID, requestOptions); });

              m_getDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions, timeout); });

              m_getDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByKeys(accessID, diagDataKeys, resultOptions, timeout); });

              m_readRequestedResults.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return readRequestedResults(accessID, requestID); });

              m_refreshAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::refreshAssemblyStatus_diagNodes const& diagNodes) { return refreshAssemblyStatus(accessID, diagNodes); });

              m_requestDiagAssemblyStatusOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return requestDiagAssemblyStatusOnChange(accessID, requestOptions); });

              m_requestDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions); });

              m_requestDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByKeys(accessID, diagDataKeys, resultOptions); });

              m_requestDiagDataOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnChange(accessID, diagDataKey, minDeltaTriggerTime, resultOptions); });

              m_requestDiagDataOnThreshold.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::Int64 const& upperThreshold, ::ara::stdtypes::Int64 const& lowerThreshold, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnThreshold(accessID, diagDataKey, minDeltaTriggerTime, upperThreshold, lowerThreshold, resultOptions); });

              m_requestSampledDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::UInt32 const& measurementPeriod, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestSampledDiagData(accessID, diagDataKey, minDeltaTriggerTime, measurementPeriod, resultOptions); });

              m_requestSetDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataItems, ::vwg::services::diagnostic::diagdata::diagdata::SetOptions const& setOptions) { return requestSetDiagData(accessID, diagDataItems, setOptions); });

              m_sendDiagControlCommandRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& controlCommand, ::ara::stdtypes::String const& controlMessage) { return sendDiagControlCommandRequest(accessID, controlCommand, controlMessage); });

            }

            DiagDataSkeleton::DiagDataSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , assemblyStatusReady{port_link()}
            , assemblyStatusUpdate{port_link()}
            , responseReady{port_link()}
            , sendDiagControlCommandResponse{port_link()}
            , updateAvailable{port_link()}
            , m_cancelRequest{method_dispatcher()}
            , m_getDiagAssemblyStatus{method_dispatcher()}
            , m_getDiagAssemblyStatusHash{method_dispatcher()}
            , m_getDiagDataByGroups{method_dispatcher()}
            , m_getDiagDataByKeys{method_dispatcher()}
            , m_readRequestedResults{method_dispatcher()}
            , m_refreshAssemblyStatus{method_dispatcher()}
            , m_requestDiagAssemblyStatusOnChange{method_dispatcher()}
            , m_requestDiagDataByGroups{method_dispatcher()}
            , m_requestDiagDataByKeys{method_dispatcher()}
            , m_requestDiagDataOnChange{method_dispatcher()}
            , m_requestDiagDataOnThreshold{method_dispatcher()}
            , m_requestSampledDiagData{method_dispatcher()}
            , m_requestSetDiagData{method_dispatcher()}
            , m_sendDiagControlCommandRequest{method_dispatcher()}
            {
              m_cancelRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return cancelRequest(accessID, requestID); });

              m_getDiagAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatus(accessID, requestOptions); });

              m_getDiagAssemblyStatusHash.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatusHash(accessID, requestOptions); });

              m_getDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions, timeout); });

              m_getDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByKeys(accessID, diagDataKeys, resultOptions, timeout); });

              m_readRequestedResults.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return readRequestedResults(accessID, requestID); });

              m_refreshAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::refreshAssemblyStatus_diagNodes const& diagNodes) { return refreshAssemblyStatus(accessID, diagNodes); });

              m_requestDiagAssemblyStatusOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return requestDiagAssemblyStatusOnChange(accessID, requestOptions); });

              m_requestDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions); });

              m_requestDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByKeys(accessID, diagDataKeys, resultOptions); });

              m_requestDiagDataOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnChange(accessID, diagDataKey, minDeltaTriggerTime, resultOptions); });

              m_requestDiagDataOnThreshold.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::Int64 const& upperThreshold, ::ara::stdtypes::Int64 const& lowerThreshold, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnThreshold(accessID, diagDataKey, minDeltaTriggerTime, upperThreshold, lowerThreshold, resultOptions); });

              m_requestSampledDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::UInt32 const& measurementPeriod, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestSampledDiagData(accessID, diagDataKey, minDeltaTriggerTime, measurementPeriod, resultOptions); });

              m_requestSetDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataItems, ::vwg::services::diagnostic::diagdata::diagdata::SetOptions const& setOptions) { return requestSetDiagData(accessID, diagDataItems, setOptions); });

              m_sendDiagControlCommandRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& controlCommand, ::ara::stdtypes::String const& controlMessage) { return sendDiagControlCommandRequest(accessID, controlCommand, controlMessage); });

            }

            DiagDataSkeleton::DiagDataSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , assemblyStatusReady{std::move(token.assemblyStatusReady)}
            , assemblyStatusUpdate{std::move(token.assemblyStatusUpdate)}
            , responseReady{std::move(token.responseReady)}
            , sendDiagControlCommandResponse{std::move(token.sendDiagControlCommandResponse)}
            , updateAvailable{std::move(token.updateAvailable)}
            , m_cancelRequest{std::move(token.cancelRequest)}
            , m_getDiagAssemblyStatus{std::move(token.getDiagAssemblyStatus)}
            , m_getDiagAssemblyStatusHash{std::move(token.getDiagAssemblyStatusHash)}
            , m_getDiagDataByGroups{std::move(token.getDiagDataByGroups)}
            , m_getDiagDataByKeys{std::move(token.getDiagDataByKeys)}
            , m_readRequestedResults{std::move(token.readRequestedResults)}
            , m_refreshAssemblyStatus{std::move(token.refreshAssemblyStatus)}
            , m_requestDiagAssemblyStatusOnChange{std::move(token.requestDiagAssemblyStatusOnChange)}
            , m_requestDiagDataByGroups{std::move(token.requestDiagDataByGroups)}
            , m_requestDiagDataByKeys{std::move(token.requestDiagDataByKeys)}
            , m_requestDiagDataOnChange{std::move(token.requestDiagDataOnChange)}
            , m_requestDiagDataOnThreshold{std::move(token.requestDiagDataOnThreshold)}
            , m_requestSampledDiagData{std::move(token.requestSampledDiagData)}
            , m_requestSetDiagData{std::move(token.requestSetDiagData)}
            , m_sendDiagControlCommandRequest{std::move(token.sendDiagControlCommandRequest)}
            {
              m_cancelRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return cancelRequest(accessID, requestID); });

              m_getDiagAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatus(accessID, requestOptions); });

              m_getDiagAssemblyStatusHash.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return getDiagAssemblyStatusHash(accessID, requestOptions); });

              m_getDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions, timeout); });

              m_getDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions, ::ara::stdtypes::UInt32 const& timeout) { return getDiagDataByKeys(accessID, diagDataKeys, resultOptions, timeout); });

              m_readRequestedResults.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& requestID) { return readRequestedResults(accessID, requestID); });

              m_refreshAssemblyStatus.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::refreshAssemblyStatus_diagNodes const& diagNodes) { return refreshAssemblyStatus(accessID, diagNodes); });

              m_requestDiagAssemblyStatusOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const& requestOptions) { return requestDiagAssemblyStatusOnChange(accessID, requestOptions); });

              m_requestDiagDataByGroups.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByGroups_diagDataGroupKeys const& diagDataGroupKeys, ::ara::stdtypes::String const& rootNode, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByGroups(accessID, diagDataGroupKeys, rootNode, resultOptions); });

              m_requestDiagDataByKeys.set_function(
              [this](::ara::stdtypes::String const& accessID, ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByKeys_diagDataKeys const& diagDataKeys, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataByKeys(accessID, diagDataKeys, resultOptions); });

              m_requestDiagDataOnChange.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnChange(accessID, diagDataKey, minDeltaTriggerTime, resultOptions); });

              m_requestDiagDataOnThreshold.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::Int64 const& upperThreshold, ::ara::stdtypes::Int64 const& lowerThreshold, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestDiagDataOnThreshold(accessID, diagDataKey, minDeltaTriggerTime, upperThreshold, lowerThreshold, resultOptions); });

              m_requestSampledDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataKey, ::ara::stdtypes::UInt16 const& minDeltaTriggerTime, ::ara::stdtypes::UInt32 const& measurementPeriod, ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const& resultOptions) { return requestSampledDiagData(accessID, diagDataKey, minDeltaTriggerTime, measurementPeriod, resultOptions); });

              m_requestSetDiagData.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& diagDataItems, ::vwg::services::diagnostic::diagdata::diagdata::SetOptions const& setOptions) { return requestSetDiagData(accessID, diagDataItems, setOptions); });

              m_sendDiagControlCommandRequest.set_function(
              [this](::ara::stdtypes::String const& accessID, ::ara::stdtypes::String const& controlCommand, ::ara::stdtypes::String const& controlMessage) { return sendDiagControlCommandRequest(accessID, controlCommand, controlMessage); });

            }

            ::ara::core::Result<DiagDataSkeleton::ConstructionToken>
            DiagDataSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
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

            ::ara::core::Result<DiagDataSkeleton::ConstructionToken>
            DiagDataSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
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

            ::ara::core::Result<DiagDataSkeleton::ConstructionToken>
            DiagDataSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
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

            DiagDataSkeleton::ConstructionToken::~ConstructionToken() = default;
            DiagDataSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            DiagDataSkeleton::ConstructionToken& DiagDataSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            DiagDataSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , assemblyStatusReady{skeleton_impl->port_link()}
            , assemblyStatusUpdate{skeleton_impl->port_link()}
            , responseReady{skeleton_impl->port_link()}
            , sendDiagControlCommandResponse{skeleton_impl->port_link()}
            , updateAvailable{skeleton_impl->port_link()}
            , cancelRequest{skeleton_impl->method_dispatcher()}
            , getDiagAssemblyStatus{skeleton_impl->method_dispatcher()}
            , getDiagAssemblyStatusHash{skeleton_impl->method_dispatcher()}
            , getDiagDataByGroups{skeleton_impl->method_dispatcher()}
            , getDiagDataByKeys{skeleton_impl->method_dispatcher()}
            , readRequestedResults{skeleton_impl->method_dispatcher()}
            , refreshAssemblyStatus{skeleton_impl->method_dispatcher()}
            , requestDiagAssemblyStatusOnChange{skeleton_impl->method_dispatcher()}
            , requestDiagDataByGroups{skeleton_impl->method_dispatcher()}
            , requestDiagDataByKeys{skeleton_impl->method_dispatcher()}
            , requestDiagDataOnChange{skeleton_impl->method_dispatcher()}
            , requestDiagDataOnThreshold{skeleton_impl->method_dispatcher()}
            , requestSampledDiagData{skeleton_impl->method_dispatcher()}
            , requestSetDiagData{skeleton_impl->method_dispatcher()}
            , sendDiagControlCommandRequest{skeleton_impl->method_dispatcher()}
            {
            }

            DiagDataSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , assemblyStatusReady{skeleton_impl->port_link()}
            , assemblyStatusUpdate{skeleton_impl->port_link()}
            , responseReady{skeleton_impl->port_link()}
            , sendDiagControlCommandResponse{skeleton_impl->port_link()}
            , updateAvailable{skeleton_impl->port_link()}
            , cancelRequest{skeleton_impl->method_dispatcher()}
            , getDiagAssemblyStatus{skeleton_impl->method_dispatcher()}
            , getDiagAssemblyStatusHash{skeleton_impl->method_dispatcher()}
            , getDiagDataByGroups{skeleton_impl->method_dispatcher()}
            , getDiagDataByKeys{skeleton_impl->method_dispatcher()}
            , readRequestedResults{skeleton_impl->method_dispatcher()}
            , refreshAssemblyStatus{skeleton_impl->method_dispatcher()}
            , requestDiagAssemblyStatusOnChange{skeleton_impl->method_dispatcher()}
            , requestDiagDataByGroups{skeleton_impl->method_dispatcher()}
            , requestDiagDataByKeys{skeleton_impl->method_dispatcher()}
            , requestDiagDataOnChange{skeleton_impl->method_dispatcher()}
            , requestDiagDataOnThreshold{skeleton_impl->method_dispatcher()}
            , requestSampledDiagData{skeleton_impl->method_dispatcher()}
            , requestSetDiagData{skeleton_impl->method_dispatcher()}
            , sendDiagControlCommandRequest{skeleton_impl->method_dispatcher()}
            {
            }

            DiagDataSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , assemblyStatusReady{skeleton_impl->port_link()}
            , assemblyStatusUpdate{skeleton_impl->port_link()}
            , responseReady{skeleton_impl->port_link()}
            , sendDiagControlCommandResponse{skeleton_impl->port_link()}
            , updateAvailable{skeleton_impl->port_link()}
            , cancelRequest{skeleton_impl->method_dispatcher()}
            , getDiagAssemblyStatus{skeleton_impl->method_dispatcher()}
            , getDiagAssemblyStatusHash{skeleton_impl->method_dispatcher()}
            , getDiagDataByGroups{skeleton_impl->method_dispatcher()}
            , getDiagDataByKeys{skeleton_impl->method_dispatcher()}
            , readRequestedResults{skeleton_impl->method_dispatcher()}
            , refreshAssemblyStatus{skeleton_impl->method_dispatcher()}
            , requestDiagAssemblyStatusOnChange{skeleton_impl->method_dispatcher()}
            , requestDiagDataByGroups{skeleton_impl->method_dispatcher()}
            , requestDiagDataByKeys{skeleton_impl->method_dispatcher()}
            , requestDiagDataOnChange{skeleton_impl->method_dispatcher()}
            , requestDiagDataOnThreshold{skeleton_impl->method_dispatcher()}
            , requestSampledDiagData{skeleton_impl->method_dispatcher()}
            , requestSetDiagData{skeleton_impl->method_dispatcher()}
            , sendDiagControlCommandRequest{skeleton_impl->method_dispatcher()}
            {
            }

          } // namespace skeleton
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg
