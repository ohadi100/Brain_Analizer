/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IMPL_TYPE_SECURITYEVENTSTRUCT_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IMPL_TYPE_SECURITYEVENTSTRUCT_H

#include "ara/core/optional.h"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/impl_type_securityeventstruct_eventframe.h"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/impl_type_securityeventstruct_timestamp.h"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/impl_type_securityeventstruct_contextdata.h"

namespace vwg
{
  namespace services
  {
    namespace security
    {
      namespace idssecurityevent
      {
        namespace idssecurityeventsmall
        {
          struct SecurityEventStruct
          {
            SecurityEventStruct_eventFrame eventFrame{};
            ::ara::core::Optional<SecurityEventStruct_timestamp> timestamp{};
            ::ara::core::Optional<SecurityEventStruct_contextData> contextData{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->eventFrame);
              f(this->timestamp);
              f(this->contextData);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->eventFrame);
              f(this->timestamp);
              f(this->contextData);
            }
          };
        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
