/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/security/idspremiumservices/idscansensor/deployment/tlv/idscansensor_transformation_props_set/periodicsignalelement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idscansensor/deployment/tlv/idscansensor_transformation_props_set/undefinecansensorfeatureselement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idscansensor/deployment/tlv/idscansensor_transformation_props_set/cansensorfeatureselement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idscansensor/deployment/tlv/idscansensor_transformation_props_set/setcansensorfeatureselement0_transformation_props.h"

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

          constexpr ::ac::com::cpp_binding::Method_id IdsCanSensor::Methods::setCanSensorFeaturesElement0::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsCanSensor::Methods::setCanSensorFeaturesElement0::name;

          constexpr ::ac::com::cpp_binding::Method_id IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::name;

          constexpr ::ac::com::cpp_binding::Event_id IdsCanSensor::Fields::canSensorFeaturesElement0::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name IdsCanSensor::Fields::canSensorFeaturesElement0::Notify::name;
          constexpr std::size_t IdsCanSensor::Fields::canSensorFeaturesElement0::Notify::queueLength;
          constexpr bool IdsCanSensor::Fields::canSensorFeaturesElement0::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IdsCanSensor::Fields::canSensorFeaturesElement0::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsCanSensor::Fields::canSensorFeaturesElement0::Get::name;

          constexpr ::ac::com::cpp_binding::Event_id IdsCanSensor::Fields::periodicSignalElement0::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name IdsCanSensor::Fields::periodicSignalElement0::Notify::name;
          constexpr std::size_t IdsCanSensor::Fields::periodicSignalElement0::Notify::queueLength;
          constexpr bool IdsCanSensor::Fields::periodicSignalElement0::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IdsCanSensor::Fields::periodicSignalElement0::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsCanSensor::Fields::periodicSignalElement0::Get::name;

          ::ara::core::ErrorCode IdsCanSensor::Methods::setCanSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsCanSensor::Methods::setCanSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IdsCanSensor::Methods::setCanSensorFeaturesElement0::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // element
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // CanSensorFeaturesSet
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // ConfigurationSettings_sensorIdentifier
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // uint64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
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
          IdsCanSensor::Methods::setCanSensorFeaturesElement0::methodOutSProps()
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::setCanSensorFeaturesElement0_transformation_props,
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
          ::ara::core::ErrorCode IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // element
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // CanSensorFeaturesUndefine
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::undefineCanSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::undefineCanSensorFeaturesElement0_transformation_props,
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
          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsCanSensor::Methods::undefineCanSensorFeaturesElement0::methodOutSProps()
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::undefineCanSensorFeaturesElement0_transformation_props,
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
          IdsCanSensor::Fields::canSensorFeaturesElement0::Notify::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_CanSensorFeaturesType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // ConfigurationSettings
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                    }
                  }
                }
              },
              // ConfigurationSettings_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ControlCommands
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // ControlCommands_sourceIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                    }
                  }
                }
              },
              // ProtocolFrameData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                    }
                  }
                }
              },
              // ProtocolFrameData_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // ProtocolFrameData_protocolFrameContents
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // AnomalyData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                    }
                  }
                }
              },
              // AnomalyData_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                    }
                  }
                }
              },
              // AnomalyData_messagePayload
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // GatewayExceptionalData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
              // GatewayExceptionalData_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                    }
                  }
                }
              },
              // GatewayExceptionalData_messagePayload
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // GatewayDiagnosticFilterEvent
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // GatewayDiagnosticFilterEvent_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                    }
                  }
                }
              },
              // bool
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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

          ::ara::core::ErrorCode IdsCanSensor::Fields::canSensorFeaturesElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsCanSensor::Fields::canSensorFeaturesElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsCanSensor::Fields::canSensorFeaturesElement0::Get::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // AT_CanSensorFeaturesType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // ConfigurationSettings
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // ConfigurationSettings_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ControlCommands
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // ControlCommands_sourceIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                  }
                }
              },
              // ProtocolFrameData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // ProtocolFrameData_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // ProtocolFrameData_protocolFrameContents
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // AnomalyData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                  }
                }
              },
              // AnomalyData_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                  }
                }
              },
              // AnomalyData_messagePayload
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // GatewayExceptionalData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                  }
                }
              },
              // GatewayExceptionalData_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                  }
                }
              },
              // GatewayExceptionalData_messagePayload
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // GatewayDiagnosticFilterEvent
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // GatewayDiagnosticFilterEvent_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 1
                  }
                }
              },
              // bool
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::canSensorFeaturesElement0_transformation_props,
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
          IdsCanSensor::Fields::periodicSignalElement0::Notify::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_PeriodicSignalType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // CycleCounter
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
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

          ::ara::core::ErrorCode IdsCanSensor::Fields::periodicSignalElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsCanSensor::Fields::periodicSignalElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsCanSensor::Fields::periodicSignalElement0::Get::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // AT_PeriodicSignalType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // CycleCounter
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idscansensor::deployment::tlv::idscansensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
