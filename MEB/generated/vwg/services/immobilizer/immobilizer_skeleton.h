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
#ifndef VWG_SERVICES_IMMOBILIZER_IMMOBILIZER_SKELETON_H
#define VWG_SERVICES_IMMOBILIZER_IMMOBILIZER_SKELETON_H

// -- Inclusion of common header file
#include "immobilizer_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace immobilizer
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using info = ::ara::com::internal::skeleton::Field<::vwg::services::immobilizer::Immobilizer::info>;
          using notifications = ::ara::com::internal::skeleton::Field<::vwg::services::immobilizer::Immobilizer::notifications>;
        }// namespace fields

        // -- Service skeleton class
        class ImmobilizerSkeleton : public ::ara::com::internal::skeleton::Skeleton<Immobilizer>
        {
          public:
          // -- Creation of service skeleton
          ImmobilizerSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , info (field_handler(), method_dispatcher())
          , notifications (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::info info;
          fields::notifications notifications;
        };
      }// namespace skeleton
    }// namespace immobilizer
  }// namespace services
}// namespace vwg
#endif
