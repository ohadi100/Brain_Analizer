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
#ifndef VWG_SERVICES_DIAG_D_117B_DATAIDENTIFIER_IDSVIWIHTTPDATABUSSERVICESERVICEINCCORECTMISSINGENCODING_SKELETON_H
#define VWG_SERVICES_DIAG_D_117B_DATAIDENTIFIER_IDSVIWIHTTPDATABUSSERVICESERVICEINCCORECTMISSINGENCODING_SKELETON_H

// -- Inclusion of common header file
#include "dataidentifier_idsviwihttpdatabusserviceserviceinccorectmissingencoding_common.h"

#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_117b
      {

        // -- Service skeleton namespace
        namespace skeleton
        {

          // -- Service methods namespace
          namespace methods
          {
            using Cancel = ::ara::com::internal::skeleton::Method<::vwg::services::diag::d_117b::DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding::Cancel>;
            using Read = ::ara::com::internal::skeleton::Method<::vwg::services::diag::d_117b::DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding::Read>;
          }// namespace methods

          // -- Service skeleton class
          class DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncodingSkeleton : public ::ara::com::internal::skeleton::Skeleton<DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding>
          {
            public:
            // -- Creation of service skeleton
            DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncodingSkeleton(
            ::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
            : Skeleton(instance, mode)
            , m_Cancel(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Cancel(metaInfo);})
            , m_Read(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Read(metaInfo);})
            {}

            // -- Provision of method
            using CancelOutput = ::vwg::services::diag::d_117b::DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding::Cancel::Output;
            virtual ::ara::com::Future<CancelOutput>
            Cancel(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

            using ReadOutput = ::vwg::services::diag::d_117b::DataIdentifier_IDSViwiHttpDataBusServiceServiceInccorectMissingEncoding::Read::Output;
            virtual ::ara::com::Future<ReadOutput>
            Read(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

            private:
            // -- Methods
            methods::Cancel m_Cancel;
            methods::Read m_Read;
          };
        }// namespace skeleton
      }// namespace d_117b
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif
