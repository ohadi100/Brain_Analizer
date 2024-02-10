/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DIAGNOSTICVALUESRESULTTYPE_DIAGRETURNTYPE_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DIAGNOSTICVALUESRESULTTYPE_DIAGRETURNTYPE_H

#include "ara/stdtypes/impl_type_uint32.h"

namespace vwg
{
  namespace services
  {
    namespace diagnosticdatadistribution
    {
      namespace datatypes
      {
        enum class DiagnosticValuesResultType_diagReturnType : ::ara::stdtypes::UInt32 
        {
          DIAG_RESULT_OK = 0U,
          DIAG_RESULT_ERROR_INIT_NOT_READY = 1U,
          DIAG_RESULT_WRONG_PARAMETER = 2U,
          DIAG_RESULT_ERROR_GENERAL = 3U
        };
      }// namespace datatypes
    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg

#endif
