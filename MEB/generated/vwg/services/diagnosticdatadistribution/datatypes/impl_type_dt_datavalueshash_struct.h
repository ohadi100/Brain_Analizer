/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DT_DATAVALUESHASH_STRUCT_H
#define VWG_SERVICES_DIAGNOSTICDATADISTRIBUTION_DATATYPES_IMPL_TYPE_DT_DATAVALUESHASH_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/stdtypes/impl_type_uint32.h"
#include "ara/stdtypes/impl_type_uint64.h"

namespace vwg
{
  namespace services
  {
    namespace diagnosticdatadistribution
    {
      namespace datatypes
      {
        struct DT_dataValuesHash_struct
        {
          ::ara::com::Optional<::ara::stdtypes::UInt32> name_space;
          ::ara::com::Optional<::ara::stdtypes::UInt32> category;
          ::ara::com::Optional<::ara::stdtypes::UInt64> hashValue;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->name_space, t.get());
            f(this->category, t.get());
            f(this->hashValue, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 3U> v
            {
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 2),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 3),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace diagnosticdatadistribution
  }// namespace services
}// namespace vwg

#endif
