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
#ifndef VWG_SERVICES_DIAG_D_4943_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMNUMBEROFALERTS_PROXY_H
#define VWG_SERVICES_DIAG_D_4943_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMNUMBEROFALERTS_PROXY_H

// -- Inclusion of common header file
#include "dataidentifier_intrusiondetectionsystemnumberofalerts_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_4943
      {

        // -- Service proxy namespace
        namespace proxy
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_4943::DataIdentifier_IntrusionDetectionSystemNumberOfAlerts::Cancel>;
            using Read = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_4943::DataIdentifier_IntrusionDetectionSystemNumberOfAlerts::Read>;
          }// namespace methods

          // -- Service proxy class
          class DataIdentifier_IntrusionDetectionSystemNumberOfAlertsProxy : public ::ara::com::internal::proxy::Proxy<DataIdentifier_IntrusionDetectionSystemNumberOfAlerts>
          {
            public:
            // -- HandleType class
            using HandleType = ::ara::com::internal::proxy::Proxy<DataIdentifier_IntrusionDetectionSystemNumberOfAlerts>::HandleType;

            // -- Creation of service proxy
            explicit DataIdentifier_IntrusionDetectionSystemNumberOfAlertsProxy(HandleType& handle)
            : Proxy<DataIdentifier_IntrusionDetectionSystemNumberOfAlerts>(handle)
            , Cancel(port_link())
            , Read(port_link())
            {}

            public:
            // -- Methods
            methods::Cancel Cancel;
            methods::Read Read;

          };
        }// namespace proxy
      }// namespace d_4943
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
