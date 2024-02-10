/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_DATA_ELEMENT_UINT8_DATAELEMENT_UINT8_COMMON_H
#define AC_DM_DATA_ELEMENT_UINT8_DATAELEMENT_UINT8_COMMON_H

#include "ara/com/types.h"
#include "dataelement_uint8_types.h"
// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace data_element_uint8
    {

      // -- Service Identifier and Service Version Classes
      class DataElement_uint8
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("ac::dm::data_element_uint8::DataElement_uint8"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Method identifier and configuration
        struct Cancel
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 0u };

          using Output = void;
          using Signature = Output(::ac::dm::types::MetaInfoType const&);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        struct Read
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

          struct Output;
          using Signature = Output(::ac::dm::types::MetaInfoType const&);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 0u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 2u; }
      };

      struct DataElement_uint8::Read::Output
      {
        ::autosar_platform::implementationdatatypes::uint8 dataRecord;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->dataRecord);
        }
      };

    }// namespace data_element_uint8
  }// namespace dm
}// namespace ac
#endif

