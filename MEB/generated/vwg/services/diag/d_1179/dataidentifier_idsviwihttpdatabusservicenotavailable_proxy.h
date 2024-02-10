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
#ifndef VWG_SERVICES_DIAG_D_1179_DATAIDENTIFIER_IDSVIWIHTTPDATABUSSERVICENOTAVAILABLE_PROXY_H
#define VWG_SERVICES_DIAG_D_1179_DATAIDENTIFIER_IDSVIWIHTTPDATABUSSERVICENOTAVAILABLE_PROXY_H

// -- Inclusion of common header file
#include "dataidentifier_idsviwihttpdatabusservicenotavailable_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_1179
      {

        // -- Service proxy namespace
        namespace proxy
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_1179::DataIdentifier_IDSViwiHttpDataBusServiceNotAvailable::Cancel>;
            using Read = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_1179::DataIdentifier_IDSViwiHttpDataBusServiceNotAvailable::Read>;
          }// namespace methods

          // -- Service proxy class
          class DataIdentifier_IDSViwiHttpDataBusServiceNotAvailableProxy : public ::ara::com::internal::proxy::Proxy<DataIdentifier_IDSViwiHttpDataBusServiceNotAvailable>
          {
            public:
            // -- HandleType class
            using HandleType = ::ara::com::internal::proxy::Proxy<DataIdentifier_IDSViwiHttpDataBusServiceNotAvailable>::HandleType;

            // -- Creation of service proxy
            explicit DataIdentifier_IDSViwiHttpDataBusServiceNotAvailableProxy(HandleType& handle)
            : Proxy<DataIdentifier_IDSViwiHttpDataBusServiceNotAvailable>(handle)
            , Cancel(port_link())
            , Read(port_link())
            {}

            public:
            // -- Methods
            methods::Cancel Cancel;
            methods::Read Read;

          };
        }// namespace proxy
      }// namespace d_1179
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
