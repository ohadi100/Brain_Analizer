/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SECURITYEVENTTYPE_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SECURITYEVENTTYPE_H

#include "ara/core/optional.h"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventtype_eventframe.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventtype_timestamp.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_securityeventtype_contextdata.h"

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
          struct SecurityEventType
          {
            ::vwg::stdtypes::DT_uuid id{};
            ::ara::core::Optional<SecurityEventType_eventFrame> eventFrame{};
            ::ara::core::Optional<SecurityEventType_timestamp> timestamp{};
            ::ara::core::Optional<SecurityEventType_contextData> contextData{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->id);
              f(this->eventFrame);
              f(this->timestamp);
              f(this->contextData);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->id);
              f(this->eventFrame);
              f(this->timestamp);
              f(this->contextData);
            }
          };
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
