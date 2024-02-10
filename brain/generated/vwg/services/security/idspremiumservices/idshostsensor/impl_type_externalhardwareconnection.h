/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_EXTERNALHARDWARECONNECTION_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_EXTERNALHARDWARECONNECTION_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalhardwareconnection_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalhardwareconnection_serialnumber.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalhardwareconnection_deviceclassesinformation.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalhardwareconnection_connectionhandlinginstancename.h"

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
          struct ExternalHardwareConnection
          {
            ExternalHardwareConnection_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 connectedHardwareType{};
            ExternalHardwareConnection_serialNumber serialNumber{};
            ExternalHardwareConnection_deviceClassesInformation deviceClassesInformation{};
            ExternalHardwareConnection_connectionHandlingInstanceName connectionHandlingInstanceName{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectedHardwareType);
              f(this->serialNumber);
              f(this->deviceClassesInformation);
              f(this->connectionHandlingInstanceName);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectedHardwareType);
              f(this->serialNumber);
              f(this->deviceClassesInformation);
              f(this->connectionHandlingInstanceName);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
