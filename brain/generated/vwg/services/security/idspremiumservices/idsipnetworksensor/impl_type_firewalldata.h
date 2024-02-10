/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IMPL_TYPE_FIREWALLDATA_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IMPL_TYPE_FIREWALLDATA_H

#include "ara/core/optional.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_ipaddresses.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_ipports.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_connectionstatus.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_connectionidentifier.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_stateinformation.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_decodedpayloaddata.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_preventionactionperformed.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata_payloaddata.h"
#include "ara/stdtypes/impl_type_uint8.h"

namespace vwg
{
  namespace services
  {
    namespace security
    {
      namespace idspremiumservices
      {
        namespace idsipnetworksensor
        {
          struct FirewallData
          {
            FirewallData_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt16 blockedConnectionAttempts{};
            FirewallData_ipAddresses ipAddresses{};
            FirewallData_ipPorts ipPorts{};
            FirewallData_connectionStatus connectionStatus{};
            FirewallData_connectionIdentifier connectionIdentifier{};
            FirewallData_stateInformation stateInformation{};
            ::ara::core::Optional<FirewallData_decodedPayloadData> decodedPayloadData{};
            ::ara::core::Optional<FirewallData_preventionActionPerformed> preventionActionPerformed{};
            ::ara::core::Optional<FirewallData_payloadData> payloadData{};
            ::ara::core::Optional<::ara::stdtypes::UInt8> messagePriorityLevel{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->blockedConnectionAttempts);
              f(this->ipAddresses);
              f(this->ipPorts);
              f(this->connectionStatus);
              f(this->connectionIdentifier);
              f(this->stateInformation);
              f(this->decodedPayloadData);
              f(this->preventionActionPerformed);
              f(this->payloadData);
              f(this->messagePriorityLevel);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->blockedConnectionAttempts);
              f(this->ipAddresses);
              f(this->ipPorts);
              f(this->connectionStatus);
              f(this->connectionIdentifier);
              f(this->stateInformation);
              f(this->decodedPayloadData);
              f(this->preventionActionPerformed);
              f(this->payloadData);
              f(this->messagePriorityLevel);
            }
          };
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
