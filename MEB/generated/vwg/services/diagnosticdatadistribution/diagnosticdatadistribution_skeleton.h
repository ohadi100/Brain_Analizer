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
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DIAGNOSTICDATADISTRIBUTION_SKELETON_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DIAGNOSTICDATADISTRIBUTION_SKELETON_H

// -- Inclusion of common header file
#include "diagnosticdatadistribution_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/method.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diagnosticdatadistribution
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using dataValuesHash = ::ara::com::internal::skeleton::Field<::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::dataValuesHash>;
        }// namespace fields

        // -- Service methods namespace
        namespace methods
        {
          using getDiagnosticData = ::ara::com::internal::skeleton::Method<::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::getDiagnosticData>;
          using getDiagnosticDataValues = ::ara::com::internal::skeleton::Method<::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::getDiagnosticDataValues>;
        }// namespace methods

        // -- Service skeleton class
        class DiagnosticDataDistributionSkeleton : public ::ara::com::internal::skeleton::Skeleton<DiagnosticDataDistribution>
        {
          public:
          // -- Creation of service skeleton
          DiagnosticDataDistributionSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , dataValuesHash (field_handler(), method_dispatcher())
          , m_getDiagnosticData(method_dispatcher(),[this](::ara::stdtypes::UInt32 name_space, ::ara::stdtypes::UInt32 category) { return getDiagnosticData(name_space, category);})
          , m_getDiagnosticDataValues(method_dispatcher(),[this](::ara::stdtypes::UInt32 name_space, ::vwg::services::diagnosticdatadistribution::datatypes::DT_ListOfIds iDs) { return getDiagnosticDataValues(name_space, iDs);})
          {}

          // -- Provision of method
          using getDiagnosticDataOutput = ::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::getDiagnosticData::Output;
          virtual ::ara::com::Future<getDiagnosticDataOutput>
          getDiagnosticData(::ara::stdtypes::UInt32 name_space, ::ara::stdtypes::UInt32 category) = 0;

          using getDiagnosticDataValuesOutput = ::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::getDiagnosticDataValues::Output;
          virtual ::ara::com::Future<getDiagnosticDataValuesOutput>
          getDiagnosticDataValues(::ara::stdtypes::UInt32 name_space, ::vwg::services::diagnosticdatadistribution::datatypes::DT_ListOfIds const& iDs) = 0;

          public:
          // -- Fields
          fields::dataValuesHash dataValuesHash;
          private:
          // -- Methods
          methods::getDiagnosticData m_getDiagnosticData;
          methods::getDiagnosticDataValues m_getDiagnosticDataValues;
        };
      }// namespace skeleton
    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg
#endif
