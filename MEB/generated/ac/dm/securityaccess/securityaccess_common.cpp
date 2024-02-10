/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
#include "securityaccess_common.h"

namespace ac
{

  namespace dm
  {

    namespace securityaccess
    {

      SecurityAccess::UDSServiceFailed::UDSServiceFailed(::ac::dm::types::UDSResponseCodeType CompareKey_nrc,
      ::ac::dm::types::UDSResponseCodeType GetSeed_nrc)
      : m_Output{CompareKey_nrc,
      GetSeed_nrc}
      {}

      SecurityAccess::UDSServiceFailed::UDSServiceFailed(::ac::com::someip::serialization::buffer_t const& data)
      : m_Output{}
      {
        ::ac::com::someip::serialization::Deserializer deserializer(data);
        auto f = [&deserializer](auto& member) { deserializer.deserialize(member); };
        m_Output.visit(f);
      }

      std::exception_ptr SecurityAccess::Cancel::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

      std::exception_ptr SecurityAccess::CompareKey::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data)
      {
        switch (error)
        {
          case 2u:
          return std::make_exception_ptr(SecurityAccess::UDSServiceFailed(data));

          default:
          return nullptr;
        }

      }

      std::exception_ptr SecurityAccess::GetSeed::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data)
      {
        switch (error)
        {
          case 2u:
          return std::make_exception_ptr(SecurityAccess::UDSServiceFailed(data));

          default:
          return nullptr;
        }

      }

    }// namespace securityaccess
  }// namespace dm
}// namespace ac
