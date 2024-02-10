/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_INDICATORSTATUSTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_INDICATORSTATUSTYPE_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class IndicatorStatusType : ::ara::stdtypes::UInt8 
      {
        kOff = 0x00U,
        kContinous = 0x01U,
        kBlinking = 0x02U,
        kBlinkingAndContinous = 0x03U,
        kSlowFlash = 0x04U,
        kFastFlash = 0x05U,
        kOnDemand = 0x06U,
        kShort = 0x07U
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
