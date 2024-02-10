/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_DEPLOYMENT_TLV_ODCAGENTGENERICLARGE_TRANSFORMATION_PROPS_SET_CONTROL_TRANSFORMATION_PROPS_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_DEPLOYMENT_TLV_ODCAGENTGENERICLARGE_TRANSFORMATION_PROPS_SET_CONTROL_TRANSFORMATION_PROPS_H

#include "ac/com/byte_order.hpp"
#include "ac/com/someip/serialization/serialization_properties.hpp"

namespace vwg
{
  namespace services
  {
    namespace connect
    {
      namespace datacollector
      {
        namespace odcagentgenericlarge
        {
          namespace deployment
          {
            namespace tlv
            {
              namespace odcagentgenericlarge_transformation_props_set
              {
                static constexpr ::ac::com::someip::serialization::Serialization_properties
                control_transformation_props
                {
                  0, // Alignment
                  ::ac::com::byte_order::Byte_order::big_endian, // Byte order
                  1, // Size of array length field
                  1, // Size of string length field
                  1, // Size of struct length field
                  1, // Size of union length field
                  4 // Size of union type selector field
                };
              } // namespace odcagentgenericlarge_transformation_props_set
            } // namespace tlv
          } // namespace deployment
        } // namespace odcagentgenericlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
