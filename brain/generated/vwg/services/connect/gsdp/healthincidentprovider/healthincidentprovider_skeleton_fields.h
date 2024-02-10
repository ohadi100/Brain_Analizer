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

// AXIVION DISABLE Style AutosarC++18_10-M10.2.1: Not a problem.
// The reported violation refers to the assignment operators in the base classes.
// There is no ambiguity here; the assignment operator of the derived class will call
// the base class assignment operators in a defined order according to [class.copy].

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_SKELETON_FIELDS_H
#define INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_SKELETON_FIELDS_H

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_common.h"

#include "ac/com/cpp_binding/skeleton/field.hpp"

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
              using Method_dispatcher = ::ac::com::cpp_binding::skeleton::Method_dispatcher;
              using Field_validator = ::ac::com::cpp_binding::skeleton::Field_validator;
              template<typename FieldTraits>
              using Field_get = ::ac::com::cpp_binding::skeleton::Field_get<FieldTraits>;
              template<typename FieldTraits>
              using Field_notify = ::ac::com::cpp_binding::skeleton::Field_notify<FieldTraits>;
              template<typename FieldTraits>
              using Field_value =::ac::com::cpp_binding::skeleton::Field_value<FieldTraits>;

              class openIncidents
              : public Field_value<HealthIncidentProvider::Fields::openIncidents>
              , public Field_get<HealthIncidentProvider::Fields::openIncidents>
              , private Field_notify<HealthIncidentProvider::Fields::openIncidents>
              {
                public:
                using FieldType = ::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents::FieldType;
                openIncidents(Method_dispatcher& method_dispatcher, Field_validator& field_validator);
              };

            } // namespace fields
          } // namespace skeleton
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif

// AXIVION ENABLE Style AutosarC++18_10-A10.1.1
// AXIVION ENABLE Style AutosarC++18_10-M10.2.1
