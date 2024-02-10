/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Service header files existence

// -- Inclusion protection
#ifndef VWG_SERVICES_IDSIPSECURITYSENSOR_IDSIPSECURITYSENSOR_PROXY_H
#define VWG_SERVICES_IDSIPSECURITYSENSOR_IDSIPSECURITYSENSOR_PROXY_H

// -- Inclusion of common header file
#include "idsipsecuritysensor_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idsipsecuritysensor
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using firewallFilterReports = ::ara::com::internal::proxy::Field<::vwg::services::idsipsecuritysensor::IDSIpSecuritySensor::firewallFilterReports>;
        }// namespace fields

        // -- Service proxy class
        class IDSIpSecuritySensorProxy : public ::ara::com::internal::proxy::Proxy<IDSIpSecuritySensor>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<IDSIpSecuritySensor>::HandleType;

          // -- Creation of service proxy
          explicit IDSIpSecuritySensorProxy(HandleType& handle)
          : Proxy<IDSIpSecuritySensor>(handle)
          , firewallFilterReports(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::firewallFilterReports firewallFilterReports;

        };
      }// namespace proxy
    }// namespace idsipsecuritysensor
  }// namespace services
}// namespace vwg
#endif
