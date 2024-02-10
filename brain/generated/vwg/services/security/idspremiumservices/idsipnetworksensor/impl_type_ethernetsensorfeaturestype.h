/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IMPL_TYPE_ETHERNETSENSORFEATURESTYPE_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSIPNETWORKSENSOR_IMPL_TYPE_ETHERNETSENSORFEATURESTYPE_H

#include "ara/core/optional.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_incidentdata.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_configurationsettings.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_controlcommands.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_firewalldata.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_ipversionviolation.h"
#include "vwg/services/security/idspremiumservices/idsipnetworksensor/impl_type_protocolcategoryviolation.h"
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
          struct EthernetSensorFeaturesType
          {
            ::ara::core::Optional<IncidentData> incidentData{};
            ::ara::core::Optional<ConfigurationSettings> configurationSettings{};
            ::ara::core::Optional<ControlCommands> controlCommands{};
            ::ara::core::Optional<FirewallData> firewallData{};
            ::ara::core::Optional<IpVersionViolation> ipVersionViolation{};
            ::ara::core::Optional<ProtocolCategoryViolation> protocolCategoryViolation{};
            ::ara::stdtypes::UInt8 elementId{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->incidentData);
              f(this->configurationSettings);
              f(this->controlCommands);
              f(this->firewallData);
              f(this->ipVersionViolation);
              f(this->protocolCategoryViolation);
              f(this->elementId);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->incidentData);
              f(this->configurationSettings);
              f(this->controlCommands);
              f(this->firewallData);
              f(this->ipVersionViolation);
              f(this->protocolCategoryViolation);
              f(this->elementId);
            }
          };
        } // namespace idsipnetworksensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
