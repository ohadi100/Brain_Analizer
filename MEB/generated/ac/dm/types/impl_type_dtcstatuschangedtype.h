/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_DTCSTATUSCHANGEDTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_DTCSTATUSCHANGEDTYPE_H

#include "ac/dm/types/impl_type_dtctype.h"
#include "ac/dm/types/impl_type_udsstatusbytetype.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct DTCStatusChangedType
      {
        DTCType DTC;
        UdsStatusByteType udsStatusByteOld;
        UdsStatusByteType udsStatusByteNew;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->DTC);
          f(this->udsStatusByteOld);
          f(this->udsStatusByteNew);
        }
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
