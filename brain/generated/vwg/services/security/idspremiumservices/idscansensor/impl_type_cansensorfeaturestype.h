/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_CANSENSORFEATURESTYPE_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_CANSENSORFEATURESTYPE_H

#include "ara/core/optional.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_configurationsettings.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_controlcommands.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_protocolframedata.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_anomalydata.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_gatewayexceptionaldata.h"
#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_gatewaydiagnosticfilterevent.h"
#include "ara/stdtypes/impl_type_uint8.h"

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
          struct CanSensorFeaturesType
          {
            ::ara::core::Optional<ConfigurationSettings> configurationSettings{};
            ::ara::core::Optional<ControlCommands> controlCommands{};
            ::ara::core::Optional<ProtocolFrameData> protocalFrameData{};
            ::ara::core::Optional<AnomalyData> anomalyData{};
            ::ara::core::Optional<GatewayExceptionalData> gatewayExceptionalData{};
            ::ara::core::Optional<GatewayDiagnosticFilterEvent> gatewayDiagnosticFilterEvent{};
            ::ara::stdtypes::UInt8 elementId{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->configurationSettings);
              f(this->controlCommands);
              f(this->protocalFrameData);
              f(this->anomalyData);
              f(this->gatewayExceptionalData);
              f(this->gatewayDiagnosticFilterEvent);
              f(this->elementId);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->configurationSettings);
              f(this->controlCommands);
              f(this->protocalFrameData);
              f(this->anomalyData);
              f(this->gatewayExceptionalData);
              f(this->gatewayDiagnosticFilterEvent);
              f(this->elementId);
            }
          };
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
