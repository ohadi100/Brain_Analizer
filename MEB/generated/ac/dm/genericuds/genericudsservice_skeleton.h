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
#ifndef AC_DM_GENERICUDS_GENERICUDSSERVICE_SKELETON_H
#define AC_DM_GENERICUDS_GENERICUDSSERVICE_SKELETON_H

// -- Inclusion of common header file
#include "genericudsservice_common.h"

#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace genericuds
    {

      // -- Service skeleton namespace
      namespace skeleton
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::skeleton::Method<::ac::dm::genericuds::GenericUDSService::Cancel>;
          using HandleMessage = ::ara::com::internal::skeleton::Method<::ac::dm::genericuds::GenericUDSService::HandleMessage>;
        }// namespace methods

        // -- Service skeleton class
        class GenericUDSServiceSkeleton : public ::ara::com::internal::skeleton::Skeleton<GenericUDSService>
        {
          public:
          // -- Creation of service skeleton
          GenericUDSServiceSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , m_Cancel(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Cancel(metaInfo);})
          , m_HandleMessage(method_dispatcher(),[this](::ac::dm::types::SIDType SID, ::ac::dm::types::ByteVectorType requestData, ::ac::dm::types::MetaInfoType metaInfo) { return HandleMessage(SID, requestData, metaInfo);})
          {}

          // -- Provision of method
          using CancelOutput = ::ac::dm::genericuds::GenericUDSService::Cancel::Output;
          virtual ::ara::com::Future<CancelOutput>
          Cancel(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          using HandleMessageOutput = ::ac::dm::genericuds::GenericUDSService::HandleMessage::Output;
          virtual ::ara::com::Future<HandleMessageOutput>
          HandleMessage(::ac::dm::types::SIDType SID, ::ac::dm::types::ByteVectorType const& requestData, ::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          private:
          // -- Methods
          methods::Cancel m_Cancel;
          methods::HandleMessage m_HandleMessage;
        };
      }// namespace skeleton
    }// namespace genericuds
  }// namespace dm
}// namespace ac
#endif
