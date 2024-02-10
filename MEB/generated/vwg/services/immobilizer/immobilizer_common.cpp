/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
#include "immobilizer_common.h"

namespace vwg
{

  namespace services
  {

    namespace immobilizer
    {

      std::exception_ptr Immobilizer::info::Get::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

      std::exception_ptr Immobilizer::notifications::Get::GetApplicationErrorExceptionPtr(
      ::ac::com::cpp_binding::Error_id /* unused */, std::vector<std::uint8_t> const& /* unused */)
      {
        return nullptr;

      }

    }// namespace immobilizer
  }// namespace services
}// namespace vwg
