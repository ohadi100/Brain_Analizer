/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONSTATUSTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_DIAGNOSTICCONVERSATIONSTATUSTYPE_H

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
        ActivityStatusType activityStatus;
        DiagnosticSessionType diagnosticSession;
        DiagnosticSecurityLevelType diagnosticSecurityLevel;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->activityStatus);
          f(this->diagnosticSession);
          f(this->diagnosticSecurityLevel);
        }
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
