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
#ifndef AC_DM_DATA_ELEMENT_UINT32_DATAELEMENT_UINT32_PROXY_H
#define AC_DM_DATA_ELEMENT_UINT32_DATAELEMENT_UINT32_PROXY_H

// -- Inclusion of common header file
#include "dataelement_uint32_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace data_element_uint32
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::proxy::Method<::ac::dm::data_element_uint32::DataElement_uint32::Cancel>;
          using Read = ::ara::com::internal::proxy::Method<::ac::dm::data_element_uint32::DataElement_uint32::Read>;
        }// namespace methods

        // -- Service proxy class
        class DataElement_uint32Proxy : public ::ara::com::internal::proxy::Proxy<DataElement_uint32>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DataElement_uint32>::HandleType;

          // -- Creation of service proxy
          explicit DataElement_uint32Proxy(HandleType& handle)
          : Proxy<DataElement_uint32>(handle)
          , Cancel(port_link())
          , Read(port_link())
          {}

          public:
          // -- Methods
          methods::Cancel Cancel;
          methods::Read Read;

        };
      }// namespace proxy
    }// namespace data_element_uint32
  }// namespace dm
}// namespace ac
#endif
