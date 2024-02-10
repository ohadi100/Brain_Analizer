/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_OPERATIONSTATUS_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENT_IMPL_TYPE_OPERATIONSTATUS_H

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
          enum class OperationStatus : ::ara::stdtypes::UInt16
          {
            operation_timeout = 65534U,
            success = 0U,
            protocol_error = 65535U,
            accepted = 202U,
            multiple_choice = 300U,
            not_modified = 304U,
            unauthorized = 401U,
            forbidden = 403U,
            not_found = 404U,
            request_time_out = 408U,
            conflict = 409U,
            request_too_large = 414U,
            too_many_requests = 429U,
            request_header_fields_too_large = 431U,
            unavailable_for_legal_reasons = 451U,
            internal_server_error = 500U,
            service_unavailable = 503U,
            gateway_time_out = 504U,
            network_authentication_required = 511U
          };
        } // namespace idssecurityevent
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
