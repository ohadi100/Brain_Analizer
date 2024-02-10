/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_COMMON_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_types.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idspremiumservices
      {

        namespace idscansensor
        {

          class IdsCanSensor
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Method identifier and configuration
            struct Methods
            {
              struct setCanSensorFeaturesElement0
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"setCanSensorFeaturesElement0"};

                struct Output;
                using Signature = Output(::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesSet const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct undefineCanSensorFeaturesElement0
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{1u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"undefineCanSensorFeaturesElement0"};

                struct Output;
                using Signature = Output(::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesUndefine const&);

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
              struct canSensorFeaturesElement0
              {
                using FieldType = ::vwg::services::security::idspremiumservices::idscansensor::CanSensorFeaturesType;
                struct Notify
                {
                  static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                  static constexpr ::ac::com::cpp_binding::Event_name name{"canSensorFeaturesElement0.EVT"};
                  static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                  static constexpr bool updateOnSubscribe{true};
                  using SampleType = FieldType;
                  static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
                };
                struct Get
                {
                  static constexpr ::ac::com::cpp_binding::Method_id id{2u};
                  static constexpr ::ac::com::cpp_binding::Method_name name{"canSensorFeaturesElement0.GET"};

                  using Output = FieldType;
                  using Signature = Output();

                  static ::ara::core::ErrorCode GetErrorCode(
                  ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                  static ::ara::core::ErrorCode GetErrorCode(
                  ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                  static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
                };
              };

              struct periodicSignalElement0
              {
                using FieldType = ::vwg::services::security::idspremiumservices::idscansensor::PeriodicSignalType;
                struct Notify
                {
                  static constexpr ::ac::com::cpp_binding::Event_id id{1u};
                  static constexpr ::ac::com::cpp_binding::Event_name name{"periodicSignalElement0.EVT"};
                  static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                  static constexpr bool updateOnSubscribe{true};
                  using SampleType = FieldType;
                  static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
                };
                struct Get
                {
                  static constexpr ::ac::com::cpp_binding::Method_id id{3u};
                  static constexpr ::ac::com::cpp_binding::Method_name name{"periodicSignalElement0.GET"};

                  using Output = FieldType;
                  using Signature = Output();

                  static ::ara::core::ErrorCode GetErrorCode(
                  ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                  static ::ara::core::ErrorCode GetErrorCode(
                  ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                  static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
                };
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,2u> get_events_of_service_interface()
            {
              return
              {
                Fields::canSensorFeaturesElement0::Notify::name,
                Fields::periodicSignalElement0::Notify::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,4u> get_methods_of_service_interface()
            {
              return
              {
                Methods::setCanSensorFeaturesElement0::name,
                Methods::undefineCanSensorFeaturesElement0::name,
                Fields::canSensorFeaturesElement0::Get::name,
                Fields::periodicSignalElement0::Get::name
              };
            }
          };

          struct IdsCanSensor::Methods::setCanSensorFeaturesElement0::Output
          {
            ::vwg::services::security::idspremiumservices::idscansensor::OperationStatus status{};
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

          struct IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::Output
          {
            ::vwg::services::security::idspremiumservices::idscansensor::OperationStatus status{};
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

        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif

