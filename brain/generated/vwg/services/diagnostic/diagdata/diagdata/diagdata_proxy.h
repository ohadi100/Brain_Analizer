/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_DIAGDATA_PROXY_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_DIAGDATA_PROXY_H

#include "vwg/services/diagnostic/diagdata/diagdata/diagdata_common.h"

#include "ac/com/cpp_binding/proxy/event.hpp"
#include "ac/com/cpp_binding/proxy/method.hpp"
#include "ac/com/cpp_binding/proxy/proxy.hpp"
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

          namespace proxy
          {

            namespace events
            {
              using assemblyStatusReady = ::ac::com::cpp_binding::proxy::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::assemblyStatusReady>;
              using assemblyStatusUpdate = ::ac::com::cpp_binding::proxy::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::assemblyStatusUpdate>;
              using responseReady = ::ac::com::cpp_binding::proxy::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::responseReady>;
              using sendDiagControlCommandResponse = ::ac::com::cpp_binding::proxy::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::sendDiagControlCommandResponse>;
              using updateAvailable = ::ac::com::cpp_binding::proxy::Event<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Events::updateAvailable>;
            } // namespace events

            namespace methods
            {
              using cancelRequest = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::cancelRequest>;
              using getDiagAssemblyStatus = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatus>;
              using getDiagAssemblyStatusHash = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagAssemblyStatusHash>;
              using getDiagDataByGroups = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByGroups>;
              using getDiagDataByKeys = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::getDiagDataByKeys>;
              using readRequestedResults = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::readRequestedResults>;
              using refreshAssemblyStatus = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::refreshAssemblyStatus>;
              using requestDiagAssemblyStatusOnChange = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagAssemblyStatusOnChange>;
              using requestDiagDataByGroups = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByGroups>;
              using requestDiagDataByKeys = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataByKeys>;
              using requestDiagDataOnChange = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnChange>;
              using requestDiagDataOnThreshold = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestDiagDataOnThreshold>;
              using requestSampledDiagData = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSampledDiagData>;
              using requestSetDiagData = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::requestSetDiagData>;
              using sendDiagControlCommandRequest = ::ac::com::cpp_binding::proxy::Method<::vwg::services::diagnostic::diagdata::diagdata::DiagData::Methods::sendDiagControlCommandRequest>;
            } // namespace methods

            class DiagDataProxy
            : public ::ac::com::cpp_binding::proxy::Proxy<DiagData>
            {
              public:
              using HandleType = ::ac::com::cpp_binding::proxy::Proxy<DiagData>::HandleType;

              using ConstructionToken = DiagDataProxy;

              static ::ara::core::Result<ConstructionToken> Preconstruct(HandleType const& handle) noexcept;

              explicit DiagDataProxy(HandleType const& handle);

              ~DiagDataProxy() noexcept;

              DiagDataProxy(DiagDataProxy&& /*other*/) noexcept;
              DiagDataProxy& operator=(DiagDataProxy&& /*other*/) & noexcept;
              DiagDataProxy(DiagDataProxy const&) = delete;
              DiagDataProxy& operator=(DiagDataProxy const&) = delete;

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
            };
          } // namespace proxy
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg
#endif
