/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_ODCAGENTCOMMONLARGE_COMMON_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_ODCAGENTCOMMONLARGE_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_types.h"

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

          class OdcAgentCommonLarge
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::connect::datacollector::odcagentcommonlarge::OdcAgentCommonLarge"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Event identifier and configuration
            struct Events
            {
              struct event
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"event"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::vwg::services::connect::datacollector::odcagentcommonlarge::Event;
                static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
              };

            };
            // -- Method identifier and configuration
            struct Methods
            {
              struct addCampaign
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"addCampaign"};

                struct Output;
                using Signature = Output(::vwg::services::connect::datacollector::odcagentcommonlarge::AddCampaignRequest const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct estimateCampaign
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{1u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"estimateCampaign"};

                struct Output;
                using Signature = Output(::vwg::services::connect::datacollector::odcagentcommonlarge::Campaign const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getCampaigns
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{2u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getCampaigns"};

                struct Output;
                using Signature = Output();

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getData
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{3u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getData"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct getInfo
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{4u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getInfo"};

                struct Output;
                using Signature = Output();

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct removeCampaign
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{5u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"removeCampaign"};

                struct Output;
                using Signature = Output(::ara::stdtypes::String const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct setData
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{6u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"setData"};

                struct Output;
                using Signature = Output(::vwg::services::connect::datacollector::odcagentcommonlarge::SetDataRequest const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,1u> get_events_of_service_interface()
            {
              return
              {
                Events::event::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,7u> get_methods_of_service_interface()
            {
              return
              {
                Methods::addCampaign::name,
                Methods::estimateCampaign::name,
                Methods::getCampaigns::name,
                Methods::getData::name,
                Methods::getInfo::name,
                Methods::removeCampaign::name,
                Methods::setData::name
              };
            }
          };

          struct OdcAgentCommonLarge::Methods::addCampaign::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::CampaignOpResponse response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

          struct OdcAgentCommonLarge::Methods::estimateCampaign::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::CampaignOpResponse response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

          struct OdcAgentCommonLarge::Methods::getCampaigns::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::GetCampaignsResponse response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

          struct OdcAgentCommonLarge::Methods::getData::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::GetDataResponse response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

          struct OdcAgentCommonLarge::Methods::getInfo::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::GetInfoResponse response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

          struct OdcAgentCommonLarge::Methods::removeCampaign::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::CampaignOpResponse response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

          struct OdcAgentCommonLarge::Methods::setData::Output
          {
            ::vwg::services::connect::datacollector::odcagentcommonlarge::Status response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->response);
            }
          };

        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif

