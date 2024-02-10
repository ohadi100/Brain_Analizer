/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idspremiumservices/idshostsensor/idshostsensor_proxy_fields.h"
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
        template class Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Fields::hostSensorFeaturesElement0::Get>;
        template class Event<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Fields::hostSensorFeaturesElement0::Notify>;
        template class Method<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Fields::periodicSignalElement0::Get>;
        template class Event<::vwg::services::security::idspremiumservices::idshostsensor::IdsHostSensor::Fields::periodicSignalElement0::Notify>;

      } // namespace proxy
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

        namespace idshostsensor
        {

          namespace proxy
          {
            namespace fields
            {
              hostSensorFeaturesElement0::hostSensorFeaturesElement0(::ac::com::cpp_binding::proxy::Rport const& port_link)
              : ::ac::com::cpp_binding::proxy::Field_get<IdsHostSensor::Fields::hostSensorFeaturesElement0>{port_link}
              , ::ac::com::cpp_binding::proxy::Field_notify<IdsHostSensor::Fields::hostSensorFeaturesElement0>{port_link}
              {
              }

              periodicSignalElement0::periodicSignalElement0(::ac::com::cpp_binding::proxy::Rport const& port_link)
              : ::ac::com::cpp_binding::proxy::Field_get<IdsHostSensor::Fields::periodicSignalElement0>{port_link}
              , ::ac::com::cpp_binding::proxy::Field_notify<IdsHostSensor::Fields::periodicSignalElement0>{port_link}
              {
              }

            } // namespace fields
          } // namespace proxy
        } // namespace idshostsensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg
