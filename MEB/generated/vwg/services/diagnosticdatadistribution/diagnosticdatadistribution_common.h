/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DIAGNOSTICDATADISTRIBUTION_COMMON_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DIAGNOSTICDATADISTRIBUTION_COMMON_H

#include "ara/com/types.h"
#include "diagnosticdatadistribution_types.h"
// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diagnosticdatadistribution
    {

      // -- Service Identifier and Service Version Classes
      class DiagnosticDataDistribution
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("vwg::services::diagnosticdatadistribution::DiagnosticDataDistribution"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Method identifier and configuration
        struct getDiagnosticData
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 0u };

          struct Output;
          using Signature = Output(::ara::stdtypes::UInt32,
          ::ara::stdtypes::UInt32);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        struct getDiagnosticDataValues
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

          struct Output;
          using Signature = Output(::ara::stdtypes::UInt32,
          ::vwg::services::diagnosticdatadistribution::datatypes::DT_ListOfIds const&);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        // -- Field identifier and configuration
        struct dataValuesHash
        {
          using FieldType = ::vwg::services::diagnosticdatadistribution::datatypes::DT_dataValuesHash_vector;
          struct Notify
          {
            static constexpr ::ac::com::cpp_binding::Event_id Id{ 0u };
            static constexpr std::size_t Queue_length{ ::ac::com::cpp_binding::defaults::queue_length };
            static constexpr bool Update_on_subscribe{true};
            using SampleType = FieldType;
          };
          struct Get
          {
            static constexpr ::ac::com::cpp_binding::Method_id Id{ 2u };

            using Output = FieldType;
            using Signature = Output();

            static std::exception_ptr GetApplicationErrorExceptionPtr(
            ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
          };
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 1u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 3u; }
      };

      struct DiagnosticDataDistribution::getDiagnosticData::Output
      {
        ::vwg::services::diagnosticdatadistribution::datatypes::DT_DiagnosticValuesResultType dataValuesResult;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->dataValuesResult);
        }
      };

      struct DiagnosticDataDistribution::getDiagnosticDataValues::Output
      {
        ::vwg::services::diagnosticdatadistribution::datatypes::DT_DiagnosticValuesResultType dataValuesResult;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->dataValuesResult);
        }
      };

    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg
#endif

