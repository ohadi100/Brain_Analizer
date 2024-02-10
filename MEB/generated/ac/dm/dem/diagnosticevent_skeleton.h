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
#ifndef AC_DM_DEM_DIAGNOSTICEVENT_SKELETON_H
#define AC_DM_DEM_DIAGNOSTICEVENT_SKELETON_H

// -- Inclusion of common header file
#include "diagnosticevent_common.h"

#include "ara/com/internal/skeleton/field.hpp"
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
        // -- Service fields namespace
        namespace fields
        {
          using EventStatus = ::ara::com::internal::skeleton::Field<::ac::dm::dem::DiagnosticEvent::EventStatus>;
        }// namespace fields

        // -- Service methods namespace
        namespace methods
        {
          using FaultDetectionCounter = ::ara::com::internal::skeleton::Method<::ac::dm::dem::DiagnosticEvent::FaultDetectionCounter>;
          using GetDTCOfEvent = ::ara::com::internal::skeleton::Method<::ac::dm::dem::DiagnosticEvent::GetDTCOfEvent>;
          using GetDebouncingOfEvent = ::ara::com::internal::skeleton::Method<::ac::dm::dem::DiagnosticEvent::GetDebouncingOfEvent>;
        }// namespace methods

        // -- Service skeleton class
        class DiagnosticEventSkeleton : public ::ara::com::internal::skeleton::Skeleton<DiagnosticEvent>
        {
          public:
          // -- Creation of service skeleton
          DiagnosticEventSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , EventStatus (field_handler(), method_dispatcher())
          , m_FaultDetectionCounter(method_dispatcher(),[this]() { return FaultDetectionCounter();})
          , m_GetDTCOfEvent(method_dispatcher(),[this](::ac::dm::types::DTCFormatType DTCFormat) { return GetDTCOfEvent(DTCFormat);})
          , m_GetDebouncingOfEvent(method_dispatcher(),[this]() { return GetDebouncingOfEvent();})
          {}

          // -- Provision of method
          using FaultDetectionCounterOutput = ::ac::dm::dem::DiagnosticEvent::FaultDetectionCounter::Output;
          virtual ::ara::com::Future<FaultDetectionCounterOutput>
          FaultDetectionCounter() = 0;

          using GetDTCOfEventOutput = ::ac::dm::dem::DiagnosticEvent::GetDTCOfEvent::Output;
          virtual ::ara::com::Future<GetDTCOfEventOutput>
          GetDTCOfEvent(::ac::dm::types::DTCFormatType DTCFormat) = 0;

          using GetDebouncingOfEventOutput = ::ac::dm::dem::DiagnosticEvent::GetDebouncingOfEvent::Output;
          virtual ::ara::com::Future<GetDebouncingOfEventOutput>
          GetDebouncingOfEvent() = 0;

          public:
          // -- Fields
          fields::EventStatus EventStatus;
          private:
          // -- Methods
          methods::FaultDetectionCounter m_FaultDetectionCounter;
          methods::GetDTCOfEvent m_GetDTCOfEvent;
          methods::GetDebouncingOfEvent m_GetDebouncingOfEvent;
        };
      }// namespace skeleton
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
