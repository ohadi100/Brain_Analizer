/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_CRYPTOGRAPHICINCIDENTNOTIFICATION_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_CRYPTOGRAPHICINCIDENTNOTIFICATION_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_cryptographicincidentnotification_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_cryptographicincidentnotification_applicationname.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_cryptographicincidentnotification_failurereason.h"

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
          struct CryptographicIncidentNotification
          {
            CryptographicIncidentNotification_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            CryptographicIncidentNotification_applicationName applicationName{};
            ::ara::stdtypes::UInt8 cryptographicFunction{};
            CryptographicIncidentNotification_failureReason failureReason{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->applicationName);
              f(this->cryptographicFunction);
              f(this->failureReason);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->applicationName);
              f(this->cryptographicFunction);
              f(this->failureReason);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
