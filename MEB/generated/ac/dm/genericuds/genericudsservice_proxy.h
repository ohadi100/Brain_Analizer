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
#ifndef AC_DM_GENERICUDS_GENERICUDSSERVICE_PROXY_H
#define AC_DM_GENERICUDS_GENERICUDSSERVICE_PROXY_H

// -- Inclusion of common header file
#include "genericudsservice_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace genericuds
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::proxy::Method<::ac::dm::genericuds::GenericUDSService::Cancel>;
          using HandleMessage = ::ara::com::internal::proxy::Method<::ac::dm::genericuds::GenericUDSService::HandleMessage>;
        }// namespace methods

        // -- Service proxy class
        class GenericUDSServiceProxy : public ::ara::com::internal::proxy::Proxy<GenericUDSService>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<GenericUDSService>::HandleType;

          // -- Creation of service proxy
          explicit GenericUDSServiceProxy(HandleType& handle)
          : Proxy<GenericUDSService>(handle)
          , Cancel(port_link())
          , HandleMessage(port_link())
          {}

          public:
          // -- Methods
          methods::Cancel Cancel;
          methods::HandleMessage HandleMessage;

        };
      }// namespace proxy
    }// namespace genericuds
  }// namespace dm
}// namespace ac
#endif
