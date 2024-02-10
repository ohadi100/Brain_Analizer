/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/datacollector/odcagentgenericlarge/odcagentgenericlarge_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/services/connect/datacollector/odcagentgenericlarge/deployment/tlv/odcagentgenericlarge_transformation_props_set/control_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentgenericlarge/deployment/tlv/odcagentgenericlarge_transformation_props_set/data_transformation_props.h"

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace datacollector
      {

        namespace odcagentgenericlarge
        {

          constexpr ::ac::com::cpp_binding::Event_id OdcAgentGenericLarge::Events::data::id;
          constexpr ::ac::com::cpp_binding::Event_name OdcAgentGenericLarge::Events::data::name;
          constexpr std::size_t OdcAgentGenericLarge::Events::data::queueLength;
          constexpr bool OdcAgentGenericLarge::Events::data::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentGenericLarge::Methods::control::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentGenericLarge::Methods::control::name;

          ::ac::com::someip::serialization::Serialization_attributes const&
          OdcAgentGenericLarge::Events::data::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_OdcAgentGenericLarge_data_eventData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                    }
                  }
                }
              },
              // Data
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                    }
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 0
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                    }
                  }
                }
              },
              // Data_value
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
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
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ChunkInfo
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::data_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 1
                    }
                  }
                }
              },
            };
            return esprops;
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          OdcAgentGenericLarge::Methods::control::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // controlInfo
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ControlInfo
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::control_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // bool
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::control_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentgenericlarge::deployment::tlv::odcagentgenericlarge_transformation_props_set::control_transformation_props,
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
            };
            return misprops;
          }
        } // namespace odcagentgenericlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
