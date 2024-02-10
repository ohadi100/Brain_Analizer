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
#ifndef AC_DM_DEM_DIAGNOSTICMONITOR_PROXY_H
#define AC_DM_DEM_DIAGNOSTICMONITOR_PROXY_H

// -- Inclusion of common header file
#include "diagnosticmonitor_common.h"

#include "ara/com/internal/proxy/event.hpp"
#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace dem
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service events namespace
        namespace events
        {
          using MonitorAction = ::ara::com::internal::proxy::Event<::ac::dm::dem::DiagnosticMonitor::MonitorAction>;
        }// namespace events

        // -- Service methods namespace
        namespace methods
        {
          using InitMonitor = ::ara::com::internal::proxy::Method<::ac::dm::dem::DiagnosticMonitor::InitMonitor>;
        }// namespace methods

        // -- Service proxy class
        class DiagnosticMonitorProxy : public ::ara::com::internal::proxy::Proxy<DiagnosticMonitor>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DiagnosticMonitor>::HandleType;

          // -- Creation of service proxy
          explicit DiagnosticMonitorProxy(HandleType& handle)
          : Proxy<DiagnosticMonitor>(handle)
          , MonitorAction(handle.GetInstanceId(), port_link())
          , InitMonitor(port_link())
          {}

          public:
          // -- Events
          events::MonitorAction MonitorAction;

          // -- Methods
          methods::InitMonitor InitMonitor;

        };
      }// namespace proxy
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
