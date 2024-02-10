/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/deployment/tlv/idssecurityeventsmall_transformation_props_set/securityevent_transformation_props.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idssecurityevent
      {

        namespace idssecurityeventsmall
        {

          constexpr ::ac::com::cpp_binding::Event_id IDSSecurityEventSmall::Events::securityEvent::id;
          constexpr ::ac::com::cpp_binding::Event_name IDSSecurityEventSmall::Events::securityEvent::name;
          constexpr std::size_t IDSSecurityEventSmall::Events::securityEvent::queueLength;
          constexpr bool IDSSecurityEventSmall::Events::securityEvent::updateOnSubscribe;

          ::ac::com::someip::serialization::Serialization_attributes const&
          IDSSecurityEventSmall::Events::securityEvent::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_SecurityEventStruct
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // SecurityEventStruct_eventFrame
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
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
                  ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // SecurityEventStruct_timestamp
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
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
                  ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // SecurityEventStruct_contextData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
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
                  ::vwg::services::security::idssecurityevent::idssecurityeventsmall::deployment::tlv::idssecurityeventsmall_transformation_props_set::securityEvent_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
            };
            return esprops;
          }

        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
