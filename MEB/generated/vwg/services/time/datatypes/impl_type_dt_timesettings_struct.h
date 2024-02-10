/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_TIME_DATATYPES_IMPL_TYPE_DT_TIMESETTINGS_STRUCT_H
#define VWG_SERVICES_TIME_DATATYPES_IMPL_TYPE_DT_TIMESETTINGS_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "ara/stdtypes/impl_type_boolean.h"
#include "vwg/services/time/datatypes/impl_type_dt_time_timesettings_timemode.h"
#include "ara/stdtypes/impl_type_int32.h"

namespace vwg
{
  namespace services
  {
    namespace time
    {
      namespace datatypes
      {
        struct DT_timeSettings_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<::ara::stdtypes::Boolean> dstActive;
          ::ara::com::Optional<DT_Time_timeSettings_timeMode> timeMode;
          ::ara::com::Optional<::ara::stdtypes::Int32> timeZoneOffset;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->dstActive, t.get());
            f(this->timeMode, t.get());
            f(this->timeZoneOffset, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 4U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_8bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 2),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 3),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace time
  }// namespace services
}// namespace vwg

#endif
