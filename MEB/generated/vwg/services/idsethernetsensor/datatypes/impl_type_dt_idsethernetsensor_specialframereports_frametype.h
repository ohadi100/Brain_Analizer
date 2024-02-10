/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSETHERNETSENSOR_DATATYPES_IMPL_TYPE_DT_IDSETHERNETSENSOR_SPECIALFRAMEREPORTS_FRAMETYPE_H
#define VWG_SERVICES_IDSETHERNETSENSOR_DATATYPES_IMPL_TYPE_DT_IDSETHERNETSENSOR_SPECIALFRAMEREPORTS_FRAMETYPE_H

#include "ara/stdtypes/impl_type_uint32.h"

namespace vwg
{
  namespace services
  {
    namespace idsethernetsensor
    {
      namespace datatypes
      {
        enum class DT_IDSEthernetSensor_specialFrameReports_frameType : ::ara::stdtypes::UInt32 
        {
          L2TP = 0U,
          DHCPv6 = 1U,
          ICMPv6 = 2U,
          TCP_CNTRL = 3U,
          XCP = 4U,
          DOIP = 5U,
          IPv4 = 6U,
          UDSoverIP = 7U
        };
      }// namespace datatypes
    }// namespace idsethernetsensor
  }// namespace services
}// namespace vwg

#endif
