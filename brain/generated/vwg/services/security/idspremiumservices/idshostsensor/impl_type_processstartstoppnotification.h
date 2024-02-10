/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_PROCESSSTARTSTOPPNOTIFICATION_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_PROCESSSTARTSTOPPNOTIFICATION_H

#include "ara/core/optional.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_processstartstoppnotification_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "ara/stdtypes/impl_type_uint32.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_processstartstoppnotification_processcommandline.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_processstartstoppnotification_adaptiveautosarapplicationname.h"

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
          struct ProcessStartStoppNotification
          {
            ProcessStartStoppNotification_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 vmIdentifier{};
            ::ara::stdtypes::UInt8 processState{};
            ::ara::stdtypes::UInt16 userIdentifier{};
            ::ara::stdtypes::UInt16 groupIdentifier{};
            ::ara::stdtypes::UInt16 effectiveUid{};
            ::ara::stdtypes::UInt32 parentProcessIdentifier{};
            ::ara::stdtypes::UInt32 processIdentifier{};
            ProcessStartStoppNotification_processCommandline processCommandline{};
            ProcessStartStoppNotification_adaptiveAutosarApplicationName adaptiveAutosarApplicationName{};
            ::ara::core::Optional<::ara::stdtypes::UInt32> errorCode{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->vmIdentifier);
              f(this->processState);
              f(this->userIdentifier);
              f(this->groupIdentifier);
              f(this->effectiveUid);
              f(this->parentProcessIdentifier);
              f(this->processIdentifier);
              f(this->processCommandline);
              f(this->adaptiveAutosarApplicationName);
              f(this->errorCode);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->vmIdentifier);
              f(this->processState);
              f(this->userIdentifier);
              f(this->groupIdentifier);
              f(this->effectiveUid);
              f(this->parentProcessIdentifier);
              f(this->processIdentifier);
              f(this->processCommandline);
              f(this->adaptiveAutosarApplicationName);
              f(this->errorCode);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
