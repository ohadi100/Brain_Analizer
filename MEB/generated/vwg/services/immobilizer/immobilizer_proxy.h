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
#ifndef VWG_SERVICES_IMMOBILIZER_IMMOBILIZER_PROXY_H
#define VWG_SERVICES_IMMOBILIZER_IMMOBILIZER_PROXY_H

// -- Inclusion of common header file
#include "immobilizer_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace immobilizer
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using info = ::ara::com::internal::proxy::Field<::vwg::services::immobilizer::Immobilizer::info>;
          using notifications = ::ara::com::internal::proxy::Field<::vwg::services::immobilizer::Immobilizer::notifications>;
        }// namespace fields

        // -- Service proxy class
        class ImmobilizerProxy : public ::ara::com::internal::proxy::Proxy<Immobilizer>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<Immobilizer>::HandleType;

          // -- Creation of service proxy
          explicit ImmobilizerProxy(HandleType& handle)
          : Proxy<Immobilizer>(handle)
          , info(handle.GetInstanceId(), port_link())
          , notifications(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::info info;
          fields::notifications notifications;

        };
      }// namespace proxy
    }// namespace immobilizer
  }// namespace services
}// namespace vwg
#endif
