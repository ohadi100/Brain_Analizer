/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_RETURNSTATUS_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_RETURNSTATUS_H

#include "ara/stdtypes/impl_type_uint8.h"

namespace vwg
{
  namespace services
  {
    namespace diagnostic
    {
      namespace diagdata
      {
        namespace diagdata
        {
          enum class ReturnStatus : ::ara::stdtypes::UInt8
          {
            success = 0U,
            generalError = 1U,
            invalidParameters = 2U,
            resourceBusy = 3U,
            assemblyStatusNotReady = 4U,
            exclusiveAccessGrantedToAnotherClient = 6U,
            keyUnknown = 8U,
            resultFormatNotSupported = 9U,
            unknownRequestId = 10U,
            functionNotSupportedForGivenKey = 11U,
            responseTimeout = 12U,
            nodeUnknown = 13U,
            clientNotAuthorized = 16U,
            schemaMismatch = 19U
          };
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg

#endif
