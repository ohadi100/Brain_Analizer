/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_HOSTSENSORFEATURESTYPE_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSHOSTSENSOR_IMPL_TYPE_HOSTSENSORFEATURESTYPE_H

#include "ara/core/optional.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_incidentdata.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_configurationsettings.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_controlcommands.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_serviceapplicationnotification.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_watchdognotification.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_vminstanceperfinfo.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_vmprocessperfinfo.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_criticalerrorinformation.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_securityeventlogcontents.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_processstartstoppnotification.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalitemreceptionnotification.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_cryptographicincidentnotification.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_hashmismatchnotification.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_teeapplicationinvokation.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_teeapplicationinstallation.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionsuccess.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificonnectionfailure.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wifinewbinding.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wifiusagestatistics.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_wificlientarpmessage.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalstorageconnection.h"
#include "vwg/services/security/idspremiumservices/idshostsensor/impl_type_externalhardwareconnection.h"
#include "ara/stdtypes/impl_type_uint8.h"

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
          struct HostSensorFeaturesType
          {
            ::ara::core::Optional<IncidentData> incidentData{};
            ::ara::core::Optional<ConfigurationSettings> configurationSettings{};
            ::ara::core::Optional<ControlCommands> controlCommands{};
            ::ara::core::Optional<ServiceApplicationNotification> serviceApplicationNotification{};
            ::ara::core::Optional<WatchdogNotification> watchdogNotification{};
            ::ara::core::Optional<VmInstancePerfInfo> vmInstancePerfInfo{};
            ::ara::core::Optional<VmProcessPerfInfo> vmProcessPerfInfo{};
            ::ara::core::Optional<CriticalErrorInformation> criticalErrorInformation{};
            ::ara::core::Optional<SecurityEventLogContents> securityEventLogContents{};
            ::ara::core::Optional<ProcessStartStoppNotification> processStartStoppNotification{};
            ::ara::core::Optional<ExternalItemReceptionNotification> externalItemReceptionNotification{};
            ::ara::core::Optional<CryptographicIncidentNotification> cryptographicIncidentNotification{};
            ::ara::core::Optional<HashMismatchNotification> hashMismatchNotification{};
            ::ara::core::Optional<TeeApplicationInvokation> teeApplicationInvokation{};
            ::ara::core::Optional<TeeApplicationInstallation> teeApplicationInstallation{};
            ::ara::core::Optional<WifiConnectionSuccess> wifiConnectionSuccess{};
            ::ara::core::Optional<WifiConnectionFailure> wifiConnectionFailure{};
            ::ara::core::Optional<WifiNewBinding> wifiNewBinding{};
            ::ara::core::Optional<WifiUsageStatistics> wifiUsageStatistics{};
            ::ara::core::Optional<WifiClientArpMessage> wifiClientArpMessage{};
            ::ara::core::Optional<ExternalStorageConnection> externalStorageConnection{};
            ::ara::core::Optional<ExternalHardwareConnection> externalHardwareConnection{};
            ::ara::stdtypes::UInt8 elementId{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->incidentData);
              f(this->configurationSettings);
              f(this->controlCommands);
              f(this->serviceApplicationNotification);
              f(this->watchdogNotification);
              f(this->vmInstancePerfInfo);
              f(this->vmProcessPerfInfo);
              f(this->criticalErrorInformation);
              f(this->securityEventLogContents);
              f(this->processStartStoppNotification);
              f(this->externalItemReceptionNotification);
              f(this->cryptographicIncidentNotification);
              f(this->hashMismatchNotification);
              f(this->teeApplicationInvokation);
              f(this->teeApplicationInstallation);
              f(this->wifiConnectionSuccess);
              f(this->wifiConnectionFailure);
              f(this->wifiNewBinding);
              f(this->wifiUsageStatistics);
              f(this->wifiClientArpMessage);
              f(this->externalStorageConnection);
              f(this->externalHardwareConnection);
              f(this->elementId);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->incidentData);
              f(this->configurationSettings);
              f(this->controlCommands);
              f(this->serviceApplicationNotification);
              f(this->watchdogNotification);
              f(this->vmInstancePerfInfo);
              f(this->vmProcessPerfInfo);
              f(this->criticalErrorInformation);
              f(this->securityEventLogContents);
              f(this->processStartStoppNotification);
              f(this->externalItemReceptionNotification);
              f(this->cryptographicIncidentNotification);
              f(this->hashMismatchNotification);
              f(this->teeApplicationInvokation);
              f(this->teeApplicationInstallation);
              f(this->wifiConnectionSuccess);
              f(this->wifiConnectionFailure);
              f(this->wifiNewBinding);
              f(this->wifiUsageStatistics);
              f(this->wifiClientArpMessage);
              f(this->externalStorageConnection);
              f(this->externalHardwareConnection);
              f(this->elementId);
            }
          };
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
