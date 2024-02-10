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
#ifndef AC_DM_DATA_ELEMENT_VECTOR_UINT8_DATAELEMENT_VECTOR_UINT8_SKELETON_H
#define AC_DM_DATA_ELEMENT_VECTOR_UINT8_DATAELEMENT_VECTOR_UINT8_SKELETON_H

// -- Inclusion of common header file
#include "dataelement_vector_uint8_common.h"

#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace data_element_vector_uint8
    {

      // -- Service skeleton namespace
      namespace skeleton
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::skeleton::Method<::ac::dm::data_element_vector_uint8::DataElement_vector_uint8::Cancel>;
          using Read = ::ara::com::internal::skeleton::Method<::ac::dm::data_element_vector_uint8::DataElement_vector_uint8::Read>;
        }// namespace methods

        // -- Service skeleton class
        class DataElement_vector_uint8Skeleton : public ::ara::com::internal::skeleton::Skeleton<DataElement_vector_uint8>
        {
          public:
          // -- Creation of service skeleton
          DataElement_vector_uint8Skeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , m_Cancel(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Cancel(metaInfo);})
          , m_Read(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Read(metaInfo);})
          {}

          // -- Provision of method
          using CancelOutput = ::ac::dm::data_element_vector_uint8::DataElement_vector_uint8::Cancel::Output;
          virtual ::ara::com::Future<CancelOutput>
          Cancel(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          using ReadOutput = ::ac::dm::data_element_vector_uint8::DataElement_vector_uint8::Read::Output;
          virtual ::ara::com::Future<ReadOutput>
          Read(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          private:
          // -- Methods
          methods::Cancel m_Cancel;
          methods::Read m_Read;
        };
      }// namespace skeleton
    }// namespace data_element_vector_uint8
  }// namespace dm
}// namespace ac
#endif
