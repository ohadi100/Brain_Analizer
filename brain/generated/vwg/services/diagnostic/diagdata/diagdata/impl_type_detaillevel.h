/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_DETAILLEVEL_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_DETAILLEVEL_H

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
          enum class DetailLevel : ::ara::stdtypes::UInt8
          {
            full = 0U,
            remoteRepair = 1U,
            update = 2U,
            documentation = 3U,
            aftersales = 4U,
            functionalSafety = 5U,
            testerEntry = 6U,
            digitalTwin = 7U
          };
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg

#endif
