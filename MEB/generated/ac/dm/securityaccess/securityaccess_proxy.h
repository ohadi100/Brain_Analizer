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
#ifndef AC_DM_SECURITYACCESS_SECURITYACCESS_PROXY_H
#define AC_DM_SECURITYACCESS_SECURITYACCESS_PROXY_H

// -- Inclusion of common header file
#include "securityaccess_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace securityaccess
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::proxy::Method<::ac::dm::securityaccess::SecurityAccess::Cancel>;
          using CompareKey = ::ara::com::internal::proxy::Method<::ac::dm::securityaccess::SecurityAccess::CompareKey>;
          using GetSeed = ::ara::com::internal::proxy::Method<::ac::dm::securityaccess::SecurityAccess::GetSeed>;
        }// namespace methods

        // -- Service proxy class
        class SecurityAccessProxy : public ::ara::com::internal::proxy::Proxy<SecurityAccess>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<SecurityAccess>::HandleType;

          // -- Creation of service proxy
          explicit SecurityAccessProxy(HandleType& handle)
          : Proxy<SecurityAccess>(handle)
          , Cancel(port_link())
          , CompareKey(port_link())
          , GetSeed(port_link())
          {}

          public:
          // -- Methods
          methods::Cancel Cancel;
          methods::CompareKey CompareKey;
          methods::GetSeed GetSeed;

        };
      }// namespace proxy
    }// namespace securityaccess
  }// namespace dm
}// namespace ac
#endif
