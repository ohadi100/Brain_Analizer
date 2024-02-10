/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H

#include "ara/stdtypes/impl_type_uint8.h"
#include "ac/dm/types/impl_type_udsaddresstype.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct DiagnosticConversationIdentifierType
      {
        ::ara::stdtypes::UInt8 diagnosticProtocolKind;
        UdsAddressType targetAddress;
        UdsAddressType sourceAddress;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->diagnosticProtocolKind);
          f(this->targetAddress);
          f(this->sourceAddress);
        }
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
