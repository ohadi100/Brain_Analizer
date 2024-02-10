/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SECURITYEVENTEVENT_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SECURITYEVENTEVENT_H

#include "ara/stdtypes/impl_type_uint32.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_subscriptiontype.h"
#include "vwg/services/security/idssecurityevent/idssecurityevent/impl_type_subscriptionstatus.h"
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
          struct SecurityEventEvent
          {
            ::ara::stdtypes::UInt32 subscriptionId{};
            ::ara::stdtypes::UInt32 updateCounter{};
            ::ara::stdtypes::UInt16 totalNoOfMessages{};
            ::ara::stdtypes::UInt16 eventMessageCounter{};
            ::ara::stdtypes::UInt16 noOfResourceElements{};
            SubscriptionType type{};
            SubscriptionStatus subscriptionStatus{};
            SecurityEventType element{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->subscriptionId);
              f(this->updateCounter);
              f(this->totalNoOfMessages);
              f(this->eventMessageCounter);
              f(this->noOfResourceElements);
              f(this->type);
              f(this->subscriptionStatus);
              f(this->element);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->subscriptionId);
              f(this->updateCounter);
              f(this->totalNoOfMessages);
              f(this->eventMessageCounter);
              f(this->noOfResourceElements);
              f(this->type);
              f(this->subscriptionStatus);
              f(this->element);
            }
          };
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
