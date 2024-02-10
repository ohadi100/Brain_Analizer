/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_MONITORACTIONTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_MONITORACTIONTYPE_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class MonitorActionType : ::ara::stdtypes::UInt8 
      {
        kPassed = 0U,
        kFailed = 1U,
        kPrepassed = 2U,
        kPrefailed = 3U,
        kFdcThresholdReached = 4U,
        kResetTestFailed = 5U,
        kFreezeDebouncing = 6U,
        kResetDebouncing = 7U,
        kPrestore = 8U,
        kClearPrestore = 9U
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
