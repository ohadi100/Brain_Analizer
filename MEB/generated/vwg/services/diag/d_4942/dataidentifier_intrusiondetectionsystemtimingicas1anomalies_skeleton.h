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
#ifndef VWG_SERVICES_DIAG_D_4942_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMTIMINGICAS1ANOMALIES_SKELETON_H
#define VWG_SERVICES_DIAG_D_4942_DATAIDENTIFIER_INTRUSIONDETECTIONSYSTEMTIMINGICAS1ANOMALIES_SKELETON_H

// -- Inclusion of common header file
#include "dataidentifier_intrusiondetectionsystemtimingicas1anomalies_common.h"

#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_4942
      {

        // -- Service skeleton namespace
        namespace skeleton
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::skeleton::Method<::vwg::services::diag::d_4942::DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies::Cancel>;
            using Read = ::ara::com::internal::skeleton::Method<::vwg::services::diag::d_4942::DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies::Read>;
          }// namespace methods

          // -- Service skeleton class
          class DataIdentifier_IntrusionDetectionSystemTimingICAS1AnomaliesSkeleton : public ::ara::com::internal::skeleton::Skeleton<DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies>
          {
            public:
            // -- Creation of service skeleton
            DataIdentifier_IntrusionDetectionSystemTimingICAS1AnomaliesSkeleton(
            ::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
            : Skeleton(instance, mode)
            , m_Cancel(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Cancel(metaInfo);})
            , m_Read(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Read(metaInfo);})
            {}

            // -- Provision of method
            using CancelOutput = ::vwg::services::diag::d_4942::DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies::Cancel::Output;
            virtual ::ara::com::Future<CancelOutput>
            Cancel(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

            using ReadOutput = ::vwg::services::diag::d_4942::DataIdentifier_IntrusionDetectionSystemTimingICAS1Anomalies::Read::Output;
            virtual ::ara::com::Future<ReadOutput>
            Read(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

            private:
            // -- Methods
            methods::Cancel m_Cancel;
            methods::Read m_Read;
          };
        }// namespace skeleton
      }// namespace d_4942
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
