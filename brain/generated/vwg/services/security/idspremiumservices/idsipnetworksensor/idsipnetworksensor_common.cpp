/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/idsipnetworksensor_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/deployment/tlv/idsipnetworksensor_transformation_props_set/periodicsignalelement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/deployment/tlv/idsipnetworksensor_transformation_props_set/ethernetsensorfeatureselement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/deployment/tlv/idsipnetworksensor_transformation_props_set/undefineethernetsensorfeatureselement0_transformation_props.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/deployment/tlv/idsipnetworksensor_transformation_props_set/setethernetsensorfeatureselement0_transformation_props.h"

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

          constexpr ::ac::com::cpp_binding::Method_id IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::name;

          constexpr ::ac::com::cpp_binding::Method_id IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::name;

          constexpr ::ac::com::cpp_binding::Event_id IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Notify::name;
          constexpr std::size_t IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Notify::queueLength;
          constexpr bool IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Get::name;

          constexpr ::ac::com::cpp_binding::Event_id IdsIpNetworkSensor::Fields::periodicSignalElement0::Notify::id;
          constexpr ::ac::com::cpp_binding::Event_name IdsIpNetworkSensor::Fields::periodicSignalElement0::Notify::name;
          constexpr std::size_t IdsIpNetworkSensor::Fields::periodicSignalElement0::Notify::queueLength;
          constexpr bool IdsIpNetworkSensor::Fields::periodicSignalElement0::Notify::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id IdsIpNetworkSensor::Fields::periodicSignalElement0::Get::id;
          constexpr ::ac::com::cpp_binding::Method_name IdsIpNetworkSensor::Fields::periodicSignalElement0::Get::name;

          ::ara::core::ErrorCode IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // element
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // EthernetSensorFeaturesSet
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // uint64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // ControlCommands
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
                // uint64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
          IdsIpNetworkSensor::Methods::setEthernetSensorFeaturesElement0::methodOutSProps()
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::setEthernetSensorFeaturesElement0_transformation_props,
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
          ::ara::core::ErrorCode IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // element
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // EthernetSensorFeaturesUndefine
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::undefineEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::undefineEthernetSensorFeaturesElement0_transformation_props,
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
                    ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::undefineEthernetSensorFeaturesElement0_transformation_props,
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
          IdsIpNetworkSensor::Methods::undefineEthernetSensorFeaturesElement0::methodOutSProps()
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::undefineEthernetSensorFeaturesElement0_transformation_props,
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
          IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Notify::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_EthernetSensorFeaturesType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // IncidentData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ConfigurationSettings
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // ControlCommands
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                    }
                  }
                }
              },
              // FirewallData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
              // FirewallData_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                    }
                  }
                }
              },
              // FirewallData_ipAddresses
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_ipPorts
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_connectionStatus
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_connectionIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_stateInformation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_decodedPayloadData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 8
                    }
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_preventionActionPerformed
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // FirewallData_payloadData
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 11
                    }
                  }
                }
              },
              // IpVersionViolation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                    }
                  }
                }
              },
              // IpVersionViolation_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                    }
                  }
                }
              },
              // ProtocolCategoryViolation
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                    }
                  }
                }
              },
              // ProtocolCategoryViolation_sensorIdentifier
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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

          ::ara::core::ErrorCode IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsIpNetworkSensor::Fields::ethernetSensorFeaturesElement0::Get::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // AT_EthernetSensorFeaturesType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // IncidentData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ConfigurationSettings
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ControlCommands
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                  }
                }
              },
              // FirewallData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                  }
                }
              },
              // FirewallData_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                  }
                }
              },
              // FirewallData_ipAddresses
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_ipPorts
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_connectionStatus
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_connectionIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_stateInformation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_decodedPayloadData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 8
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_preventionActionPerformed
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // FirewallData_payloadData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 11
                  }
                }
              },
              // IpVersionViolation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
              // IpVersionViolation_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 2
                  }
                }
              },
              // ProtocolCategoryViolation
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 5
                  }
                }
              },
              // ProtocolCategoryViolation_sensorIdentifier
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::ethernetSensorFeaturesElement0_transformation_props,
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
          IdsIpNetworkSensor::Fields::periodicSignalElement0::Notify::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_PeriodicSignalType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // CycleCounter
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                  ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
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

          ::ara::core::ErrorCode IdsIpNetworkSensor::Fields::periodicSignalElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode IdsIpNetworkSensor::Fields::periodicSignalElement0::Get::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          IdsIpNetworkSensor::Fields::periodicSignalElement0::Get::methodOutSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const mosprops
            {
              // AT_PeriodicSignalType
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // CycleCounter
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
                ::vwg::services::security::idspremiumservices::idsipnetworksensor::deployment::tlv::idsipnetworksensor_transformation_props_set::periodicSignalElement0_transformation_props,
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
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
