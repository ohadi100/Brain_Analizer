/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_SERVICEAPPLICATIONNOTIFICATION_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_SERVICEAPPLICATIONNOTIFICATION_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_serviceapplicationnotification_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_serviceapplicationnotification_registeredservice.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_serviceapplicationnotification_requestingapplicationidentifier.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_serviceapplicationnotification_requestingserveripaddress.h"
#include "ara/stdtypes/impl_type_boolean.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_serviceapplicationnotification_errorinformation.h"

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
          struct ServiceApplicationNotification
          {
            ServiceApplicationNotification_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 serviceRegistryIdentifier{};
            ServiceApplicationNotification_registeredService registeredService{};
            ::ara::stdtypes::UInt8 requestType{};
            ServiceApplicationNotification_requestingApplicationIdentifier requestingApplicationIdentifier{};
            ServiceApplicationNotification_requestingServerIpAddress requestingServerIpAddress{};
            ::ara::stdtypes::Boolean requestStatus{};
            ServiceApplicationNotification_errorInformation errorInformation{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->serviceRegistryIdentifier);
              f(this->registeredService);
              f(this->requestType);
              f(this->requestingApplicationIdentifier);
              f(this->requestingServerIpAddress);
              f(this->requestStatus);
              f(this->errorInformation);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->serviceRegistryIdentifier);
              f(this->registeredService);
              f(this->requestType);
              f(this->requestingApplicationIdentifier);
              f(this->requestingServerIpAddress);
              f(this->requestStatus);
              f(this->errorInformation);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
