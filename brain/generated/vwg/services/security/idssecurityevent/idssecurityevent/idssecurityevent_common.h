/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IDSSECURITYEVENT_COMMON_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IDSSECURITYEVENT_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_types.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idssecurityevent
      {

        namespace idssecurityevent
        {

          class IDSSecurityEvent
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEvent"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Event identifier and configuration
            struct Events
            {
              struct securityEventEvent
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"securityEventEvent"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::vwg::services::security::idssecurityevent::idssecurityevent::SecurityEventEvent;
                static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
              };

            };
            // -- Method identifier and configuration
            struct Methods
            {
              struct getSecurityEventElementByKey
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getSecurityEventElementByKey"};

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

              struct getSecurityEventElements
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{1u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"getSecurityEventElements"};

                struct Output;
                using Signature = Output();

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct subscribeSecurityEvent
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{2u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"subscribeSecurityEvent"};

                struct Output;
                using Signature = Output(::ara::stdtypes::Boolean,
                ::vwg::stdtypes::DT_uuid const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct subscribeSecurityEventByKey
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{3u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"subscribeSecurityEventByKey"};

                struct Output;
                using Signature = Output(::vwg::stdtypes::DT_uuid const&,
                ::ara::stdtypes::Boolean,
                ::vwg::stdtypes::DT_uuid const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,3> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct unsubscribeSecurityEvent
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{4u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"unsubscribeSecurityEvent"};

                struct Output;
                using Signature = Output(::ara::stdtypes::UInt32,
                ::vwg::stdtypes::DT_uuid const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,2> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,1u> get_events_of_service_interface()
            {
              return
              {
                Events::securityEventEvent::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,5u> get_methods_of_service_interface()
            {
              return
              {
                Methods::getSecurityEventElementByKey::name,
                Methods::getSecurityEventElements::name,
                Methods::subscribeSecurityEvent::name,
                Methods::subscribeSecurityEventByKey::name,
                Methods::unsubscribeSecurityEvent::name
              };
            }
          };

          struct IDSSecurityEvent::Methods::getSecurityEventElementByKey::Output
          {
            ::vwg::services::security::idssecurityevent::idssecurityevent::securityEventResponseSingle result{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->result);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->result);
            }
          };

          struct IDSSecurityEvent::Methods::getSecurityEventElements::Output
          {
            ::vwg::services::security::idssecurityevent::idssecurityevent::SecurityEventResponse result{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->result);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->result);
            }
          };

          struct IDSSecurityEvent::Methods::subscribeSecurityEvent::Output
          {
            ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEventSubscriptionResponse result{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->result);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->result);
            }
          };

          struct IDSSecurityEvent::Methods::subscribeSecurityEventByKey::Output
          {
            ::vwg::services::security::idssecurityevent::idssecurityevent::IDSSecurityEventSubscriptionResponse result{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->result);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->result);
            }
          };

          struct IDSSecurityEvent::Methods::unsubscribeSecurityEvent::Output
          {
            ::vwg::services::security::idssecurityevent::idssecurityevent::SubscriptionStatus status{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->status);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->status);
            }
          };

        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif

