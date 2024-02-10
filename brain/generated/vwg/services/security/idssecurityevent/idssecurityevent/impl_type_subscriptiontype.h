/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SUBSCRIPTIONTYPE_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_SUBSCRIPTIONTYPE_H

#include "ara/stdtypes/impl_type_uint8.h"

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
          enum class SubscriptionType : ::ara::stdtypes::UInt8
          {
            singleUpdate = 0U,
            singleInitialEvent = 1U,
            resourceFullUpdate = 2U,
            resourceInitialEvent = 3U
          };
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
