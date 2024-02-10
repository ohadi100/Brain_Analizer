/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_DEM_DIAGNOSTICEVENT_COMMON_H
#define AC_DM_DEM_DIAGNOSTICEVENT_COMMON_H

#include "ara/com/types.h"
#include "diagnosticevent_types.h"
// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace dem
    {

      // -- Service Identifier and Service Version Classes
      class DiagnosticEvent
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("ac::dm::dem::DiagnosticEvent"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Method identifier and configuration
        struct FaultDetectionCounter
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 0u };

          struct Output;
          using Signature = Output();

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        struct GetDTCOfEvent
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

          struct Output;
          using Signature = Output(::ac::dm::types::DTCFormatType);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        struct GetDebouncingOfEvent
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 2u };

          struct Output;
          using Signature = Output();

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        // -- Field identifier and configuration
        struct EventStatus
        {
          using FieldType = ::ac::dm::types::EventStatusByteType;
          struct Notify
          {
            static constexpr ::ac::com::cpp_binding::Event_id Id{ 0u };
            static constexpr std::size_t Queue_length{ ::ac::com::cpp_binding::defaults::queue_length };
            static constexpr bool Update_on_subscribe{true};
            using SampleType = FieldType;
          };
          struct Get
          {
            static constexpr ::ac::com::cpp_binding::Method_id Id{ 3u };

            using Output = FieldType;
            using Signature = Output();

            static std::exception_ptr GetApplicationErrorExceptionPtr(
            ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
          };
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 1u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 4u; }
      };

      struct DiagnosticEvent::FaultDetectionCounter::Output
      {
        ::ac::dm::types::FaultDetectionCounterType faultDetectionCounter;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->faultDetectionCounter);
        }
      };

      struct DiagnosticEvent::GetDTCOfEvent::Output
      {
        ::ac::dm::types::DTCType DTCOfEvent;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->DTCOfEvent);
        }
      };

      struct DiagnosticEvent::GetDebouncingOfEvent::Output
      {
        ::ac::dm::types::DebouncingStateType debouncingState;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->debouncingState);
        }
      };

    }// namespace dem
  }// namespace dm
}// namespace ac
#endif

