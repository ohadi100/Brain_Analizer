/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSCOREDUMPSENSOR_DATATYPES_IMPL_TYPE_DT_COREDUMPREPORTS_STRUCT_H
#define VWG_SERVICES_IDSCOREDUMPSENSOR_DATATYPES_IMPL_TYPE_DT_COREDUMPREPORTS_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "ara/stdtypes/impl_type_string.h"

namespace vwg
{
  namespace services
  {
    namespace idscoredumpsensor
    {
      namespace datatypes
      {
        struct DT_coreDumpReports_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<::ara::stdtypes::String> procName;
          ::ara::com::Optional<::ara::stdtypes::String> crashReason;
          ::ara::com::Optional<::ara::stdtypes::String> crashTime;
          ::ara::com::Optional<::ara::stdtypes::String> stackTrace;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->procName, t.get());
            f(this->crashReason, t.get());
            f(this->crashTime, t.get());
            f(this->stackTrace, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 5U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 1),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 2),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 3),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 4),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace idscoredumpsensor
  }// namespace services
}// namespace vwg

#endif
