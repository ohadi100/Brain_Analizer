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
#ifndef AC_DM_DEM_DIAGNOSTICEVENT_PROXY_H
#define AC_DM_DEM_DIAGNOSTICEVENT_PROXY_H

// -- Inclusion of common header file
#include "diagnosticevent_common.h"

#include "ara/com/internal/proxy/field.hpp"
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

        // -- Service fields namespace
        namespace fields
        {
          using EventStatus = ::ara::com::internal::proxy::Field<::ac::dm::dem::DiagnosticEvent::EventStatus>;
        }// namespace fields

        // -- Service methods namespace
        namespace methods
        {
          using FaultDetectionCounter = ::ara::com::internal::proxy::Method<::ac::dm::dem::DiagnosticEvent::FaultDetectionCounter>;
          using GetDTCOfEvent = ::ara::com::internal::proxy::Method<::ac::dm::dem::DiagnosticEvent::GetDTCOfEvent>;
          using GetDebouncingOfEvent = ::ara::com::internal::proxy::Method<::ac::dm::dem::DiagnosticEvent::GetDebouncingOfEvent>;
        }// namespace methods

        // -- Service proxy class
        class DiagnosticEventProxy : public ::ara::com::internal::proxy::Proxy<DiagnosticEvent>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DiagnosticEvent>::HandleType;

          // -- Creation of service proxy
          explicit DiagnosticEventProxy(HandleType& handle)
          : Proxy<DiagnosticEvent>(handle)
          , EventStatus(handle.GetInstanceId(), port_link())
          , FaultDetectionCounter(port_link())
          , GetDTCOfEvent(port_link())
          , GetDebouncingOfEvent(port_link())
          {}

          public:
          // -- Fields
          fields::EventStatus EventStatus;

          // -- Methods
          methods::FaultDetectionCounter FaultDetectionCounter;
          methods::GetDTCOfEvent GetDTCOfEvent;
          methods::GetDebouncingOfEvent GetDebouncingOfEvent;

        };
      }// namespace proxy
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
