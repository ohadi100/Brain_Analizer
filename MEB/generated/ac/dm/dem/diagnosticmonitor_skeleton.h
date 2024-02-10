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
#ifndef AC_DM_DEM_DIAGNOSTICMONITOR_SKELETON_H
#define AC_DM_DEM_DIAGNOSTICMONITOR_SKELETON_H

// -- Inclusion of common header file
#include "diagnosticmonitor_common.h"

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
          using MonitorAction = ::ara::com::internal::skeleton::Event<::ac::dm::dem::DiagnosticMonitor::MonitorAction>;
        }// namespace events

        // -- Service methods namespace
        namespace methods
        {
          using InitMonitor = ::ara::com::internal::skeleton::Method<::ac::dm::dem::DiagnosticMonitor::InitMonitor>;
        }// namespace methods

        // -- Service skeleton class
        class DiagnosticMonitorSkeleton : public ::ara::com::internal::skeleton::Skeleton<DiagnosticMonitor>
        {
          public:
          // -- Creation of service skeleton
          DiagnosticMonitorSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , MonitorAction (port_link())
          , m_InitMonitor(method_dispatcher(),[this](::ac::dm::types::InitMonitorReasonType reason) { return InitMonitor(reason);})
          {}

          // -- Provision of method
          using InitMonitorOutput = ::ac::dm::dem::DiagnosticMonitor::InitMonitor::Output;
          virtual ::ara::com::Future<InitMonitorOutput>
          InitMonitor(::ac::dm::types::InitMonitorReasonType reason) = 0;

          public:
          // -- Events
          events::MonitorAction MonitorAction;
          private:
          // -- Methods
          methods::InitMonitor m_InitMonitor;
        };
      }// namespace skeleton
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
