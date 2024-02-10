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
#ifndef VWG_SERVICES_TIME_TIME_SKELETON_H
#define VWG_SERVICES_TIME_TIME_SKELETON_H

// -- Inclusion of common header file
#include "time_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace time
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using timeSettings = ::ara::com::internal::skeleton::Field<::vwg::services::time::Time::timeSettings>;
          using times = ::ara::com::internal::skeleton::Field<::vwg::services::time::Time::times>;
        }// namespace fields

        // -- Service skeleton class
        class TimeSkeleton : public ::ara::com::internal::skeleton::Skeleton<Time>
        {
          public:
          // -- Creation of service skeleton
          TimeSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , timeSettings (field_handler(), method_dispatcher())
          , times (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::timeSettings timeSettings;
          fields::times times;
        };
      }// namespace skeleton
    }// namespace time
  }// namespace services
}// namespace vwg
#endif
