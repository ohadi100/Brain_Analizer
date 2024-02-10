/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/connect/gsdp/healthincidentprovider/deployment/tlv/healthincidentprovider_transformation_props_set/requestincidents_transformation_props.h"
#include "vwg/services/connect/gsdp/healthincidentprovider/deployment/tlv/healthincidentprovider_transformation_props_set/getlastincidents_transformation_props.h"
#include "vwg/services/connect/gsdp/healthincidentprovider/deployment/tlv/healthincidentprovider_transformation_props_set/configureincidentevent_transformation_props.h"
#include "vwg/services/connect/gsdp/healthincidentprovider/deployment/tlv/healthincidentprovider_transformation_props_set/incident_transformation_props.h"

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

          constexpr ::ac::com::cpp_binding::Event_id HealthIncidentProvider::Events::incident::id;
          constexpr ::ac::com::cpp_binding::Event_name HealthIncidentProvider::Events::incident::name;
          constexpr std::size_t HealthIncidentProvider::Events::incident::queueLength;
          constexpr bool HealthIncidentProvider::Events::incident::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id HealthIncidentProvider::Methods::configureIncidentEvent::id;
          constexpr ::ac::com::cpp_binding::Method_name HealthIncidentProvider::Methods::configureIncidentEvent::name;

          constexpr ::ac::com::cpp_binding::Method_id HealthIncidentProvider::Methods::getLastIncidents::id;
          constexpr ::ac::com::cpp_binding::Method_name HealthIncidentProvider::Methods::getLastIncidents::name;

          constexpr ::ac::com::cpp_binding::Method_id HealthIncidentProvider::Methods::requestIncidents::id;
          constexpr ::ac::com::cpp_binding::Method_name HealthIncidentProvider::Methods::requestIncidents::name;

          constexpr ::ac::com::cpp_binding::Event_id HealthIncidentProvider::Fields::openIncidents::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name HealthIncidentProvider::Fields::openIncidents::Notify::name;
          constexpr std::size_t HealthIncidentProvider::Fields::openIncidents::Notify::queueLength;
          constexpr bool HealthIncidentProvider::Fields::openIncidents::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id HealthIncidentProvider::Fields::openIncidents::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name HealthIncidentProvider::Fields::openIncidents::Get::name;

          ::ac::com::someip::serialization::Serialization_attributes_entry const&
          HealthIncidentProvider::Events::incident::eventSProps()
          {
            static ::ac::com::someip::serialization::Serialization_attributes_entry const esprops
            {
              ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::incident_transformation_props,
              ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
            };
            return esprops;
          }

          ::ara::core::ErrorCode HealthIncidentProvider::Methods::configureIncidentEvent::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode HealthIncidentProvider::Methods::configureIncidentEvent::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          HealthIncidentProvider::Methods::configureIncidentEvent::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // query
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::configureIncidentEvent_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          HealthIncidentProvider::Methods::configureIncidentEvent::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // Output structure
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::ac::com::someip::serialization::defaults::method_output_properties(),
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // bool
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::configureIncidentEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode HealthIncidentProvider::Methods::getLastIncidents::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode HealthIncidentProvider::Methods::getLastIncidents::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          HealthIncidentProvider::Methods::getLastIncidents::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // lastIncidentId
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // DT_uuid
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::getLastIncidents_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::getLastIncidents_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          HealthIncidentProvider::Methods::getLastIncidents::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // Output structure
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::ac::com::someip::serialization::defaults::method_output_properties(),
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // String
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::getLastIncidents_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode HealthIncidentProvider::Methods::requestIncidents::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode HealthIncidentProvider::Methods::requestIncidents::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          HealthIncidentProvider::Methods::requestIncidents::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // query
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::requestIncidents_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          HealthIncidentProvider::Methods::requestIncidents::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // Output structure
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::ac::com::someip::serialization::defaults::method_output_properties(),
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // String
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::gsdp::healthincidentprovider::deployment::tlv::healthincidentprovider_transformation_props_set::requestIncidents_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode HealthIncidentProvider::Fields::openIncidents::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode HealthIncidentProvider::Fields::openIncidents::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
