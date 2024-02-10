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
#ifndef VWG_SERVICES_IDSIPSECURITYSENSOR_IDSIPSECURITYSENSOR_SKELETON_H
#define VWG_SERVICES_IDSIPSECURITYSENSOR_IDSIPSECURITYSENSOR_SKELETON_H

// -- Inclusion of common header file
#include "idsipsecuritysensor_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idsipsecuritysensor
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using firewallFilterReports = ::ara::com::internal::skeleton::Field<::vwg::services::idsipsecuritysensor::IDSIpSecuritySensor::firewallFilterReports>;
        }// namespace fields

        // -- Service skeleton class
        class IDSIpSecuritySensorSkeleton : public ::ara::com::internal::skeleton::Skeleton<IDSIpSecuritySensor>
        {
          public:
          // -- Creation of service skeleton
          IDSIpSecuritySensorSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , firewallFilterReports (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::firewallFilterReports firewallFilterReports;
        };
      }// namespace skeleton
    }// namespace idsipsecuritysensor
  }// namespace services
}// namespace vwg
#endif
