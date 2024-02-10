/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// AXIVION DISABLE Style AutosarC++18_10-A10.1.1: This violation is by design.
// The use of multiple inheritance here is to ease the implementation of fields by
// mixing-in base classes for the different aspects of reading, writing, and notifying.
// This follows a clear pattern and addresses the rationale of the rule, namely concerns
// about readability and maintainability.

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_PROXY_FIELDS_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IDSCANSENSOR_PROXY_FIELDS_H

#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_common.h"
#include "ac/com/cpp_binding/proxy/field.hpp"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idspremiumservices
      {

        namespace idscansensor
        {

          namespace proxy
          {
            namespace fields
            {
              class canSensorFeaturesElement0
              : public ::ac::com::cpp_binding::proxy::Field_get<IdsCanSensor::Fields::canSensorFeaturesElement0>
              , public ::ac::com::cpp_binding::proxy::Field_notify<IdsCanSensor::Fields::canSensorFeaturesElement0>
              {
                public:
                using FieldType = ::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::canSensorFeaturesElement0::FieldType;
                explicit canSensorFeaturesElement0(::ac::com::cpp_binding::proxy::Rport const& port_link);
              };

              class periodicSignalElement0
              : public ::ac::com::cpp_binding::proxy::Field_get<IdsCanSensor::Fields::periodicSignalElement0>
              , public ::ac::com::cpp_binding::proxy::Field_notify<IdsCanSensor::Fields::periodicSignalElement0>
              {
                public:
                using FieldType = ::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::periodicSignalElement0::FieldType;
                explicit periodicSignalElement0(::ac::com::cpp_binding::proxy::Rport const& port_link);
              };

            } // namespace fields
          } // namespace proxy
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
#endif

// AXIVION ENABLE Style AutosarC++18_10-A10.1.1
