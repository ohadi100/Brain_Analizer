/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/connect/gsdp/healthincidentprovider/healthincidentprovider_proxy_fields.h"
#include "ac/com/cpp_binding/proxy/rport.hpp"
#include "ac/com/cpp_binding/proxy/field_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace proxy
      {
        template class Method<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents::Get>;
        template class Event<::vwg::services::connect::gsdp::healthincidentprovider::HealthIncidentProvider::Fields::openIncidents::Notify>;

      } // namespace proxy
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

          namespace proxy
          {
            namespace fields
            {
              openIncidents::openIncidents(::ac::com::cpp_binding::proxy::Rport const& port_link)
              : ::ac::com::cpp_binding::proxy::Field_get<HealthIncidentProvider::Fields::openIncidents>{port_link}
              , ::ac::com::cpp_binding::proxy::Field_notify<HealthIncidentProvider::Fields::openIncidents>{port_link}
              {
              }

            } // namespace fields
          } // namespace proxy
        } // namespace healthincidentprovider
      } // namespace gsdp
    } // namespace connect
  } // namespace services
} // namespace vwg
