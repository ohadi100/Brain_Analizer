/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_DEM_DIAGNOSTICMONITOR_COMMON_H
#define AC_DM_DEM_DIAGNOSTICMONITOR_COMMON_H

#include "ara/com/types.h"
#include "diagnosticmonitor_types.h"
// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace dem
    {

      // -- Service Identifier and Service Version Classes
      class DiagnosticMonitor
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("ac::dm::dem::DiagnosticMonitor"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Event identifier and configuration
        struct MonitorAction
        {
          static constexpr ::ac::com::cpp_binding::Event_id Id{ 0u };
          static constexpr std::size_t Queue_length{ ::ac::com::cpp_binding::defaults::queue_length };
          static constexpr bool Update_on_subscribe{false};
          using SampleType = ::ac::dm::types::MonitorActionType;
        };

        // -- Method identifier and configuration
        struct InitMonitor
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 0u };

          using Output = void;
          using Signature = Output(::ac::dm::types::InitMonitorReasonType);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 1u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 1u; }
      };

    }// namespace dem
  }// namespace dm
}// namespace ac
#endif

