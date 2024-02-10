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
#ifndef AC_DM_DATA_ELEMENT_VECTOR_UINT8_DATAELEMENT_VECTOR_UINT8_PROXY_H
#define AC_DM_DATA_ELEMENT_VECTOR_UINT8_DATAELEMENT_VECTOR_UINT8_PROXY_H

// -- Inclusion of common header file
#include "dataelement_vector_uint8_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace data_element_vector_uint8
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::proxy::Method<::ac::dm::data_element_vector_uint8::DataElement_vector_uint8::Cancel>;
          using Read = ::ara::com::internal::proxy::Method<::ac::dm::data_element_vector_uint8::DataElement_vector_uint8::Read>;
        }// namespace methods

        // -- Service proxy class
        class DataElement_vector_uint8Proxy : public ::ara::com::internal::proxy::Proxy<DataElement_vector_uint8>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DataElement_vector_uint8>::HandleType;

          // -- Creation of service proxy
          explicit DataElement_vector_uint8Proxy(HandleType& handle)
          : Proxy<DataElement_vector_uint8>(handle)
          , Cancel(port_link())
          , Read(port_link())
          {}

          public:
          // -- Methods
          methods::Cancel Cancel;
          methods::Read Read;

        };
      }// namespace proxy
    }// namespace data_element_vector_uint8
  }// namespace dm
}// namespace ac
#endif
