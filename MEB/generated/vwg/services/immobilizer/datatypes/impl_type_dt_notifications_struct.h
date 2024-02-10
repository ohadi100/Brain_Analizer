/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IMMOBILIZER_DATATYPES_IMPL_TYPE_DT_NOTIFICATIONS_STRUCT_H
#define VWG_SERVICES_IMMOBILIZER_DATATYPES_IMPL_TYPE_DT_NOTIFICATIONS_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/services/immobilizer/datatypes/impl_type_dt_immobilizer_notifications_type.h"
#include "ara/stdtypes/impl_type_uint32.h"

namespace vwg
{
  namespace services
  {
    namespace immobilizer
    {
      namespace datatypes
      {
        struct DT_notifications_struct
        {
          ::ara::com::Optional<DT_Immobilizer_notifications_type> type;
          ::ara::com::Optional<::ara::stdtypes::UInt32> value;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->type, t.get());
            f(this->value, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 2U> v
            {
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 1),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace immobilizer
  }// namespace services
}// namespace vwg

#endif
