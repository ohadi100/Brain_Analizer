/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_AC_DM_TYPES_IMPL_TYPE_CONFIRMATIONSTATUSTYPE_H
#define INC_AC_DM_TYPES_IMPL_TYPE_CONFIRMATIONSTATUSTYPE_H

#include <cstdint>

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class ConfirmationStatusType : std::uint8_t
      {
        kResPosOk = 0x00U,
        kResPosNotOk = 0x01U,
        kResNegOk = 0x02U,
        kResNegNotOk = 0x03U,
        kResPosSuppressed = 0x04U,
        kResNegSuppressed = 0x05U,
        kCanceled = 0x06U,
        kNoProcessingNoResponse = 0x07U
      };
    } // namespace types
  } // namespace dm
} // namespace ac

#endif
