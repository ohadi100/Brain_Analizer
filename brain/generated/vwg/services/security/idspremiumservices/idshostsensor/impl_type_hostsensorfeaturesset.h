/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_HOSTSENSORFEATURESSET_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_HOSTSENSORFEATURESSET_H

#include "ara/core/optional.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_configurationsettings.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_controlcommands.h"

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
          struct HostSensorFeaturesSet
          {
            ::ara::core::Optional<ConfigurationSettings> configurationSettings{};
            ::ara::core::Optional<ControlCommands> controlCommands{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->configurationSettings);
              f(this->controlCommands);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->configurationSettings);
              f(this->controlCommands);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
