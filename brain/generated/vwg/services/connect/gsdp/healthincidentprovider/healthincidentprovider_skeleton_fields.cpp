/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_skeleton_fields.h"
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
        template class Field_value<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents>;
        template class Field_get<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents>;
        template class Field_notify<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents>;

      } // namespace skeleton
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace gsdp
      {

        namespace healthincidentprovider
        {

          namespace skeleton
          {

            namespace fields
            {
              openIncidents::openIncidents(Method_dispatcher& method_dispatcher,
              Field_validator& field_validator)
              : Field_value<HealthIncidentProvider::Fields::openIncidents>{}
              , Field_get<HealthIncidentProvider::Fields::openIncidents>{method_dispatcher, field_validator, Field_value::get_value()}
              , Field_notify<HealthIncidentProvider::Fields::openIncidents>{method_dispatcher, field_validator, Field_value::get_value()}
              {
              }

            } // namespace fields
          } // namespace skeleton
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
