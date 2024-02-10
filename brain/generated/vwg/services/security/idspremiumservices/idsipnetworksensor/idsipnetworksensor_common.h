/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IDSIPNETWORKSENSOR_COMMON_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IDSIPNETWORKSENSOR_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_types.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idspremiumservices
      {

        namespace idsipnetworksensor
        {

          class IdsIpNetworkSensor
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::security::idspremiumservices::idsipnetworksensor::IdsIpNetworkSensor"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Method identifier and configuration
            struct Methods
            {
              struct setEthernetSensorFeaturesElement0
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"setEthernetSensorFeaturesElement0"};

                struct Output;
                using Signature = Output(::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesSet const&);

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::IdType domainId, ::ara::core::ErrorDomain::CodeType codeId, ::ara::core::ErrorDomain::SupportDataType data = 0, char const* userMessage = nullptr) noexcept;

                static ::ara::core::ErrorCode GetErrorCode(
                ::ara::core::ErrorDomain::CodeType codeId) noexcept;

                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
                static ::ac::com::someip::serialization::Serialization_attributes const& methodOutSProps();
              };

              struct undefineEthernetSensorFeaturesElement0
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{1u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"undefineEthernetSensorFeaturesElement0"};

                struct Output;
                using Signature = Output(::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesUndefine const&);

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
              struct ethernetSensorFeaturesElement0
              {
                using FieldType = ::vwg::services::security::idspremiumservices::idsipnetworksensor::EthernetSensorFeaturesType;
                struct Notify
                {
                  static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                  static constexpr ::ac::com::cpp_binding::Event_name name{"ethernetSensorFeaturesElement0.EVT"};
                  static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                  static constexpr bool updateOnSubscribe{true};
                  using SampleType = FieldType;
                  static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
                };
                struct Get
                {
                  static constexpr ::ac::com::cpp_binding::Method_id id{2u};
                  static constexpr ::ac::com::cpp_binding::Method_name name{"ethernetSensorFeaturesElement0.GET"};

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
                using FieldType = ::vwg::services::security::idspremiumservices::idsipnetworksensor::PeriodicSignalType;
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
                Fields::ethernetSensorFeaturesElement0::Notify::name,
                Fields::periodicSignalElement0::Notify::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,4u> get_methods_of_service_interface()
            {
              return
              {
                Methods::setEthernetSensorFeaturesElement0::name,
                Methods::undefineEthernetSensorFeaturesElement0::name,
                Fields::ethernetSensorFeaturesElement0::Get::name,
                Fields::periodicSignalElement0::Get::name
              };
            }
          };

          struct IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::Output
          {
            ::vwg::services::security::idspremiumservices::idsipnetworksensor::OperationStatus status{};
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

          struct IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::Output
          {
            ::vwg::services::security::idspremiumservices::idsipnetworksensor::OperationStatus status{};
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

        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif

