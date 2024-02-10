/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DT_DIAGNOSTICVALUESRESULTTYPE_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DT_DIAGNOSTICVALUESRESULTTYPE_H

#include "ara/stdtypes/impl_type_uint32.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "vwg/services/diagnosticdatadistribution/datatypes/impl_type_dt_diagnosticvaluesresulttype_diagnosticdata_array.h"
#include "vwg/services/diagnosticdatadistribution/datatypes/impl_type_diagnosticvaluesresulttype_diagreturntype.h"

namespace vwg
{
  namespace services
  {
    namespace diagnosticdatadistribution
    {
      namespace datatypes
      {
        struct DT_DiagnosticValuesResultType
        {
          ::ara::stdtypes::UInt32 name_space;
          ::ara::stdtypes::UInt32 category;
          ::ara::stdtypes::UInt64 hashValue;
          ::ara::stdtypes::UInt32 length;
          DT_DiagnosticValuesResultType_diagnosticData_ARRAY diagnosticData;
          DiagnosticValuesResultType_diagReturnType diagReturnType;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            f(this->name_space);
            f(this->category);
            f(this->hashValue);
            f(this->length);
            f(this->diagnosticData);
            f(this->diagReturnType);
          }
        };
      }// namespace datatypes
    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg

#endif
