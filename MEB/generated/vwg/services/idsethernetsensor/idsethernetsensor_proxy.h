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
#ifndef VWG_SERVICES_IDSETHERNETSENSOR_IDSETHERNETSENSOR_PROXY_H
#define VWG_SERVICES_IDSETHERNETSENSOR_IDSETHERNETSENSOR_PROXY_H

// -- Inclusion of common header file
#include "idsethernetsensor_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idsethernetsensor
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using classifierMatchReports = ::ara::com::internal::proxy::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::classifierMatchReports>;
          using portStatistics = ::ara::com::internal::proxy::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::portStatistics>;
          using serviceDiscoveryReports = ::ara::com::internal::proxy::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::serviceDiscoveryReports>;
          using specialFrameReports = ::ara::com::internal::proxy::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::specialFrameReports>;
          using trafficFlowSamples = ::ara::com::internal::proxy::Field<::vwg::services::idsethernetsensor::IDSEthernetSensor::trafficFlowSamples>;
        }// namespace fields

        // -- Service proxy class
        class IDSEthernetSensorProxy : public ::ara::com::internal::proxy::Proxy<IDSEthernetSensor>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<IDSEthernetSensor>::HandleType;

          // -- Creation of service proxy
          explicit IDSEthernetSensorProxy(HandleType& handle)
          : Proxy<IDSEthernetSensor>(handle)
          , classifierMatchReports(handle.GetInstanceId(), port_link())
          , portStatistics(handle.GetInstanceId(), port_link())
          , serviceDiscoveryReports(handle.GetInstanceId(), port_link())
          , specialFrameReports(handle.GetInstanceId(), port_link())
          , trafficFlowSamples(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::classifierMatchReports classifierMatchReports;
          fields::portStatistics portStatistics;
          fields::serviceDiscoveryReports serviceDiscoveryReports;
          fields::specialFrameReports specialFrameReports;
          fields::trafficFlowSamples trafficFlowSamples;

        };
      }// namespace proxy
    }// namespace idsethernetsensor
  }// namespace services
}// namespace vwg
#endif
