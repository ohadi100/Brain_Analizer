/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_EVENTSTATUSBYTETYPELITERALS_H
#define AC_DM_TYPES_IMPL_TYPE_EVENTSTATUSBYTETYPELITERALS_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class EventStatusByteTypeLiterals : ::ara::stdtypes::UInt8 
      {
        kUDSStatusTF = 0x01U,
        kUDSStatusTFTOC = 0x02U,
        kUDSStatusTNCTOC = 0x40U
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
