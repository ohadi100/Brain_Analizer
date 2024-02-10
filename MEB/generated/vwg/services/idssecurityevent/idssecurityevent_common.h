/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSSECURITYEVENT_IDSSECURITYEVENT_COMMON_H
#define VWG_SERVICES_IDSSECURITYEVENT_IDSSECURITYEVENT_COMMON_H

#include "ara/com/types.h"
#include "idssecurityevent_types.h"
// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idssecurityevent
    {

      // -- Service Identifier and Service Version Classes
      class IDSSecurityEvent
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("vwg::services::idssecurityevent::IDSSecurityEvent"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Field identifier and configuration
        struct securityEvent
        {
          using FieldType = ::vwg::services::idssecurityevent::datatypes::DT_securityEvent_vector;
          struct Notify
          {
            static constexpr ::ac::com::cpp_binding::Event_id Id{ 0u };
            static constexpr std::size_t Queue_length{ ::ac::com::cpp_binding::defaults::queue_length };
            static constexpr bool Update_on_subscribe{true};
            using SampleType = FieldType;
          };
          struct Get
          {
            static constexpr ::ac::com::cpp_binding::Method_id Id{ 0u };

            using Output = FieldType;
            using Signature = Output();

            static std::exception_ptr GetApplicationErrorExceptionPtr(
            ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
          };
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 1u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 1u; }
      };

    }// namespace idssecurityevent
  }// namespace services
}// namespace vwg
#endif

