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
#ifndef AC_DM_DATA_ELEMENT_UINT16_DATAELEMENT_UINT16_PROXY_H
#define AC_DM_DATA_ELEMENT_UINT16_DATAELEMENT_UINT16_PROXY_H

// -- Inclusion of common header file
#include "dataelement_uint16_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace data_element_uint16
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::proxy::Method<::ac::dm::data_element_uint16::DataElement_uint16::Cancel>;
          using Read = ::ara::com::internal::proxy::Method<::ac::dm::data_element_uint16::DataElement_uint16::Read>;
        }// namespace methods

        // -- Service proxy class
        class DataElement_uint16Proxy : public ::ara::com::internal::proxy::Proxy<DataElement_uint16>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DataElement_uint16>::HandleType;

          // -- Creation of service proxy
          explicit DataElement_uint16Proxy(HandleType& handle)
          : Proxy<DataElement_uint16>(handle)
          , Cancel(port_link())
          , Read(port_link())
          {}

          public:
          // -- Methods
          methods::Cancel Cancel;
          methods::Read Read;

        };
      }// namespace proxy
    }// namespace data_element_uint16
  }// namespace dm
}// namespace ac
#endif
