/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IDSSECURITYEVENTSMALL_COMMON_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IDSSECURITYEVENTSMALL_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_types.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idssecurityevent
      {

        namespace idssecurityeventsmall
        {

          class IDSSecurityEventSmall
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Event identifier and configuration
            struct Events
            {
              struct securityEvent
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"securityEvent"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::vwg::services::security::idssecurityevent::idssecurityeventsmall::SecurityEventStruct;
                static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,1u> get_events_of_service_interface()
            {
              return
              {
                Events::securityEvent::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,0u> get_methods_of_service_interface()
            {
              return
              {
              };
            }
          };

        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif

