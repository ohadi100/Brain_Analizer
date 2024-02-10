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
#ifndef INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_PROXY_FIELDS_H
#define INC_VWG_SERVICES_CONNECT_GSDP_HEALTHINCIDENTPROVIDER_HEALTHINCIDENTPROVIDER_PROXY_FIELDS_H

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_common.h"
#include "ac/com/cpp_binding/proxy/field.hpp"

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

          namespace proxy
          {
            namespace fields
            {
              class openIncidents
              : public ::ac::com::cpp_binding::proxy::Field_get<HealthIncidentProvider::Fields::openIncidents>
              , public ::ac::com::cpp_binding::proxy::Field_notify<HealthIncidentProvider::Fields::openIncidents>
              {
                public:
                using FieldType = ::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents::FieldType;
                explicit openIncidents(::ac::com::cpp_binding::proxy::Rport const& port_link);
              };

            } // namespace fields
          } // namespace proxy
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif

// AXIVION ENABLE Style AutosarC++18_10-A10.1.1
