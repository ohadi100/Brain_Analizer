/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idssecurityevent/idssecurityevent/idssecurityevent_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/deployment/tlv/idssecurityevent_transformation_props_set/getsecurityeventelementbykey_transformation_props.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/deployment/tlv/idssecurityevent_transformation_props_set/getsecurityeventelements_transformation_props.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/deployment/tlv/idssecurityevent_transformation_props_set/subscribesecurityevent_transformation_props.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/deployment/tlv/idssecurityevent_transformation_props_set/securityeventevent_transformation_props.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/deployment/tlv/idssecurityevent_transformation_props_set/subscribesecurityeventbykey_transformation_props.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/deployment/tlv/idssecurityevent_transformation_props_set/unsubscribesecurityevent_transformation_props.h"

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

          constexpr ::ac::com::cpp_binding::Event_id IDSSecurityEvent::Events::securityEventEvent::id;
          constexpr ::ac::com::cpp_binding::Event_name IDSSecurityEvent::Events::securityEventEvent::name;
          constexpr std::size_t IDSSecurityEvent::Events::securityEventEvent::queueLength;
          constexpr bool IDSSecurityEvent::Events::securityEventEvent::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IDSSecurityEvent::Methods::getSecurityEventElementByKey::id;
          constexpr ::ac::com::cpp_binding::Method_name IDSSecurityEvent::Methods::getSecurityEventElementByKey::name;

          constexpr ::ac::com::cpp_binding::Method_id IDSSecurityEvent::Methods::getSecurityEventElements::id;
          constexpr ::ac::com::cpp_binding::Method_name IDSSecurityEvent::Methods::getSecurityEventElements::name;

          constexpr ::ac::com::cpp_binding::Method_id IDSSecurityEvent::Methods::subscribeSecurityEvent::id;
          constexpr ::ac::com::cpp_binding::Method_name IDSSecurityEvent::Methods::subscribeSecurityEvent::name;

          constexpr ::ac::com::cpp_binding::Method_id IDSSecurityEvent::Methods::subscribeSecurityEventByKey::id;
          constexpr ::ac::com::cpp_binding::Method_name IDSSecurityEvent::Methods::subscribeSecurityEventByKey::name;

          constexpr ::ac::com::cpp_binding::Method_id IDSSecurityEvent::Methods::unsubscribeSecurityEvent::id;
          constexpr ::ac::com::cpp_binding::Method_name IDSSecurityEvent::Methods::unsubscribeSecurityEvent::name;

          ::ac::com::someip::serialization::Serialization_attributes const&
          IDSSecurityEvent::Events::securityEventEvent::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_SecurityEventEvent
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 0
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 5
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 6
                    }
                  }
                }
              },
              // SecurityEventType
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                    }
                  }
                }
              },
              // DT_uuid
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
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
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // SecurityEventType_eventFrame
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // SecurityEventType_timestamp
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // SecurityEventType_contextData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::securityEventEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
            };
            return esprops;
          }

          ::ara::core::ErrorCode IDSSecurityEvent::Methods::getSecurityEventElementByKey::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IDSSecurityEvent::Methods::getSecurityEventElementByKey::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IDSSecurityEvent::Methods::getSecurityEventElementByKey::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // key
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // DT_uuid
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
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
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
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
          IDSSecurityEvent::Methods::getSecurityEventElementByKey::methodOutSProps()
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
              // securityEventResponseSingle
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 0
                  }
                }
              },
              // SecurityEventType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // DT_uuid
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventType_eventFrame
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventType_timestamp
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventType_contextData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElementByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode IDSSecurityEvent::Methods::getSecurityEventElements::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IDSSecurityEvent::Methods::getSecurityEventElements::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IDSSecurityEvent::Methods::getSecurityEventElements::methodOutSProps()
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
              // SecurityEventResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 0
                  }
                }
              },
              // SecurityEventVector
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // SecurityEventType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // DT_uuid
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventType_eventFrame
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventType_timestamp
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventType_contextData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::getSecurityEventElements_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode IDSSecurityEvent::Methods::subscribeSecurityEvent::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IDSSecurityEvent::Methods::subscribeSecurityEvent::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          IDSSecurityEvent::Methods::subscribeSecurityEvent::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // initialEventRequired
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // bool
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEvent_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                      }
                    }
                  }
                },
              },
              // consumerId
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // DT_uuid
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEvent_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEvent_transformation_props,
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
          IDSSecurityEvent::Methods::subscribeSecurityEvent::methodOutSProps()
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
              // IDSSecurityEventSubscriptionResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 0
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode IDSSecurityEvent::Methods::subscribeSecurityEventByKey::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IDSSecurityEvent::Methods::subscribeSecurityEventByKey::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const&
          IDSSecurityEvent::Methods::subscribeSecurityEventByKey::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const misprops
            {
              // key
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // DT_uuid
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
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
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
              },
              // initialEventRequired
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // bool
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                      }
                    }
                  }
                },
              },
              // consumerId
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // DT_uuid
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
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
          IDSSecurityEvent::Methods::subscribeSecurityEventByKey::methodOutSProps()
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
              // IDSSecurityEventSubscriptionResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 0
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::subscribeSecurityEventByKey_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode IDSSecurityEvent::Methods::unsubscribeSecurityEvent::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IDSSecurityEvent::Methods::unsubscribeSecurityEvent::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          IDSSecurityEvent::Methods::unsubscribeSecurityEvent::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // subscriptionId
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint32_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::unsubscribeSecurityEvent_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 0
                      }
                    }
                  }
                },
              },
              // consumerId
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // DT_uuid
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::unsubscribeSecurityEvent_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::unsubscribeSecurityEvent_transformation_props,
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
          IDSSecurityEvent::Methods::unsubscribeSecurityEvent::methodOutSProps()
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
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityevent::deployment::tlv::idssecurityevent_transformation_props_set::unsubscribeSecurityEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 0
                  }
                }
              },
            };
            return mosprops;
          }
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
