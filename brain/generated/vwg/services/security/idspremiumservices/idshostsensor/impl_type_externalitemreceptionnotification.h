/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_EXTERNALITEMRECEPTIONNOTIFICATION_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_EXTERNALITEMRECEPTIONNOTIFICATION_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalitemreceptionnotification_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalitemreceptionnotification_dataorigin.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalitemreceptionnotification_destinationapplicationname.h"
#include "ara/stdtypes/impl_type_uint32.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalitemreceptionnotification_objectname.h"

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
          struct ExternalItemReceptionNotification
          {
            ExternalItemReceptionNotification_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 dataType{};
            ExternalItemReceptionNotification_dataOrigin dataOrigin{};
            ExternalItemReceptionNotification_destinationApplicationName destinationApplicationName{};
            ::ara::stdtypes::UInt32 dataSize{};
            ExternalItemReceptionNotification_objectName objectName{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->dataType);
              f(this->dataOrigin);
              f(this->destinationApplicationName);
              f(this->dataSize);
              f(this->objectName);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->dataType);
              f(this->dataOrigin);
              f(this->destinationApplicationName);
              f(this->dataSize);
              f(this->objectName);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
