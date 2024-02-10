/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/diagnostic/diagdata/diagdata/diagdata_proxy.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/proxy/event_defs.hpp"
#include "ac/com/cpp_binding/proxy/method_defs.hpp"
#include "ac/com/cpp_binding/proxy/proxy_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace proxy
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
        template class Proxy<::vwg::services::diagnostic::diagdata::diagdata::DiagData>;
      } // namespace proxy
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

          namespace proxy
          {
            DiagDataProxy::DiagDataProxy(HandleType const& handle)
            : Proxy<DiagData>{handle}
            , assemblyStatusReady{port_link()}
            , assemblyStatusUpdate{port_link()}
            , responseReady{port_link()}
            , sendDiagControlCommandResponse{port_link()}
            , updateAvailable{port_link()}
            , cancelRequest{port_link()}
            , getDiagAssemblyStatus{port_link()}
            , getDiagAssemblyStatusHash{port_link()}
            , getDiagDataByGroups{port_link()}
            , getDiagDataByKeys{port_link()}
            , readRequestedResults{port_link()}
            , refreshAssemblyStatus{port_link()}
            , requestDiagAssemblyStatusOnChange{port_link()}
            , requestDiagDataByGroups{port_link()}
            , requestDiagDataByKeys{port_link()}
            , requestDiagDataOnChange{port_link()}
            , requestDiagDataOnThreshold{port_link()}
            , requestSampledDiagData{port_link()}
            , requestSetDiagData{port_link()}
            , sendDiagControlCommandRequest{port_link()}
            {
            }

            DiagDataProxy::~DiagDataProxy() noexcept
            {
              ::ac::com::cpp_binding::proxy::Proxy<DiagData>::close();
            }

            DiagDataProxy::DiagDataProxy(DiagDataProxy&& /*other*/) noexcept = default;
            DiagDataProxy& DiagDataProxy::operator=(DiagDataProxy&& /*other*/) & noexcept = default;

            ::ara::core::Result<DiagDataProxy::ConstructionToken>
            DiagDataProxy::Preconstruct(HandleType const& handle) noexcept
            {
              try
              {
                return ConstructionToken{handle};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

          } // namespace proxy
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg
