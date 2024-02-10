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
#ifndef VWG_SERVICES_IDSCOREDUMPSENSOR_IDSCOREDUMPSENSOR_PROXY_H
#define VWG_SERVICES_IDSCOREDUMPSENSOR_IDSCOREDUMPSENSOR_PROXY_H

// -- Inclusion of common header file
#include "idscoredumpsensor_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idscoredumpsensor
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using coreDumpReports = ::ara::com::internal::proxy::Field<::vwg::services::idscoredumpsensor::IDSCoreDumpSensor::coreDumpReports>;
        }// namespace fields

        // -- Service proxy class
        class IDSCoreDumpSensorProxy : public ::ara::com::internal::proxy::Proxy<IDSCoreDumpSensor>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<IDSCoreDumpSensor>::HandleType;

          // -- Creation of service proxy
          explicit IDSCoreDumpSensorProxy(HandleType& handle)
          : Proxy<IDSCoreDumpSensor>(handle)
          , coreDumpReports(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::coreDumpReports coreDumpReports;

        };
      }// namespace proxy
    }// namespace idscoredumpsensor
  }// namespace services
}// namespace vwg
#endif
