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
#ifndef VWG_SERVICES_IDSETHERNETSENSOR_IDSETHERNETSENSOR_SKELETON_H
#define VWG_SERVICES_IDSETHERNETSENSOR_IDSETHERNETSENSOR_SKELETON_H

// -- Inclusion of common header file
#include "idsethernetsensor_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idsethernetsensor
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using classifierMatchReports = ::ara::com::internal::skeleton::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::classifierMatchReports>;
          using portStatistics = ::ara::com::internal::skeleton::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::portStatistics>;
          using serviceDiscoveryReports = ::ara::com::internal::skeleton::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::serviceDiscoveryReports>;
          using specialFrameReports = ::ara::com::internal::skeleton::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::specialFrameReports>;
          using trafficFlowSamples = ::ara::com::internal::skeleton::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::trafficFlowSamples>;
        }// namespace fields

        // -- Service skeleton class
        class IDSEthernetSensorSkeleton : public ::ara::com::internal::skeleton::Skeleton<IDSEthernetSensor>
        {
          public:
          // -- Creation of service skeleton
          IDSEthernetSensorSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , classifierMatchReports (field_handler(), method_dispatcher())
          , portStatistics (field_handler(), method_dispatcher())
          , serviceDiscoveryReports (field_handler(), method_dispatcher())
          , specialFrameReports (field_handler(), method_dispatcher())
          , trafficFlowSamples (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::classifierMatchReports classifierMatchReports;
          fields::portStatistics portStatistics;
          fields::serviceDiscoveryReports serviceDiscoveryReports;
          fields::specialFrameReports specialFrameReports;
          fields::trafficFlowSamples trafficFlowSamples;
        };
      }// namespace skeleton
    }// namespace idsethernetsensor
  }// namespace services
}// namespace vwg
#endif
