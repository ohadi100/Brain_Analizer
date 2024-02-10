/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_UDSRESPONSECODETYPE_H
#define AC_DM_TYPES_IMPL_TYPE_UDSRESPONSECODETYPE_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      enum class UDSResponseCodeType : ::ara::stdtypes::UInt8 
      {
        kGeneralReject = 0x10U,
        kServiceNotSupported = 0x11U,
        kSubfunctionNotSupported = 0x12U,
        kIncorrectMessageLengthOrInvalidFormat = 0x13U,
        kBusyRepeatRequest = 0x21U,
        kConditionsNotCorrect = 0x22U,
        kRequestSequenceError = 0x24U,
        kNoResponseFromSubnetComponent = 0x25U,
        kFailurePreventsExecutionOfRequestedAction = 0x26U,
        kRequestOutOfRange = 0x31U,
        kSecurityAccessDenied = 0x33U,
        kInvalidKey = 0x35U,
        kExceedNumberOfAttempts = 0x36U,
        kRequiredTimeDelayNotExpired = 0x37U,
        kUploadDownloadNotAccepted = 0x70U,
        kTransferDataSuspended = 0x71U,
        kGeneralProgrammingFailure = 0x72U,
        kWrongBlockSequenceCounter = 0x73U,
        kRequestCorrectlyReceivedResponsePending = 0x78U,
        kSubFunctionNotSupportedInActiveSession = 0x7EU,
        kServiceNotSupportedInActiveSession = 0x7FU,
        kNoProcessingNoResponse = 0xFFU
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
