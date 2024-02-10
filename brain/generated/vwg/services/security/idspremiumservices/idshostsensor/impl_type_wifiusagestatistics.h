/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_WIFIUSAGESTATISTICS_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_WIFIUSAGESTATISTICS_H

#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wifiusagestatistics_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "ara/stdtypes/impl_type_uint16.h"
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
          struct WifiUsageStatistics
          {
            WifiUsageStatistics_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 connectionType{};
            ::ara::stdtypes::UInt16 layerType{};
            ::ara::stdtypes::UInt32 newSessionsCount{};
            ::ara::stdtypes::UInt32 totalPassedPackets{};
            ::ara::stdtypes::UInt64 totalPassedBytes{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectionType);
              f(this->layerType);
              f(this->newSessionsCount);
              f(this->totalPassedPackets);
              f(this->totalPassedBytes);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->connectionType);
              f(this->layerType);
              f(this->newSessionsCount);
              f(this->totalPassedPackets);
              f(this->totalPassedBytes);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
