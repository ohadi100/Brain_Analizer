/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/connect/datacollector/odcagentcommonlarge/odcagentcommonlarge_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/estimatecampaign_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/getcampaigns_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/setdata_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/addcampaign_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/getinfo_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/getdata_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/event_transformation_props.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/deployment/tlv/odcagentcommonlarge_transformation_props_set/removecampaign_transformation_props.h"

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace datacollector
      {

        namespace odcagentcommonlarge
        {

          constexpr ::ac::com::cpp_binding::Event_id OdcAgentCommonLarge::Events::event::id;
          constexpr ::ac::com::cpp_binding::Event_name OdcAgentCommonLarge::Events::event::name;
          constexpr std::size_t OdcAgentCommonLarge::Events::event::queueLength;
          constexpr bool OdcAgentCommonLarge::Events::event::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::addCampaign::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::addCampaign::name;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::estimateCampaign::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::estimateCampaign::name;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::getCampaigns::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::getCampaigns::name;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::getData::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::getData::name;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::getInfo::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::getInfo::name;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::removeCampaign::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::removeCampaign::name;

          constexpr ::ac::com::cpp_binding::Method_id OdcAgentCommonLarge::Methods::setData::id;
          constexpr ::ac::com::cpp_binding::Method_name OdcAgentCommonLarge::Methods::setData::name;

          ::ac::com::someip::serialization::Serialization_attributes const&
          OdcAgentCommonLarge::Events::event::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_Event
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::event_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // uint8_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::event_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                    }
                  }
                }
              },
              // String
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::event_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                    }
                  }
                }
              },
              // Timestamp
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::event_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                    }
                  }
                }
              },
              // uint64_t
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::event_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 0
                    }
                  }
                }
              },
              // String
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::event_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                    }
                  }
                }
              },
            };
            return esprops;
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::addCampaign::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::addCampaign::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          OdcAgentCommonLarge::Methods::addCampaign::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // request
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // AddCampaignRequest
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // Signature
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // Campaign
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // Campaign_data
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
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
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
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
          OdcAgentCommonLarge::Methods::addCampaign::methodOutSProps()
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
              // CampaignOpResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // ResourceVector
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // ResourceVector_data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // Resource
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::addCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::estimateCampaign::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::estimateCampaign::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          OdcAgentCommonLarge::Methods::estimateCampaign::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // campaign
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // Campaign
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // Campaign_data
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
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
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
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
          OdcAgentCommonLarge::Methods::estimateCampaign::methodOutSProps()
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
              // CampaignOpResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // ResourceVector
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // ResourceVector_data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // Resource
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::estimateCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::getCampaigns::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::getCampaigns::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          OdcAgentCommonLarge::Methods::getCampaigns::methodOutSProps()
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
              // GetCampaignsResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // GetCampaignsResponse_uuids
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // String
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // ResourceVector
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // ResourceVector_data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // Resource
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getCampaigns_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::getData::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::getData::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          OdcAgentCommonLarge::Methods::getData::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // resource
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getData_transformation_props,
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
          OdcAgentCommonLarge::Methods::getData::methodOutSProps()
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
              // GetDataResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getData_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getData_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // Data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getData_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // Data_data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getData_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getData_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::getInfo::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::getInfo::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          OdcAgentCommonLarge::Methods::getInfo::methodOutSProps()
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
              // GetInfoResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 0
                  }
                }
              },
              // Version
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
              // uint16_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 2
                  }
                }
              },
              // ResourceVector
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                  }
                }
              },
              // ResourceVector_data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // Resource
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::getInfo_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::removeCampaign::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::removeCampaign::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          OdcAgentCommonLarge::Methods::removeCampaign::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // uuid
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
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
          OdcAgentCommonLarge::Methods::removeCampaign::methodOutSProps()
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
              // CampaignOpResponse
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
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
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // ResourceVector
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // ResourceVector_data
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                  }
                }
              },
              // Resource
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                  }
                }
              },
              // uint32_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::removeCampaign_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::setData::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode OdcAgentCommonLarge::Methods::setData::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const&
          OdcAgentCommonLarge::Methods::setData::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 1> const misprops
            {
              // request
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // SetDataRequest
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::setData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 0
                      }
                    }
                  }
                },
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::setData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // Data
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::setData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
                // Data_data
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::setData_transformation_props,
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
                    ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::setData_transformation_props,
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
          OdcAgentCommonLarge::Methods::setData::methodOutSProps()
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
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::connect::datacollector::odcagentcommonlarge::deployment::tlv::odcagentcommonlarge_transformation_props_set::setData_transformation_props,
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
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
