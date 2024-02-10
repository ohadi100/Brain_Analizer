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
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DIAGNOSTICDATADISTRIBUTION_PROXY_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DIAGNOSTICDATADISTRIBUTION_PROXY_H

// -- Inclusion of common header file
#include "diagnosticdatadistribution_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/method.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diagnosticdatadistribution
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using dataValuesHash = ::ara::com::internal::proxy::Field<::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::dataValuesHash>;
        }// namespace fields

        // -- Service methods namespace
        namespace methods
        {
          using getDiagnosticData = ::ara::com::internal::proxy::Method<::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::getDiagnosticData>;
          using getDiagnosticDataValues = ::ara::com::internal::proxy::Method<::vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution::getDiagnosticDataValues>;
        }// namespace methods

        // -- Service proxy class
        class DiagnosticDataDistributionProxy : public ::ara::com::internal::proxy::Proxy<DiagnosticDataDistribution>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<DiagnosticDataDistribution>::HandleType;

          // -- Creation of service proxy
          explicit DiagnosticDataDistributionProxy(HandleType& handle)
          : Proxy<DiagnosticDataDistribution>(handle)
          , dataValuesHash(handle.GetInstanceId(), port_link())
          , getDiagnosticData(port_link())
          , getDiagnosticDataValues(port_link())
          {}

          public:
          // -- Fields
          fields::dataValuesHash dataValuesHash;

          // -- Methods
          methods::getDiagnosticData getDiagnosticData;
          methods::getDiagnosticDataValues getDiagnosticDataValues;

        };
      }// namespace proxy
    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg
#endif
