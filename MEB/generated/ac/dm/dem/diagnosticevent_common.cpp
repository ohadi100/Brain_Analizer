/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
#include "diagnosticevent_common.h"

namespace ac
{

  namespace dm
  {

    namespace dem
    {

      std::exception_ptr DiagnosticEvent::FaultDetectionCounter::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

      std::exception_ptr DiagnosticEvent::GetDTCOfEvent::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

      std::exception_ptr DiagnosticEvent::GetDebouncingOfEvent::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

      std::exception_ptr DiagnosticEvent::EventStatus::Get::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

    }// namespace dem
  }// namespace dm
}// namespace ac
