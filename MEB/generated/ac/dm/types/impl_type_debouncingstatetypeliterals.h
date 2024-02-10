/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_DEBOUNCINGSTATETYPELITERALS_H
#define AC_DM_TYPES_IMPL_TYPE_DEBOUNCINGSTATETYPELITERALS_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class DebouncingStateTypeLiterals : ::ara::stdtypes::UInt8 
      {
        kTemporarilyDefective = 0U,
        kFinallyDefective = 1U,
        kTemporarilyHealed = 2U,
        kTestComplete = 4U,
        kDTRUpdate = 8U
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
