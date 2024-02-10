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
#ifndef AC_DM_DEM_DTCINFORMATION_SKELETON_H
#define AC_DM_DEM_DTCINFORMATION_SKELETON_H

// -- Inclusion of common header file
#include "dtcinformation_common.h"

#include "ara/com/internal/skeleton/event.hpp"
#include "ara/com/internal/skeleton/method.hpp"
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
        // -- Service events namespace
        namespace events
        {
          using DTCStatusChanged = ::ara::com::internal::skeleton::Event<::ac::dm::dem::DTCInformation::DTCStatusChanged>;
        }// namespace events

        // -- Service methods namespace
        namespace methods
        {
          using GetCurrentStatus = ::ara::com::internal::skeleton::Method<::ac::dm::dem::DTCInformation::GetCurrentStatus>;
        }// namespace methods

        // -- Service skeleton class
        class DTCInformationSkeleton : public ::ara::com::internal::skeleton::Skeleton<DTCInformation>
        {
          public:
          // -- Creation of service skeleton
          DTCInformationSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , DTCStatusChanged (port_link())
          , m_GetCurrentStatus(method_dispatcher(),[this](::ac::dm::types::DTCType DTC) { return GetCurrentStatus(DTC);})
          {}

          // -- Provision of method
          using GetCurrentStatusOutput = ::ac::dm::dem::DTCInformation::GetCurrentStatus::Output;
          virtual ::ara::com::Future<GetCurrentStatusOutput>
          GetCurrentStatus(::ac::dm::types::DTCType DTC) = 0;

          public:
          // -- Events
          events::DTCStatusChanged DTCStatusChanged;
          private:
          // -- Methods
          methods::GetCurrentStatus m_GetCurrentStatus;
        };
      }// namespace skeleton
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
