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
#ifndef VWG_SERVICES_TIME_TIME_PROXY_H
#define VWG_SERVICES_TIME_TIME_PROXY_H

// -- Inclusion of common header file
#include "time_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace time
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using timeSettings = ::ara::com::internal::proxy::Field<::vwg::services::time::Time::timeSettings>;
          using times = ::ara::com::internal::proxy::Field<::vwg::services::time::Time::times>;
        }// namespace fields

        // -- Service proxy class
        class TimeProxy : public ::ara::com::internal::proxy::Proxy<Time>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<Time>::HandleType;

          // -- Creation of service proxy
          explicit TimeProxy(HandleType& handle)
          : Proxy<Time>(handle)
          , timeSettings(handle.GetInstanceId(), port_link())
          , times(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::timeSettings timeSettings;
          fields::times times;

        };
      }// namespace proxy
    }// namespace time
  }// namespace services
}// namespace vwg
#endif
