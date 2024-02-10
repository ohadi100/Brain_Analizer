/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_COMMON_H
#define INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_types.h"

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace gsdp
      {

        namespace healthincidentprovider
        {

          class HealthIncidentProvider
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Event identifier and configuration
            struct Events
            {
              struct incident
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"incident"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::ara::stdtypes::String;
                static ::ac::com::someip::serialization::Serialization_attributes_entry const& eventSProps();
              };

            };
            // -- Method identifier and configuration
            struct Methods
            {
              struct configureIncidentEvent
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"configureIncidentEvent"};

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

              struct getLastIncidents
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{1u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getLastIncidents"};

                struct Output;
                using Signature = Output(::vwg::stdtypes::DT_uuid const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct requestIncidents
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{2u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"requestIncidents"};

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

            };
            // -- Field identifier and configuration
            struct Fields
            {
              struct openIncidents
              {
                using FieldType = ::ara::stdtypes::UInt16;
                struct Notify
                {
                  static constexpr ::ac::com::cpp_binding::Event_id id{1u};
                  static constexpr ::ac::com::cpp_binding::Event_name name{"openIncidents.EVT"};
                  static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                  static constexpr bool updateOnSubscribe{true};
                  using SampleType = FieldType;
                };
                struct Get
                {
                  static constexpr ::ac::com::cpp_binding::Method_id id{3u};
                  static constexpr ::ac::com::cpp_binding::Method_name name{"openIncidents.GET"};

                  using Output = FieldType;
                  using Signature = Output();

                  static ::ara::core::ErrorCode GetErrorCode(
                  ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                  static ::ara::core::ErrorCode GetErrorCode(
                  ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                };
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,2u> get_events_of_service_interface()
            {
              return
              {
                Events::incident::name,
                Fields::openIncidents::Notify::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,4u> get_methods_of_service_interface()
            {
              return
              {
                Methods::configureIncidentEvent::name,
                Methods::getLastIncidents::name,
                Methods::requestIncidents::name,
                Fields::openIncidents::Get::name
              };
            }
          };

          struct HealthIncidentProvider::Methods::configureIncidentEvent::Output
          {
            ::ara::stdtypes::Boolean success{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->success);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->success);
            }
          };

          struct HealthIncidentProvider::Methods::getLastIncidents::Output
          {
            ::ara::stdtypes::String incidents{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->incidents);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->incidents);
            }
          };

          struct HealthIncidentProvider::Methods::requestIncidents::Output
          {
            ::ara::stdtypes::String incidents{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->incidents);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->incidents);
            }
          };

        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif

