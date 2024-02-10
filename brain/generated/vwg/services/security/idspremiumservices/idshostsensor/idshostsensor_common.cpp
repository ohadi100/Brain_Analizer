/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/deployment/tlv/idshostsensor_transformation_props_set/periodicsignalelement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/deployment/tlv/idshostsensor_transformation_props_set/hostsensorfeatureselement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/deployment/tlv/idshostsensor_transformation_props_set/undefinehostsensorfeatureselement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/deployment/tlv/idshostsensor_transformation_props_set/sethostsensorfeatureselement0_transformation_props.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idspremiumservices
      {

        namespace idshostsensor
        {

          constexpr ::ac::com::cpp_binding::Method_id IdsHostSensor::Methods::setHostSensorFeaturesElement0::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsHostSensor::Methods::setHostSensorFeaturesElement0::name;

          constexpr ::ac::com::cpp_binding::Method_id IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::name;

          constexpr ::ac::com::cpp_binding::Event_id IdsHostSensor::Fields::hostSensorFeaturesElement0::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name IdsHostSensor::Fields::hostSensorFeaturesElement0::Notify::name;
          constexpr std::size_t IdsHostSensor::Fields::hostSensorFeaturesElement0::Notify::queueLength;
          constexpr bool IdsHostSensor::Fields::hostSensorFeaturesElement0::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IdsHostSensor::Fields::hostSensorFeaturesElement0::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsHostSensor::Fields::hostSensorFeaturesElement0::Get::name;

          constexpr ::ac::com::cpp_binding::Event_id IdsHostSensor::Fields::periodicSignalElement0::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name IdsHostSensor::Fields::periodicSignalElement0::Notify::name;
          constexpr std::size_t IdsHostSensor::Fields::periodicSignalElement0::Notify::queueLength;
          constexpr bool IdsHostSensor::Fields::periodicSignalElement0::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IdsHostSensor::Fields::periodicSignalElement0::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsHostSensor::Fields::periodicSignalElement0::Get::name;

          ::ara::core::ErrorCode IdsHostSensor::Methods::setHostSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsHostSensor::Methods::setHostSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IdsHostSensor::Methods::setHostSensorFeaturesElement0::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // element
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // HostSensorFeaturesSet
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // ConfigurationSettings
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
                // ConfigurationSettings_sensorIdentifier
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // uint16_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // uint64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                      }
                    }
                  }
                },
                // ConfigurationSettings_configurationData
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // ControlCommands
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // ControlCommands_sourceIdentifier
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // uint16_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // uint64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                      }
                    }
                  }
                },
                // uint16_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsHostSensor::Methods::setHostSensorFeaturesElement0::methodOutSProps()
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::setHostSensorFeaturesElement0_transformation_props,
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
          ::ara::core::ErrorCode IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // element
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // HostSensorFeaturesUndefine
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::undefineHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // bool
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::undefineHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                      }
                    }
                  }
                },
                // bool
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::undefineHostSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsHostSensor::Methods::undefineHostSensorFeaturesElement0::methodOutSProps()
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::undefineHostSensorFeaturesElement0_transformation_props,
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
          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsHostSensor::Fields::hostSensorFeaturesElement0::Notify::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_HostSensorFeaturesType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // IncidentData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // IncidentData_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // IncidentData_incidentData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ConfigurationSettings
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                    }
                  }
                }
              },
              // ConfigurationSettings_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // ConfigurationSettings_configurationData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ControlCommands
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                    }
                  }
                }
              },
              // ControlCommands_sourceIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                    }
                  }
                }
              },
              // ServiceApplicationNotification
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
              // ServiceApplicationNotification_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // ServiceApplicationNotification_registeredService
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 8
                    }
                  }
                }
              },
              // ServiceApplicationNotification_requestingApplicationIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ServiceApplicationNotification_requestingServerIpAddress
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // bool
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 6
                    }
                  }
                }
              },
              // ServiceApplicationNotification_errorInformation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WatchdogNotification
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // WatchdogNotification_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // WatchdogNotification_crashedInstanceName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // VmInstancePerfInfo
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // VmInstancePerfInfo_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // VmInstancePerfInfo_vmExits
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // VmInstancePerfInfo_processingTime
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // VmProcessPerfInfo
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 21
                    }
                  }
                }
              },
              // VmProcessPerfInfo_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // VmProcessPerfInfo_processId
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // VmProcessPerfInfo_processingTime
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 5
                    }
                  }
                }
              },
              // CriticalErrorInformation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                    }
                  }
                }
              },
              // CriticalErrorInformation_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                    }
                  }
                }
              },
              // CriticalErrorInformation_additionalInformation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // SecurityEventLogContents
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                    }
                  }
                }
              },
              // SecurityEventLogContents_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // SecurityEventLogContents_logFileContents
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ProcessStartStoppNotification
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 8
                    }
                  }
                }
              },
              // ProcessStartStoppNotification_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 4
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 5
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 6
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 7
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 8
                    }
                  }
                }
              },
              // ProcessStartStoppNotification_processCommandline
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 9
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ProcessStartStoppNotification_adaptiveAutosarApplicationName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 10
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 11
                    }
                  }
                }
              },
              // ExternalItemReceptionNotification
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 9
                    }
                  }
                }
              },
              // ExternalItemReceptionNotification_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // ExternalItemReceptionNotification_dataOrigin
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ExternalItemReceptionNotification_destinationApplicationName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 5
                    }
                  }
                }
              },
              // ExternalItemReceptionNotification_objectName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // CryptographicIncidentNotification
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 10
                    }
                  }
                }
              },
              // CryptographicIncidentNotification_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // CryptographicIncidentNotification_applicationName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                    }
                  }
                }
              },
              // CryptographicIncidentNotification_failureReason
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // HashMismatchNotification
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 11
                    }
                  }
                }
              },
              // HashMismatchNotification_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // HashMismatchNotification_fileNameList
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // TeeApplicationInvokation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 12
                    }
                  }
                }
              },
              // TeeApplicationInvokation_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // TeeApplicationInvokation_trustedApplicationName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // TeeApplicationInvokation_richOsInstanceName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // TeeApplicationInstallation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 13
                    }
                  }
                }
              },
              // TeeApplicationInstallation_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // TeeApplicationInstallation_applicationName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // TeeApplicationInstallation_applicationHash
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiConnectionSuccess
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 14
                    }
                  }
                }
              },
              // WifiConnectionSuccess_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // WifiConnectionSuccess_connectingUnitAddress
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiConnectionSuccess_suppliedIpv4Address
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiConnectionSuccess_suppliedIpv6Address
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiConnectionSuccess_connectingUnitDeviceName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiConnectionFailure
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 15
                    }
                  }
                }
              },
              // WifiConnectionFailure_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // WifiConnectionFailure_connectingUnitAddress
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                    }
                  }
                }
              },
              // WifiConnectionFailure_connectingUnitDeviceName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiNewBinding
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 16
                    }
                  }
                }
              },
              // WifiNewBinding_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // WifiNewBinding_objectName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiNewBinding_requestedConnectionName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // WifiUsageStatistics
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 17
                    }
                  }
                }
              },
              // WifiUsageStatistics_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 4
                    }
                  }
                }
              },
              // uint32_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 5
                    }
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 6
                    }
                  }
                }
              },
              // WifiClientArpMessage
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 18
                    }
                  }
                }
              },
              // WifiClientArpMessage_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // WifiClientArpMessage_packetPayload
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ExternalStorageConnection
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 19
                    }
                  }
                }
              },
              // ExternalStorageConnection_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // ExternalStorageConnection_serialNumber
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 5
                    }
                  }
                }
              },
              // ExternalStorageConnection_mainVolumeName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ExternalStorageConnection_volumesSizes
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ExternalHardwareConnection
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 20
                    }
                  }
                }
              },
              // ExternalHardwareConnection_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint16_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // ExternalHardwareConnection_serialNumber
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ExternalHardwareConnection_deviceClassesInformation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ExternalHardwareConnection_connectionHandlingInstanceName
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2047
                    }
                  }
                }
              },
            };
            return esprops;
          }

          ::ara::core::ErrorCode IdsHostSensor::Fields::hostSensorFeaturesElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsHostSensor::Fields::hostSensorFeaturesElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsHostSensor::Fields::hostSensorFeaturesElement0::Get::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // AT_HostSensorFeaturesType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // IncidentData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // IncidentData_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // IncidentData_incidentData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ConfigurationSettings
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // ConfigurationSettings_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // ConfigurationSettings_configurationData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ControlCommands
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                  }
                }
              },
              // ControlCommands_sourceIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                  }
                }
              },
              // ServiceApplicationNotification
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                  }
                }
              },
              // ServiceApplicationNotification_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // ServiceApplicationNotification_registeredService
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 8
                  }
                }
              },
              // ServiceApplicationNotification_requestingApplicationIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ServiceApplicationNotification_requestingServerIpAddress
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // bool
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 6
                  }
                }
              },
              // ServiceApplicationNotification_errorInformation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WatchdogNotification
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // WatchdogNotification_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // WatchdogNotification_crashedInstanceName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // VmInstancePerfInfo
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // VmInstancePerfInfo_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // VmInstancePerfInfo_vmExits
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                  }
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // VmInstancePerfInfo_processingTime
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // VmProcessPerfInfo
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 21
                  }
                }
              },
              // VmProcessPerfInfo_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // VmProcessPerfInfo_processId
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // VmProcessPerfInfo_processingTime
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 5
                  }
                }
              },
              // CriticalErrorInformation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                  }
                }
              },
              // CriticalErrorInformation_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                  }
                }
              },
              // CriticalErrorInformation_additionalInformation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // SecurityEventLogContents
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                  }
                }
              },
              // SecurityEventLogContents_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // SecurityEventLogContents_logFileContents
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ProcessStartStoppNotification
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 8
                  }
                }
              },
              // ProcessStartStoppNotification_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 4
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 5
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 6
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 7
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 8
                  }
                }
              },
              // ProcessStartStoppNotification_processCommandline
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 9
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ProcessStartStoppNotification_adaptiveAutosarApplicationName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 10
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 11
                  }
                }
              },
              // ExternalItemReceptionNotification
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 9
                  }
                }
              },
              // ExternalItemReceptionNotification_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // ExternalItemReceptionNotification_dataOrigin
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ExternalItemReceptionNotification_destinationApplicationName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 5
                  }
                }
              },
              // ExternalItemReceptionNotification_objectName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // CryptographicIncidentNotification
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 10
                  }
                }
              },
              // CryptographicIncidentNotification_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // CryptographicIncidentNotification_applicationName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                  }
                }
              },
              // CryptographicIncidentNotification_failureReason
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // HashMismatchNotification
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 11
                  }
                }
              },
              // HashMismatchNotification_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // HashMismatchNotification_fileNameList
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // TeeApplicationInvokation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 12
                  }
                }
              },
              // TeeApplicationInvokation_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // TeeApplicationInvokation_trustedApplicationName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // TeeApplicationInvokation_richOsInstanceName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // TeeApplicationInstallation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 13
                  }
                }
              },
              // TeeApplicationInstallation_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // TeeApplicationInstallation_applicationName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // TeeApplicationInstallation_applicationHash
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiConnectionSuccess
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 14
                  }
                }
              },
              // WifiConnectionSuccess_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // WifiConnectionSuccess_connectingUnitAddress
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiConnectionSuccess_suppliedIpv4Address
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiConnectionSuccess_suppliedIpv6Address
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiConnectionSuccess_connectingUnitDeviceName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiConnectionFailure
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 15
                  }
                }
              },
              // WifiConnectionFailure_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // WifiConnectionFailure_connectingUnitAddress
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                  }
                }
              },
              // WifiConnectionFailure_connectingUnitDeviceName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiNewBinding
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 16
                  }
                }
              },
              // WifiNewBinding_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // WifiNewBinding_objectName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiNewBinding_requestedConnectionName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // WifiUsageStatistics
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 17
                  }
                }
              },
              // WifiUsageStatistics_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 4
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 5
                  }
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 6
                  }
                }
              },
              // WifiClientArpMessage
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 18
                  }
                }
              },
              // WifiClientArpMessage_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // WifiClientArpMessage_packetPayload
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ExternalStorageConnection
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 19
                  }
                }
              },
              // ExternalStorageConnection_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // ExternalStorageConnection_serialNumber
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 5
                  }
                }
              },
              // ExternalStorageConnection_mainVolumeName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 6
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ExternalStorageConnection_volumesSizes
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 7
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ExternalHardwareConnection
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 20
                  }
                }
              },
              // ExternalHardwareConnection_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // ExternalHardwareConnection_serialNumber
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ExternalHardwareConnection_deviceClassesInformation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ExternalHardwareConnection_connectionHandlingInstanceName
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::hostSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2047
                  }
                }
              },
            };
            return mosprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsHostSensor::Fields::periodicSignalElement0::Notify::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_PeriodicSignalType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // CycleCounter
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 0
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2047
                    }
                  }
                }
              },
            };
            return esprops;
          }

          ::ara::core::ErrorCode IdsHostSensor::Fields::periodicSignalElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsHostSensor::Fields::periodicSignalElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsHostSensor::Fields::periodicSignalElement0::Get::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // AT_PeriodicSignalType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // CycleCounter
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 0
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idshostsensor::deployment::tlv::idshostsensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2047
                  }
                }
              },
            };
            return mosprops;
          }
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
