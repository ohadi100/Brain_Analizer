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
#ifndef AC_DM_DATA_ELEMENT_UINT16_DATAELEMENT_UINT16_SKELETON_H
#define AC_DM_DATA_ELEMENT_UINT16_DATAELEMENT_UINT16_SKELETON_H

// -- Inclusion of common header file
#include "dataelement_uint16_common.h"

#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace data_element_uint16
    {

      // -- Service skeleton namespace
      namespace skeleton
      {

        // -- Service methods namespace
        namespace methods
        {
          using Cancel = ::ara::com::internal::skeleton::Method<::ac::dm::data_element_uint16::DataElement_uint16::Cancel>;
          using Read = ::ara::com::internal::skeleton::Method<::ac::dm::data_element_uint16::DataElement_uint16::Read>;
        }// namespace methods

        // -- Service skeleton class
        class DataElement_uint16Skeleton : public ::ara::com::internal::skeleton::Skeleton<DataElement_uint16>
        {
          public:
          // -- Creation of service skeleton
          DataElement_uint16Skeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , m_Cancel(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Cancel(metaInfo);})
          , m_Read(method_dispatcher(),[this](::ac::dm::types::MetaInfoType metaInfo) { return Read(metaInfo);})
          {}

          // -- Provision of method
          using CancelOutput = ::ac::dm::data_element_uint16::DataElement_uint16::Cancel::Output;
          virtual ::ara::com::Future<CancelOutput>
          Cancel(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          using ReadOutput = ::ac::dm::data_element_uint16::DataElement_uint16::Read::Output;
          virtual ::ara::com::Future<ReadOutput>
          Read(::ac::dm::types::MetaInfoType const& metaInfo) = 0;

          private:
          // -- Methods
          methods::Cancel m_Cancel;
          methods::Read m_Read;
        };
      }// namespace skeleton
    }// namespace data_element_uint16
  }// namespace dm
}// namespace ac
#endif
