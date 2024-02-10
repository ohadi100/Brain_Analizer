/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DT_LISTOFIDS_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DT_LISTOFIDS_H

#include "vwg/services/diagnosticdatadistribution/datatypes/impl_type_dt_listofids_ids_array.h"

namespace vwg
{
  namespace services
  {
    namespace diagnosticdatadistribution
    {
      namespace datatypes
      {
        struct DT_ListOfIds
        {
          DT_ListOfIds_iDs_ARRAY iDs;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            f(this->iDs);
          }
        };
      }// namespace datatypes
    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg

#endif
