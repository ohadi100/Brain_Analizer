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
#ifndef AC_DM_SECURITYACCESS_SECURITYACCESS_SKELETON_H
#define AC_DM_SECURITYACCESS_SECURITYACCESS_SKELETON_H

// -- Inclusion of common header file
#include "securityaccess_common.h"

#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace securityaccess
    {

      // -- Service skeleton namespace
      namespace skeleton
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::skeleton::Method<::ac::dm::securityaccess::SecurityAccess::Cancel>;
          using CompareKey = ::ara::com::internal::skeleton::Method<::ac::dm::securityaccess::SecurityAccess::CompareKey>;
          using GetSeed = ::ara::com::internal::skeleton::Method<::ac::dm::securityaccess::SecurityAccess::GetSeed>;
        }// namespace methods

        // -- Service skeleton class
        class SecurityAccessSkeleton : public ::ara::com::internal::skeleton::Skeleton<SecurityAccess>
        {
          public:
          // -- Creation of service skeleton
          SecurityAccessSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , m_Cancel(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Cancel(metaInfo);})
          , m_CompareKey(method_dispatcher(),[this](::ac::dm::types::ByteVectorType key, ::ac::dm::types::MetaInfoType metaInfo) { return CompareKey(key, metaInfo);})
          , m_GetSeed(method_dispatcher(),[this](::ac::dm::types::ByteVectorType securityAccessDataRecord, ::ac::dm::types::MetaInfoType metaInfo) { return GetSeed(securityAccessDataRecord, metaInfo);})
          {}

          // -- Provision of method
          using CancelOutput = ::ac::dm::securityaccess::SecurityAccess::Cancel::Output;
          virtual ::ara::com::Future<CancelOutput>
          Cancel(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          using CompareKeyOutput = ::ac::dm::securityaccess::SecurityAccess::CompareKey::Output;
          virtual ::ara::com::Future<CompareKeyOutput>
          CompareKey(::ac::dm::types::ByteVectorType const& key, ::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          using GetSeedOutput = ::ac::dm::securityaccess::SecurityAccess::GetSeed::Output;
          virtual ::ara::com::Future<GetSeedOutput>
          GetSeed(::ac::dm::types::ByteVectorType const& securityAccessDataRecord, ::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          private:
          // -- Methods
          methods::Cancel m_Cancel;
          methods::CompareKey m_CompareKey;
          methods::GetSeed m_GetSeed;
        };
      }// namespace skeleton
    }// namespace securityaccess
  }// namespace dm
}// namespace ac
#endif
