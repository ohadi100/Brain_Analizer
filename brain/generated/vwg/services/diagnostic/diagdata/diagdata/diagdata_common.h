/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_DIAGDATA_COMMON_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_DIAGDATA_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/diagnostic/diagdata/diagdata/diagdata_types.h"

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

          class DiagData
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::diagnostic::diagdata::diagdata::DiagData"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Event identifier and configuration
            struct Events
            {
              struct assemblyStatusReady
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"assemblyStatusReady"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::ara::stdtypes::UInt8;
              };

              struct assemblyStatusUpdate
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{1u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"assemblyStatusUpdate"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::ara::stdtypes::String;
                static ::ac::com::someip::serialization::Serialization_attributes_entry const& eventSProps();
              };

              struct responseReady
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{2u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"responseReady"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::ara::stdtypes::String;
                static ::ac::com::someip::serialization::Serialization_attributes_entry const& eventSProps();
              };

              struct sendDiagControlCommandResponse
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{3u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"sendDiagControlCommandResponse"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::vwg::services::diagnostic::diagdata::diagdata::DiagData_sendDiagControlCommandResponse_eventData;
                static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
              };

              struct updateAvailable
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{4u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"updateAvailable"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::ara::stdtypes::String;
                static ::ac::com::someip::serialization::Serialization_attributes_entry const& eventSProps();
              };

            };
            // -- Method identifier and configuration
            struct Methods
            {
              struct cancelRequest
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"cancelRequest"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getDiagAssemblyStatus
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{1u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getDiagAssemblyStatus"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getDiagAssemblyStatusHash
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{2u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getDiagAssemblyStatusHash"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getDiagDataByGroups
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{3u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getDiagDataByGroups"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByGroups_diagDataGroupKeys const&,
                ::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&,
                ::ara::stdtypes::UInt32);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,5> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getDiagDataByKeys
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{4u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getDiagDataByKeys"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::getDiagDataByKeys_diagDataKeys const&,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&,
                ::ara::stdtypes::UInt32);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,4> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct readRequestedResults
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{5u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"readRequestedResults"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct refreshAssemblyStatus
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{6u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"refreshAssemblyStatus"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::refreshAssemblyStatus_diagNodes const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestDiagAssemblyStatusOnChange
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{7u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestDiagAssemblyStatusOnChange"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::RequestOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestDiagDataByGroups
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{8u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestDiagDataByGroups"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByGroups_diagDataGroupKeys const&,
                ::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,4> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestDiagDataByKeys
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{9u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestDiagDataByKeys"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::requestDiagDataByKeys_diagDataKeys const&,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,3> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestDiagDataOnChange
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{10u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestDiagDataOnChange"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&,
                ::ara::stdtypes::UInt16,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,4> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestDiagDataOnThreshold
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{11u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestDiagDataOnThreshold"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&,
                ::ara::stdtypes::UInt16,
                ::ara::stdtypes::Int64,
                ::ara::stdtypes::Int64,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,6> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestSampledDiagData
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{12u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestSampledDiagData"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&,
                ::ara::stdtypes::UInt16,
                ::ara::stdtypes::UInt32,
                ::vwg::services::diagnostic::diagdata::diagdata::ResultOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,5> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestSetDiagData
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{13u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestSetDiagData"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&,
                ::vwg::services::diagnostic::diagdata::diagdata::SetOptions const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,3> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct sendDiagControlCommandRequest
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{14u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"sendDiagControlCommandRequest"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&,
                ::ara::stdtypes::String const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,3> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,5u> get_events_of_service_interface()
            {
              return
              {
                Events::assemblyStatusReady::name,
                Events::assemblyStatusUpdate::name,
                Events::responseReady::name,
                Events::sendDiagControlCommandResponse::name,
                Events::updateAvailable::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,15u> get_methods_of_service_interface()
            {
              return
              {
                Methods::cancelRequest::name,
                Methods::getDiagAssemblyStatus::name,
                Methods::getDiagAssemblyStatusHash::name,
                Methods::getDiagDataByGroups::name,
                Methods::getDiagDataByKeys::name,
                Methods::readRequestedResults::name,
                Methods::refreshAssemblyStatus::name,
                Methods::requestDiagAssemblyStatusOnChange::name,
                Methods::requestDiagDataByGroups::name,
                Methods::requestDiagDataByKeys::name,
                Methods::requestDiagDataOnChange::name,
                Methods::requestDiagDataOnThreshold::name,
                Methods::requestSampledDiagData::name,
                Methods::requestSetDiagData::name,
                Methods::sendDiagControlCommandRequest::name
              };
            }
          };

          struct DiagData::Methods::cancelRequest::Output
          {
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::getDiagAssemblyStatus::Output
          {
            ::ara::stdtypes::String diagAssemblyStatus{};
            ::ara::stdtypes::String hash{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->diagAssemblyStatus);
              f(this->hash);
              f(this->timestamp);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->diagAssemblyStatus);
              f(this->hash);
              f(this->timestamp);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::getDiagAssemblyStatusHash::Output
          {
            ::ara::stdtypes::String hash{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->hash);
              f(this->timestamp);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->hash);
              f(this->timestamp);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::getDiagDataByGroups::Output
          {
            ::ara::stdtypes::String diagDataItems{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->diagDataItems);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->diagDataItems);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::getDiagDataByKeys::Output
          {
            ::ara::stdtypes::String diagDataItems{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->diagDataItems);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->diagDataItems);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::readRequestedResults::Output
          {
            ::ara::stdtypes::String diagDataItems{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->diagDataItems);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->diagDataItems);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::refreshAssemblyStatus::Output
          {
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::requestDiagAssemblyStatusOnChange::Output
          {
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            ::ara::stdtypes::String requestID{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->returnStatus);
              f(this->requestID);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->returnStatus);
              f(this->requestID);
            }
          };

          struct DiagData::Methods::requestDiagDataByGroups::Output
          {
            ::ara::stdtypes::String requestID{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->requestID);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->requestID);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::requestDiagDataByKeys::Output
          {
            ::ara::stdtypes::String requestID{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->requestID);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->requestID);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::requestDiagDataOnChange::Output
          {
            ::ara::stdtypes::String requestID{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->requestID);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->requestID);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::requestDiagDataOnThreshold::Output
          {
            ::ara::stdtypes::String requestID{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->requestID);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->requestID);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::requestSampledDiagData::Output
          {
            ::ara::stdtypes::String requestID{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->requestID);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->requestID);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::requestSetDiagData::Output
          {
            ::ara::stdtypes::String requestID{};
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->requestID);
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->requestID);
              f(this->returnStatus);
            }
          };

          struct DiagData::Methods::sendDiagControlCommandRequest::Output
          {
            ::vwg::services::diagnostic::diagdata::diagdata::ReturnStatus returnStatus{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->returnStatus);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->returnStatus);
            }
          };

        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg
#endif

