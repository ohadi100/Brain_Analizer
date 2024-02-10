/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONSTATUSTYPE_H
#define INC_AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONSTATUSTYPE_H

#include "ac/dm/types/impl_type_activitystatustype.h"
#include "ac/dm/types/impl_type_diagnosticsessiontype.h"
#include "ac/dm/types/impl_type_diagnosticsecurityleveltype.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct DiagnosticConversationStatusType
      {
        ActivityStatusType activityStatus{};
        DiagnosticSessionType diagnosticSession{};
        DiagnosticSecurityLevelType diagnosticSecurityLevel{};
        using Generated_tag = void;
        // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
        // not.
        template<typename F> void visit(F& f)
        {
          f(this->activityStatus);
          f(this->diagnosticSession);
          f(this->diagnosticSecurityLevel);
        }
        // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
        // not.
        template<typename F> void visit(F& f) const
        {
          f(this->activityStatus);
          f(this->diagnosticSession);
          f(this->diagnosticSecurityLevel);
        }
      };
    } // namespace types
  } // namespace dm
} // namespace ac

#endif
