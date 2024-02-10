/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_WIFICONNECTIONSUCCESS_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_WIFICONNECTIONSUCCESS_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionsuccess_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionsuccess_connectingunitaddress.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionsuccess_suppliedipv4address.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionsuccess_suppliedipv6address.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionsuccess_connectingunitdevicename.h"

namespace vwg
{
  namespace services
  {
    namespace security
    {
      namespace idspremiumservices
      {
        namespace idshostsensor
        {
          struct WifiConnectionSuccess
          {
            WifiConnectionSuccess_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 connectionType{};
            WifiConnectionSuccess_connectingUnitAddress connectingUnitAddress{};
            WifiConnectionSuccess_suppliedIpv4Address suppliedIpv4Address{};
            WifiConnectionSuccess_suppliedIpv6Address suppliedIpv6Address{};
            WifiConnectionSuccess_connectingUnitDeviceName connectingUnitDeviceName{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectionType);
              f(this->connectingUnitAddress);
              f(this->suppliedIpv4Address);
              f(this->suppliedIpv6Address);
              f(this->connectingUnitDeviceName);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectionType);
              f(this->connectingUnitAddress);
              f(this->suppliedIpv4Address);
              f(this->suppliedIpv6Address);
              f(this->connectingUnitDeviceName);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
