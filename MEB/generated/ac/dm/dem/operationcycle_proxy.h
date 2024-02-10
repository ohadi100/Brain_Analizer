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
#ifndef AC_DM_DEM_OPERATIONCYCLE_PROXY_H
#define AC_DM_DEM_OPERATIONCYCLE_PROXY_H

// -- Inclusion of common header file
#include "operationcycle_common.h"

#include "ara/com/internal/proxy/field.hpp"
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
          using State = ::ara::com::internal::proxy::Field<::ac::dm::dem::OperationCycle::State>;
        }// namespace fields

        // -- Service proxy class
        class OperationCycleProxy : public ::ara::com::internal::proxy::Proxy<OperationCycle>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<OperationCycle>::HandleType;

          // -- Creation of service proxy
          explicit OperationCycleProxy(HandleType& handle)
          : Proxy<OperationCycle>(handle)
          , State(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::State State;

        };
      }// namespace proxy
    }// namespace dem
  }// namespace dm
}// namespace ac
#endif
