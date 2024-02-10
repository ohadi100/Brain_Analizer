/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_DEPLOYMENT_TLV_ODCAGENTCOMMONLARGE_TRANSFORMATION_PROPS_SET_ESTIMATECAMPAIGN_TRANSFORMATION_PROPS_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_DEPLOYMENT_TLV_ODCAGENTCOMMONLARGE_TRANSFORMATION_PROPS_SET_ESTIMATECAMPAIGN_TRANSFORMATION_PROPS_H

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
        namespace odcagentcommonlarge
        {
          namespace deployment
          {
            namespace tlv
            {
              namespace odcagentcommonlarge_transformation_props_set
              {
                static constexpr ::ac::com::someip::serialization::Serialization_properties
                estimateCampaign_transformation_props
                {
                  0, // Alignment
                  ::ac::com::byte_order::Byte_order::big_endian, // Byte order
                  4, // Size of array length field
                  4, // Size of string length field
                  4, // Size of struct length field
                  4, // Size of union length field
                  4 // Size of union type selector field
                };
              } // namespace odcagentcommonlarge_transformation_props_set
            } // namespace tlv
          } // namespace deployment
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif
