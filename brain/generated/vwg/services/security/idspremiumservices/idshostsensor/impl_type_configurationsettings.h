/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_CONFIGURATIONSETTINGS_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_CONFIGURATIONSETTINGS_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_configurationsettings_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_configurationsettings_configurationdata.h"

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
          struct ConfigurationSettings
          {
            ConfigurationSettings_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ConfigurationSettings_configurationData configurationData{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->configurationData);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->configurationData);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
