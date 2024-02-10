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
#ifndef VWG_SERVICES_IDSSECURITYEVENT_IDSSECURITYEVENT_PROXY_H
#define VWG_SERVICES_IDSSECURITYEVENT_IDSSECURITYEVENT_PROXY_H

// -- Inclusion of common header file
#include "idssecurityevent_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idssecurityevent
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using securityEvent = ::ara::com::internal::proxy::Field<::vwg::services::idssecurityevent::IDSSecurityEvent::securityEvent>;
        }// namespace fields

        // -- Service proxy class
        class IDSSecurityEventProxy : public ::ara::com::internal::proxy::Proxy<IDSSecurityEvent>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<IDSSecurityEvent>::HandleType;

          // -- Creation of service proxy
          explicit IDSSecurityEventProxy(HandleType& handle)
          : Proxy<IDSSecurityEvent>(handle)
          , securityEvent(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::securityEvent securityEvent;

        };
      }// namespace proxy
    }// namespace idssecurityevent
  }// namespace services
}// namespace vwg
#endif
