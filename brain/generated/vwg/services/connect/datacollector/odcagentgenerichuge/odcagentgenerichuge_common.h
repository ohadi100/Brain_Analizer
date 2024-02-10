/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_ODCAGENTGENERICHUGE_COMMON_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_ODCAGENTGENERICHUGE_COMMON_H

#include "ac/com/cpp_binding/types.hpp"
#include "ara/com/types.h"
#include "ara/core/error_code.h"
#include "ara/core/error_domain.h"
#include <array>
#include <cstddef>
#include "ac/com/someip/serialization/serialization_attributes.hpp"
#include "vwg/services/connect/datacollector/odcagentgenerichuge/odcagentgenerichuge_types.h"

namespace vwg
{

  namespace services
  {

    namespace connect
    {

      namespace datacollector
      {

        namespace odcagentgenerichuge
        {

          class OdcAgentGenericHuge
          {
            public:
            static constexpr ::ara::com::ServiceIdentifierType id()
            { return ::ara::com::ServiceIdentifierType("vwg::services::connect::datacollector::odcagentgenerichuge::OdcAgentGenericHuge"); }

            static constexpr ::ara::com::ServiceVersionType version()
            { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

            // -- Event identifier and configuration
            struct Events
            {
              struct data
              {
                static constexpr ::ac::com::cpp_binding::Event_id id{0u};
                static constexpr ::ac::com::cpp_binding::Event_name name{"data"};
                static constexpr std::size_t queueLength{::ac::com::cpp_binding::defaults::queue_length};
                static constexpr bool updateOnSubscribe{false};
                using SampleType = ::vwg::services::connect::datacollector::odcagentgenerichuge::Data;
                static ::ac::com::someip::serialization::Serialization_attributes const& eventSProps();
              };

            };
            // -- Method identifier and configuration
            struct Methods
            {
              struct control
              {
                static constexpr ::ac::com::cpp_binding::Method_id id{0u};
                static constexpr ::ac::com::cpp_binding::Method_name name{"control"};

                using Signature = void(::vwg::services::connect::datacollector::odcagentgenerichuge::ControlInfo const&);
                // Serialization properties for arguments
                static std::array<::ac::com::someip::serialization::Serialization_attributes,1> const& methodInSProps();
              };

            };
            // aggregated list of event and field notifier members
            static constexpr std::array<::ac::com::cpp_binding::Event_name,1u> get_events_of_service_interface()
            {
              return
              {
                Events::data::name
              };
            }

            // aggregated list of method and field getter/setter members
            static constexpr std::array<::ac::com::cpp_binding::Method_name,1u> get_methods_of_service_interface()
            {
              return
              {
                Methods::control::name
              };
            }
          };

        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg
#endif

