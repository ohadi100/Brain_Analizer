/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
#include "dataidentifier_intrusiondetectionsystemgetlog_common.h"

namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_4944
      {

        DataIdentifier_IntrusionDetectionSystemGetLog::UDSServiceFailed::UDSServiceFailed(::ac::dm::types::UDSResponseCodeType Read_nrc)
        : m_Output{Read_nrc}
        {}

        DataIdentifier_IntrusionDetectionSystemGetLog::UDSServiceFailed::UDSServiceFailed(::ac::com::someip::serialization::buffer_t const& data)
        : m_Output{}
        {
          ::ac::com::someip::serialization::Deserializer deserializer(data);
          auto f = [&deserializer](auto& member) { deserializer.deserialize(member); };
          m_Output.visit(f);
        }

        std::exception_ptr DataIdentifier_IntrusionDetectionSystemGetLog::Cancel::GetApplicationErrorExceptionPtr(
        ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
        {
          return nullptr;

        }

        std::exception_ptr DataIdentifier_IntrusionDetectionSystemGetLog::Read::GetApplicationErrorExceptionPtr(
        ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data)
        {
          switch (error)
          {
            case 2u:
            return std::make_exception_ptr(DataIdentifier_IntrusionDetectionSystemGetLog::UDSServiceFailed(data));

            default:
            return nullptr;
          }

        }

      }// namespace d_4944
    }// namespace diag
  }// namespace services
}// namespace vwg
