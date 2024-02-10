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
#ifndef AC_DM_DEM_DTCINFORMATION_PROXY_H
#define AC_DM_DEM_DTCINFORMATION_PROXY_H

// -- Inclusion of common header file
#include "dtcinformation_common.h"

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
          using DTCStatusChanged = ::ara::com::internal::proxy::Event<::ac::dm::dem::DTCInformation::DTCStatusChanged>;
        }// namespace events

        // -- Service methods namespace
        namespace methods
        {
          using GetCurrentStatus = ::ara::com::internal::proxy::Method<::ac::dm::dem::DTCInformation::GetCurrentStatus>;
        }// namespace methods

        // -- Service proxy class
        class DTCInformationProxy : public ::ara::com::internal::proxy::Proxy<DTCInformation>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DTCInformation>::HandleType;

          // -- Creation of service proxy
          explicit DTCInformationProxy(HandleType& handle)
          : Proxy<DTCInformation>(handle)
          , DTCStatusChanged(handle.GetInstanceId(), port_link())
          , GetCurrentStatus(port_link())
          {}

          public:
          // -- Events
          events::DTCStatusChanged DTCStatusChanged;

          // -- Methods
          methods::GetCurrentStatus GetCurrentStatus;

        };
      }// namespace proxy
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
