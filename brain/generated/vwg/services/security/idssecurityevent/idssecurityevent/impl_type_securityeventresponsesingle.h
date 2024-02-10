/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SECURITYEVENTRESPONSESINGLE_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SECURITYEVENTRESPONSESINGLE_H

#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_operationstatus.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventtype.h"

namespace vwg
{
  namespace services
  {
    namespace security
    {
      namespace idssecurityevent
      {
        namespace idssecurityevent
        {
          struct securityEventResponseSingle
          {
            OperationStatus status{};
            SecurityEventType element{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->status);
              f(this->element);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->status);
              f(this->element);
            }
          };
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
