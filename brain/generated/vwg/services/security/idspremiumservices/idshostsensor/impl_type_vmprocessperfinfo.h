/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_VMPROCESSPERFINFO_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_VMPROCESSPERFINFO_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_vmprocessperfinfo_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_vmprocessperfinfo_processid.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_vmprocessperfinfo_processingtime.h"
#include "ara/stdtypes/impl_type_uint32.h"

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
          struct VmProcessPerfInfo
          {
            VmProcessPerfInfo_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 vmIdentifier{};
            VmProcessPerfInfo_processId processId{};
            VmProcessPerfInfo_processingTime processingTime{};
            ::ara::stdtypes::UInt32 ramUtilization{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->vmIdentifier);
              f(this->processId);
              f(this->processingTime);
              f(this->ramUtilization);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->vmIdentifier);
              f(this->processId);
              f(this->processingTime);
              f(this->ramUtilization);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
