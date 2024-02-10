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
#ifndef VWG_SERVICES_DIAG_D_4944_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMGETLOG_PROXY_H
#define VWG_SERVICES_DIAG_D_4944_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMGETLOG_PROXY_H

// -- Inclusion of common header file
#include "dataidentifier_intrusiondetectionsystemgetlog_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_4944
      {

        // -- Service proxy namespace
        namespace proxy
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_4944::DataIdentifier_IntrusionDetectionSystemGetLog::Cancel>;
            using Read = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_4944::DataIdentifier_IntrusionDetectionSystemGetLog::Read>;
          }// namespace methods

          // -- Service proxy class
          class DataIdentifier_IntrusionDetectionSystemGetLogProxy : public ::ara::com::internal::proxy::Proxy<DataIdentifier_IntrusionDetectionSystemGetLog>
          {
            public:
            // -- HandleType class
            using HandleType = ::ara::com::internal::proxy::Proxy<DataIdentifier_IntrusionDetectionSystemGetLog>::HandleType;

            // -- Creation of service proxy
            explicit DataIdentifier_IntrusionDetectionSystemGetLogProxy(HandleType& handle)
            : Proxy<DataIdentifier_IntrusionDetectionSystemGetLog>(handle)
            , Cancel(port_link())
            , Read(port_link())
            {}

            public:
            // -- Methods
            methods::Cancel Cancel;
            methods::Read Read;

          };
        }// namespace proxy
      }// namespace d_4944
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
