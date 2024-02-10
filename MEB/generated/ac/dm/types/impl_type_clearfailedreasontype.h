/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_CLEARFAILEDREASONTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_CLEARFAILEDREASONTYPE_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class ClearFailedReasonType : ::ara::stdtypes::UInt8 
      {
        kFailed = 0x00U,
        kBusy = 0x01U,
        kMemoryError = 0x02U,
        kWrongDtc = 0x03U
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
