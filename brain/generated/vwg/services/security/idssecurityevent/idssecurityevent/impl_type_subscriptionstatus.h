/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SUBSCRIPTIONSTATUS_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SUBSCRIPTIONSTATUS_H

#include "ara/stdtypes/impl_type_uint16.h"

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
          enum class SubscriptionStatus : ::ara::stdtypes::UInt16
          {
            subscription_timeout = 65534U,
            subscription_error = 65535U,
            accepted = 0U,
            running = 1U,
            cancelled = 2U,
            target_deleted = 3U
          };
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
