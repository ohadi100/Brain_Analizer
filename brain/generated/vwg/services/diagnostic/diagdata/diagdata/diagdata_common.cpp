/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
#include "vwg/services/diagnostic/diagdata/diagdata/diagdata_common.h"
#include "ac/com/someip/serialization/defaults.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestsetdiagdata_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/getdiagdatabygroups_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestdiagdataonthreshold_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/getdiagdatabykeys_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/senddiagcontrolcommandresponse_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/responseready_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestsampleddiagdata_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/senddiagcontrolcommandrequest_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestdiagdatabygroups_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/updateavailable_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/cancelrequest_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/getdiagassemblystatus_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/getdiagassemblystatushash_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestdiagassemblystatusonchange_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/readrequestedresults_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestdiagdatabykeys_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/requestdiagdataonchange_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/assemblystatusupdate_transformation_props.h"
#include "vwg/services/diagnostic/diagdata/diagdata/deployment/tlv/diagdata_transformation_props_set/refreshassemblystatus_transformation_props.h"

namespace vwg
{

  namespace services
  {

    namespace diagnostic
    {

      namespace diagdata
      {

        namespace diagdata
        {

          constexpr ::ac::com::cpp_binding::Event_id DiagData::Events::assemblyStatusReady::id;
          constexpr ::ac::com::cpp_binding::Event_name DiagData::Events::assemblyStatusReady::name;
          constexpr std::size_t DiagData::Events::assemblyStatusReady::queueLength;
          constexpr bool DiagData::Events::assemblyStatusReady::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Event_id DiagData::Events::assemblyStatusUpdate::id;
          constexpr ::ac::com::cpp_binding::Event_name DiagData::Events::assemblyStatusUpdate::name;
          constexpr std::size_t DiagData::Events::assemblyStatusUpdate::queueLength;
          constexpr bool DiagData::Events::assemblyStatusUpdate::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Event_id DiagData::Events::responseReady::id;
          constexpr ::ac::com::cpp_binding::Event_name DiagData::Events::responseReady::name;
          constexpr std::size_t DiagData::Events::responseReady::queueLength;
          constexpr bool DiagData::Events::responseReady::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Event_id DiagData::Events::sendDiagControlCommandResponse::id;
          constexpr ::ac::com::cpp_binding::Event_name DiagData::Events::sendDiagControlCommandResponse::name;
          constexpr std::size_t DiagData::Events::sendDiagControlCommandResponse::queueLength;
          constexpr bool DiagData::Events::sendDiagControlCommandResponse::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Event_id DiagData::Events::updateAvailable::id;
          constexpr ::ac::com::cpp_binding::Event_name DiagData::Events::updateAvailable::name;
          constexpr std::size_t DiagData::Events::updateAvailable::queueLength;
          constexpr bool DiagData::Events::updateAvailable::updateOnSubscribe;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::cancelRequest::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::cancelRequest::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::getDiagAssemblyStatus::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::getDiagAssemblyStatus::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::getDiagAssemblyStatusHash::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::getDiagAssemblyStatusHash::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::getDiagDataByGroups::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::getDiagDataByGroups::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::getDiagDataByKeys::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::getDiagDataByKeys::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::readRequestedResults::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::readRequestedResults::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::refreshAssemblyStatus::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::refreshAssemblyStatus::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestDiagAssemblyStatusOnChange::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestDiagAssemblyStatusOnChange::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestDiagDataByGroups::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestDiagDataByGroups::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestDiagDataByKeys::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestDiagDataByKeys::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestDiagDataOnChange::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestDiagDataOnChange::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestDiagDataOnThreshold::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestDiagDataOnThreshold::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestSampledDiagData::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestSampledDiagData::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::requestSetDiagData::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::requestSetDiagData::name;

          constexpr ::ac::com::cpp_binding::Method_id DiagData::Methods::sendDiagControlCommandRequest::id;
          constexpr ::ac::com::cpp_binding::Method_name DiagData::Methods::sendDiagControlCommandRequest::name;

          ::ac::com::someip::serialization::Serialization_attributes_entry const&
          DiagData::Events::assemblyStatusUpdate::eventSProps()
          {
            static ::ac::com::someip::serialization::Serialization_attributes_entry const esprops
            {
              ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::assemblyStatusUpdate_transformation_props,
              ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
            };
            return esprops;
          }

          ::ac::com::someip::serialization::Serialization_attributes_entry const&
          DiagData::Events::responseReady::eventSProps()
          {
            static ::ac::com::someip::serialization::Serialization_attributes_entry const esprops
            {
              ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::responseReady_transformation_props,
              ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
            };
            return esprops;
          }

          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Events::sendDiagControlCommandResponse::eventSProps()
          {
            // AXIVION AutosarC++18_10-A3.3.2: Initialization without side effects
            static ::ac::com::someip::serialization::Serialization_attributes const esprops
            {
              // AT_DiagData_sendDiagControlCommandResponse_eventData
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandResponse_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
              },
              // String
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandResponse_transformation_props,
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
                  ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandResponse_transformation_props,
                  ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                  {
                    ::ac::com::someip::serialization::Structure_tag
                    {
                      ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                    }
                  }
                }
              },
              // String
              {
                ::ac::com::someip::serialization::Serialization_attributes_entry
                {
                  ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandResponse_transformation_props,
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

          ::ac::com::someip::serialization::Serialization_attributes_entry const&
          DiagData::Events::updateAvailable::eventSProps()
          {
            static ::ac::com::someip::serialization::Serialization_attributes_entry const esprops
            {
              ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::updateAvailable_transformation_props,
              ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>{}
            };
            return esprops;
          }

          ::ara::core::ErrorCode DiagData::Methods::cancelRequest::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::cancelRequest::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          DiagData::Methods::cancelRequest::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::cancelRequest_transformation_props,
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
              // requestID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::cancelRequest_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::cancelRequest::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::cancelRequest_transformation_props,
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
          ::ara::core::ErrorCode DiagData::Methods::getDiagAssemblyStatus::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::getDiagAssemblyStatus::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          DiagData::Methods::getDiagAssemblyStatus::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
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
              // requestOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // RequestOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                      }
                    }
                  }
                },
                // RequestOptions_diagNodes
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
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
          DiagData::Methods::getDiagAssemblyStatus::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 2
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatus_transformation_props,
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
          ::ara::core::ErrorCode DiagData::Methods::getDiagAssemblyStatusHash::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::getDiagAssemblyStatusHash::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          DiagData::Methods::getDiagAssemblyStatusHash::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
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
              // requestOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // RequestOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                      }
                    }
                  }
                },
                // RequestOptions_diagNodes
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
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
          DiagData::Methods::getDiagAssemblyStatusHash::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                  }
                }
              },
              // uint64_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 2
                  }
                }
              },
              // uint8_t
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagAssemblyStatusHash_transformation_props,
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
          ::ara::core::ErrorCode DiagData::Methods::getDiagDataByGroups::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::getDiagDataByGroups::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 5> const&
          DiagData::Methods::getDiagDataByGroups::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 5> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
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
              // diagDataGroupKeys
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // getDiagDataByGroups_diagDataGroupKeys
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
              },
              // rootNode
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
              // timeout
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint32_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::getDiagDataByGroups::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByGroups_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::getDiagDataByKeys::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::getDiagDataByKeys::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 4> const&
          DiagData::Methods::getDiagDataByKeys::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 4> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
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
              // diagDataKeys
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // getDiagDataByKeys_diagDataKeys
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
              // timeout
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint32_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::getDiagDataByKeys::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::getDiagDataByKeys_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::readRequestedResults::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::readRequestedResults::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          DiagData::Methods::readRequestedResults::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::readRequestedResults_transformation_props,
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
              // requestID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::readRequestedResults_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::readRequestedResults::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::readRequestedResults_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::readRequestedResults_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::refreshAssemblyStatus::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::refreshAssemblyStatus::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          DiagData::Methods::refreshAssemblyStatus::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::refreshAssemblyStatus_transformation_props,
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
              // diagNodes
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // refreshAssemblyStatus_diagNodes
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::refreshAssemblyStatus_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::refreshAssemblyStatus_transformation_props,
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
          DiagData::Methods::refreshAssemblyStatus::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::refreshAssemblyStatus_transformation_props,
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
          ::ara::core::ErrorCode DiagData::Methods::requestDiagAssemblyStatusOnChange::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestDiagAssemblyStatusOnChange::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const&
          DiagData::Methods::requestDiagAssemblyStatusOnChange::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 2> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
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
              // requestOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // RequestOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 0
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                      }
                    }
                  }
                },
                // RequestOptions_diagNodes
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
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
          DiagData::Methods::requestDiagAssemblyStatusOnChange::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                  }
                }
              },
              // String
              ::ac::com::someip::serialization::Serialization_attributes_entry
              {
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagAssemblyStatusOnChange_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 4
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataByGroups::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataByGroups::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 4> const&
          DiagData::Methods::requestDiagDataByGroups::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 4> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
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
              // diagDataGroupKeys
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // requestDiagDataByGroups_diagDataGroupKeys
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
              },
              // rootNode
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::requestDiagDataByGroups::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByGroups_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataByKeys::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataByKeys::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const&
          DiagData::Methods::requestDiagDataByKeys::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
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
              // diagDataKeys
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // requestDiagDataByKeys_diagDataKeys
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::requestDiagDataByKeys::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataByKeys_transformation_props,
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
          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataOnChange::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataOnChange::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 4> const&
          DiagData::Methods::requestDiagDataOnChange::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 4> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
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
              // diagDataKey
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
              },
              // minDeltaTriggerTime
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint16_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                      }
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::requestDiagDataOnChange::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnChange_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataOnThreshold::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestDiagDataOnThreshold::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 6> const&
          DiagData::Methods::requestDiagDataOnThreshold::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 6> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
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
              // diagDataKey
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
              },
              // minDeltaTriggerTime
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint16_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                      }
                    }
                  }
                },
              },
              // upperThreshold
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // int64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 4
                      }
                    }
                  }
                },
              },
              // lowerThreshold
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // int64_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_64bit, 5
                      }
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::requestDiagDataOnThreshold::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestDiagDataOnThreshold_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::requestSampledDiagData::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestSampledDiagData::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 5> const&
          DiagData::Methods::requestSampledDiagData::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 5> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
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
              // diagDataKey
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
              },
              // minDeltaTriggerTime
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint16_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_16bit, 3
                      }
                    }
                  }
                },
              },
              // measurementPeriod
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // uint32_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_32bit, 4
                      }
                    }
                  }
                },
              },
              // resultOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // ResultOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 3
                      }
                    }
                  }
                },
                // uint8_t
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 4
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::requestSampledDiagData::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSampledDiagData_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::requestSetDiagData::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::requestSetDiagData::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const&
          DiagData::Methods::requestSetDiagData::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSetDiagData_transformation_props,
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
              // diagDataItems
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSetDiagData_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 1
                      }
                    }
                  }
                },
              },
              // setOptions
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // SetOptions
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSetDiagData_transformation_props,
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
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSetDiagData_transformation_props,
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
          DiagData::Methods::requestSetDiagData::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSetDiagData_transformation_props,
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::requestSetDiagData_transformation_props,
                ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                {
                  ::ac::com::someip::serialization::Structure_tag
                  {
                    ::ac::com::someip::serialization::Structure_tag::Wire_type::base_data_type_8bit, 1
                  }
                }
              },
            };
            return mosprops;
          }
          ::ara::core::ErrorCode DiagData::Methods::sendDiagControlCommandRequest::GetErrorCode(
          ::ara::core::ErrorDomain::IdType /* unused */, ::ara::core::ErrorDomain::CodeType /* unused */,
          ::ara::core::ErrorDomain::SupportDataType /* unused */, char const* /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          ::ara::core::ErrorCode DiagData::Methods::sendDiagControlCommandRequest::GetErrorCode(
          ::ara::core::ErrorDomain::CodeType  /* unused */) noexcept
          {
            return {::ara::com::ComErrc::kNetworkBindingFailure};
          }

          std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const&
          DiagData::Methods::sendDiagControlCommandRequest::methodInSProps()
          {
            static std::array<::ac::com::someip::serialization::Serialization_attributes, 3> const misprops
            {
              // accessID
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandRequest_transformation_props,
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
              // controlCommand
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandRequest_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 2
                      }
                    }
                  }
                },
              },
              // controlMessage
              ::ac::com::someip::serialization::Serialization_attributes
              {
                // String
                {
                  ::ac::com::someip::serialization::Serialization_attributes_entry
                  {
                    ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandRequest_transformation_props,
                    ::ac::core::optional<::ac::com::someip::serialization::Structure_tag>
                    {
                      ::ac::com::someip::serialization::Structure_tag
                      {
                        ::ac::com::someip::serialization::Structure_tag::Wire_type::complex_data_type_static_length_field, 3
                      }
                    }
                  }
                },
              },
            };
            return misprops;
          }
          ::ac::com::someip::serialization::Serialization_attributes const&
          DiagData::Methods::sendDiagControlCommandRequest::methodOutSProps()
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
                ::vwg::services::diagnostic::diagdata::diagdata::deployment::tlv::diagdata_transformation_props_set::sendDiagControlCommandRequest_transformation_props,
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
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg
