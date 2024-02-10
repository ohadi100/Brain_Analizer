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
#ifndef VWG_SERVICES_DIAG_D_117B_DATAIDENTIFIER_IDSVIWIHTTPDATABUSSERVICESERVICEINCCORECTMISSINGENCODING_PROXY_H
#define VWG_SERVICES_DIAG_D_117B_DATAIDENTIFIER_IDSVIWIHTTPDATABUSSERVICESERVICEINCCORECTMISSINGENCODING_PROXY_H

// -- Inclusion of common header file
#include "dataidentifier_idsviwihttpdatabusserviceserviceinccorectmissingencoding_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_117b
      {

        // -- Service proxy namespace
        namespace proxy
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_117b::DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding::Cancel>;
            using Read = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_117b::DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding::Read>;
          }// namespace methods

          // -- Service proxy class
          class DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncodingProxy : public ::ara::com::internal::proxy::Proxy<DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding>
          {
            public:
            // -- HandleType class
            using HandleType = ::ara::com::internal::proxy::Proxy<DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding>::HandleType;

            // -- Creation of service proxy
            explicit DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncodingProxy(HandleType& handle)
            : Proxy<DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding>(handle)
            , Cancel(port_link())
            , Read(port_link())
            {}

            public:
            // -- Methods
            methods::Cancel Cancel;
            methods::Read Read;

          };
        }// namespace proxy
      }// namespace d_117b
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
