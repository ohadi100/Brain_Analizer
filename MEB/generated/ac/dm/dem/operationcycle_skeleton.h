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
#ifndef AC_DM_DEM_OPERATIONCYCLE_SKELETON_H
#define AC_DM_DEM_OPERATIONCYCLE_SKELETON_H

// -- Inclusion of common header file
#include "operationcycle_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace dem
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using State = ::ara::com::internal::skeleton::Field<::ac::dm::dem::OperationCycle::State>;
        }// namespace fields

        // -- Service skeleton class
        class OperationCycleSkeleton : public ::ara::com::internal::skeleton::Skeleton<OperationCycle>
        {
          public:
          // -- Creation of service skeleton
          OperationCycleSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , State (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::State State;
        };
      }// namespace skeleton
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
