/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_TIME_DATATYPES_IMPL_TYPE_DT_TIMES_STRUCT_H
#define VWG_SERVICES_TIME_DATATYPES_IMPL_TYPE_DT_TIMES_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/services/time/datatypes/impl_type_dt_time_times_type.h"
#include "ara/stdtypes/impl_type_string.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint32.h"

namespace vwg
{
  namespace services
  {
    namespace time
    {
      namespace datatypes
      {
        struct DT_times_struct
        {
          ::ara::com::Optional<DT_Time_times_type> type;
          ::ara::com::Optional<::ara::stdtypes::String> date;
          ::ara::com::Optional<::ara::stdtypes::UInt64> pltOffset;
          ::ara::com::Optional<::ara::stdtypes::String> time;
          ::ara::com::Optional<::ara::stdtypes::UInt64> unix;
          ::ara::com::Optional<::ara::stdtypes::UInt32> standby;
          ::ara::com::Optional<::ara::stdtypes::UInt32> vehicleOffTime;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->type, t.get());
            f(this->date, t.get());
            f(this->pltOffset, t.get());
            f(this->time, t.get());
            f(this->unix, t.get());
            f(this->standby, t.get());
            f(this->vehicleOffTime, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 7U> v
            {
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 2),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 3),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 4),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 5),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 6),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace time
  }// namespace services
}// namespace vwg

#endif
