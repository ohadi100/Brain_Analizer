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
#ifndef VWG_SERVICES_DIAG_D_1176_DATAIDENTIFIER_IDSSOMEIPDATABUSSERVICENOTAVAILABLE_PROXY_H
#define VWG_SERVICES_DIAG_D_1176_DATAIDENTIFIER_IDSSOMEIPDATABUSSERVICENOTAVAILABLE_PROXY_H

// -- Inclusion of common header file
#include "dataidentifier_idssomeipdatabusservicenotavailable_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_1176
      {

        // -- Service proxy namespace
        namespace proxy
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_1176::DataIdentifier_IDSSomeipDataBusServiceNotAvailable::Cancel>;
            using Read = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_1176::DataIdentifier_IDSSomeipDataBusServiceNotAvailable::Read>;
          }// namespace methods

          // -- Service proxy class
          class DataIdentifier_IDSSomeipDataBusServiceNotAvailableProxy : public ::ara::com::internal::proxy::Proxy<DataIdentifier_IDSSomeipDataBusServiceNotAvailable>
          {
            public:
            // -- HandleType class
            using HandleType = ::ara::com::internal::proxy::Proxy<DataIdentifier_IDSSomeipDataBusServiceNotAvailable>::HandleType;

            // -- Creation of service proxy
            explicit DataIdentifier_IDSSomeipDataBusServiceNotAvailableProxy(HandleType& handle)
            : Proxy<DataIdentifier_IDSSomeipDataBusServiceNotAvailable>(handle)
            , Cancel(port_link())
            , Read(port_link())
            {}

            public:
            // -- Methods
            methods::Cancel Cancel;
            methods::Read Read;

          };
        }// namespace proxy
      }// namespace d_1176
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
