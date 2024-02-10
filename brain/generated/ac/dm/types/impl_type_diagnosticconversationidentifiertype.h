/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H
#define INC_AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONIDENTIFIERTYPE_H

#include <cstdint>
#include "ac/dm/types/impl_type_udsaddresstype.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct DiagnosticConversationIdentifierType
      {
        std::uint8_t diagnosticProtocolKind{};
        UdsAddressType targetAddress{};
        UdsAddressType sourceAddress{};
        using Generated_tag = void;
        // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
        // not.
        template<typename F> void visit(F& f)
        {
          f(this->diagnosticProtocolKind);
          f(this->targetAddress);
          f(this->sourceAddress);
        }
        // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
        // not.
        template<typename F> void visit(F& f) const
        {
          f(this->diagnosticProtocolKind);
          f(this->targetAddress);
          f(this->sourceAddress);
        }
      };
    } // namespace types
  } // namespace dm
} // namespace ac

#endif
