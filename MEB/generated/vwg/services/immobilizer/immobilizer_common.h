/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IMMOBILIZER_IMMOBILIZER_COMMON_H
#define VWG_SERVICES_IMMOBILIZER_IMMOBILIZER_COMMON_H

#include "ara/com/types.h"
#include "immobilizer_types.h"
// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace immobilizer
    {

      // -- Service Identifier and Service Version Classes
      class Immobilizer
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("vwg::services::immobilizer::Immobilizer"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Field identifier and configuration
        struct info
        {
          using FieldType = ::vwg::services::immobilizer::datatypes::DT_info_vector;
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

        struct notifications
        {
          using FieldType = ::vwg::services::immobilizer::datatypes::DT_notifications_vector;
          struct Notify
          {
            static constexpr ::ac::com::cpp_binding::Event_id Id{ 1u };
            static constexpr std::size_t Queue_length{ ::ac::com::cpp_binding::defaults::queue_length };
            static constexpr bool Update_on_subscribe{true};
            using SampleType = FieldType;
          };
          struct Get
          {
            static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

            using Output = FieldType;
            using Signature = Output();

            static std::exception_ptr GetApplicationErrorExceptionPtr(
            ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
          };
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 2u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 2u; }
      };

    }// namespace immobilizer
  }// namespace services
}// namespace vwg
#endif

