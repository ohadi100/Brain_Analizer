/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_GIDSTATUSTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_GIDSTATUSTYPE_H

#include "ac/dm/types/impl_type_gidtype.h"
#include "ara/stdtypes/impl_type_uint8.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct GIDstatusType
      {
        GIDType GID;
        ::ara::stdtypes::UInt8 furtherActionReq;
        ::ara::stdtypes::UInt8 syncStatus;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->GID);
          f(this->furtherActionReq);
          f(this->syncStatus);
        }
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
