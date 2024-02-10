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
#ifndef VWG_SERVICES_DIAG_D_4942_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMTIMINGICAS1ANOMALIES_PROXY_H
#define VWG_SERVICES_DIAG_D_4942_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMTIMINGICAS1ANOMALIES_PROXY_H

// -- Inclusion of common header file
#include "dataidentifier_intrusiondetectionsystemtimingicas1anomalies_common.h"

#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_4942
      {

        // -- Service proxy namespace
        namespace proxy
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_4942::DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies::Cancel>;
            using Read = ::ara::com::internal::proxy::Method<::vwg::services::diag::d_4942::DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies::Read>;
          }// namespace methods

          // -- Service proxy class
          class DataIdentifier_IntrusionDetectionSystemTimingICAS1AnomaliesProxy : public ::ara::com::internal::proxy::Proxy<DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies>
          {
            public:
            // -- HandleType class
            using HandleType = ::ara::com::internal::proxy::Proxy<DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies>::HandleType;

            // -- Creation of service proxy
            explicit DataIdentifier_IntrusionDetectionSystemTimingICAS1AnomaliesProxy(HandleType& handle)
            : Proxy<DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies>(handle)
            , Cancel(port_link())
            , Read(port_link())
            {}

            public:
            // -- Methods
            methods::Cancel Cancel;
            methods::Read Read;

          };
        }// namespace proxy
      }// namespace d_4942
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
