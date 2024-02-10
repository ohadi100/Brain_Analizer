/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_DEM_OPERATIONCYCLE_COMMON_H
#define AC_DM_DEM_OPERATIONCYCLE_COMMON_H

#include "ara/com/types.h"
#include "operationcycle_types.h"
// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace dem
    {

      // -- Service Identifier and Service Version Classes
      class OperationCycle
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("ac::dm::dem::OperationCycle"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Field identifier and configuration
        struct State
        {
          using FieldType = ::ac::dm::types::OperationCycleStateType;
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
          struct Set
          {
            static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

            using Output = FieldType;
            using Signature = Output(FieldType const&);

            static std::exception_ptr GetApplicationErrorExceptionPtr(
            ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
          };
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 1u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 2u; }
      };

    }// namespace dem
  }// namespace dm
}// namespace ac
#endif

