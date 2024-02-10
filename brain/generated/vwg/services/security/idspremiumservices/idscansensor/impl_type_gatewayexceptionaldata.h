/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_GATEWAYEXCEPTIONALDATA_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_GATEWAYEXCEPTIONALDATA_H

#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_gatewayexceptionaldata_sensoridentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint8.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_gatewayexceptionaldata_messagepayload.h"

namespace vwg
{
  namespace services
  {
    namespace security
    {
      namespace idspremiumservices
      {
        namespace idscansensor
        {
          struct GatewayExceptionalData
          {
            GatewayExceptionalData_sensorIdentifier sensorIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt8 canIdentifierType{};
            ::ara::stdtypes::UInt16 canBusIdentifier{};
            GatewayExceptionalData_messagePayload messagePayload{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->canIdentifierType);
              f(this->canBusIdentifier);
              f(this->messagePayload);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sensorIdentifier);
              f(this->timestamp);
              f(this->canIdentifierType);
              f(this->canBusIdentifier);
              f(this->messagePayload);
            }
          };
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
