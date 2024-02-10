/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idspremiumservices/idscansensor/idscansensor_skeleton_fields.h"
#include "ac/com/cpp_binding/skeleton/field_defs.hpp"
#include "ac/com/cpp_binding/skeleton/field_validator.hpp"
#include "ac/com/cpp_binding/skeleton/method_dispatcher.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace skeleton
      {
        template class Field_value<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::canSensorFeaturesElement0>;
        template class Field_get<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::canSensorFeaturesElement0>;
        template class Field_notify<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::canSensorFeaturesElement0>;
        template class Field_value<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::periodicSignalElement0>;
        template class Field_get<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::periodicSignalElement0>;
        template class Field_notify<::vwg::services::security::idspremiumservices::idscansensor::IdsCanSensor::Fields::periodicSignalElement0>;

      } // namespace skeleton
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

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

          namespace skeleton
          {

            namespace fields
            {
              canSensorFeaturesElement0::canSensorFeaturesElement0(Method_dispatcher& method_dispatcher,
              Field_validator& field_validator)
              : Field_value<IdsCanSensor::Fields::canSensorFeaturesElement0>{}
              , Field_get<IdsCanSensor::Fields::canSensorFeaturesElement0>{method_dispatcher, field_validator, Field_value::get_value()}
              , Field_notify<IdsCanSensor::Fields::canSensorFeaturesElement0>{method_dispatcher, field_validator, Field_value::get_value()}
              {
              }

              periodicSignalElement0::periodicSignalElement0(Method_dispatcher& method_dispatcher,
              Field_validator& field_validator)
              : Field_value<IdsCanSensor::Fields::periodicSignalElement0>{}
              , Field_get<IdsCanSensor::Fields::periodicSignalElement0>{method_dispatcher, field_validator, Field_value::get_value()}
              , Field_notify<IdsCanSensor::Fields::periodicSignalElement0>{method_dispatcher, field_validator, Field_value::get_value()}
              {
              }

            } // namespace fields
          } // namespace skeleton
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
