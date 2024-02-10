/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_EXTERNALSTORAGECONNECTION_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_EXTERNALSTORAGECONNECTION_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalstorageconnection_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalstorageconnection_serialnumber.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalstorageconnection_mainvolumename.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalstorageconnection_volumessizes.h"

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
          struct ExternalStorageConnection
          {
            ExternalStorageConnection_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 connectionType{};
            ExternalStorageConnection_serialNumber serialNumber{};
            ::ara::stdtypes::UInt8 fileSystemType{};
            ::ara::stdtypes::UInt16 volumeCount{};
            ExternalStorageConnection_mainVolumeName mainVolumeName{};
            ExternalStorageConnection_volumesSizes volumesSizes{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectionType);
              f(this->serialNumber);
              f(this->fileSystemType);
              f(this->volumeCount);
              f(this->mainVolumeName);
              f(this->volumesSizes);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectionType);
              f(this->serialNumber);
              f(this->fileSystemType);
              f(this->volumeCount);
              f(this->mainVolumeName);
              f(this->volumesSizes);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
