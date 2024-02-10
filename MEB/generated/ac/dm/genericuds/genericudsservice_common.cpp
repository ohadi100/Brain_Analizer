/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
#include "genericudsservice_common.h"

namespace ac
{

  namespace dm
  {

    namespace genericuds
    {

      GenericUDSService::UDSServiceFailed::UDSServiceFailed(::ac::dm::types::UDSResponseCodeType HandleMessage_nrc)
      : m_Output{HandleMessage_nrc}
      {}

      GenericUDSService::UDSServiceFailed::UDSServiceFailed(::ac::com::someip::serialization::buffer_t const& data)
      : m_Output{}
      {
        ::ac::com::someip::serialization::Deserializer deserializer(data);
        auto f = [&deserializer](auto& member) { deserializer.deserialize(member); };
        m_Output.visit(f);
      }

      std::exception_ptr GenericUDSService::Cancel::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

      std::exception_ptr GenericUDSService::HandleMessage::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data)
      {
        switch (error)
        {
          case 2u:
          return std::make_exception_ptr(GenericUDSService::UDSServiceFailed(data));

          default:
          return nullptr;
        }

      }

    }// namespace genericuds
  }// namespace dm
}// namespace ac
