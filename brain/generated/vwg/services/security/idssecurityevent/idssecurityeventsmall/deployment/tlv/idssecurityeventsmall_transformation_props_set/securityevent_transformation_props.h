/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_DEPLOYMENT_TLV_IDSSECURITYEVENTSMALL_TRANSFORMATION_PROPS_SET_SECURITYEVENT_TRANSFORMATION_PROPS_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_DEPLOYMENT_TLV_IDSSECURITYEVENTSMALL_TRANSFORMATION_PROPS_SET_SECURITYEVENT_TRANSFORMATION_PROPS_H

#include "ac/com/byte_order.hpp"
#include "ac/com/someip/serialization/serialization_properties.hpp"

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
          namespace deployment
          {
            namespace tlv
            {
              namespace idssecurityeventsmall_transformation_props_set
              {
                static constexpr ::ac::com::someip::serialization::Serialization_properties
                securityEvent_transformation_props
                {
                  0, // Alignment
                  ::ac::com::byte_order::Byte_order::big_endian, // Byte order
                  2, // Size of array length field
                  2, // Size of string length field
                  2, // Size of struct length field
                  2, // Size of union length field
                  4 // Size of union type selector field
                };
              } // namespace idssecurityeventsmall_transformation_props_set
            } // namespace tlv
          } // namespace deployment
        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
