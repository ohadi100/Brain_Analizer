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
#ifndef VWG_SERVICES_IDSCOREDUMPSENSOR_IDSCOREDUMPSENSOR_SKELETON_H
#define VWG_SERVICES_IDSCOREDUMPSENSOR_IDSCOREDUMPSENSOR_SKELETON_H

// -- Inclusion of common header file
#include "idscoredumpsensor_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idscoredumpsensor
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using coreDumpReports = ::ara::com::internal::skeleton::Field<::vwg::services::idscoredumpsensor::IDSCoreDumpSensor::coreDumpReports>;
        }// namespace fields

        // -- Service skeleton class
        class IDSCoreDumpSensorSkeleton : public ::ara::com::internal::skeleton::Skeleton<IDSCoreDumpSensor>
        {
          public:
          // -- Creation of service skeleton
          IDSCoreDumpSensorSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , coreDumpReports (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::coreDumpReports coreDumpReports;
        };
      }// namespace skeleton
    }// namespace idscoredumpsensor
  }// namespace services
}// namespace vwg
#endif
