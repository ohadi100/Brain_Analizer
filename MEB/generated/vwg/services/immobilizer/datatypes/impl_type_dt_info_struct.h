/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IMMOBILIZER_DATATYPES_IMPL_TYPE_DT_INFO_STRUCT_H
#define VWG_SERVICES_IMMOBILIZER_DATATYPES_IMPL_TYPE_DT_INFO_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "ara/stdtypes/impl_type_uint32.h"
#include "ara/stdtypes/impl_type_boolean.h"
#include "ara/stdtypes/impl_type_string.h"

namespace vwg
{
  namespace services
  {
    namespace immobilizer
    {
      namespace datatypes
      {
        struct DT_info_struct
        {
          ::ara::com::Optional<::ara::stdtypes::UInt32> elementId;
          ::ara::com::Optional<::ara::stdtypes::UInt32> learningKeyValue;
          ::ara::com::Optional<::ara::stdtypes::UInt32> learnedKeyValue;
          ::ara::com::Optional<::ara::stdtypes::Boolean> isLocked;
          ::ara::com::Optional<::ara::stdtypes::UInt32> stateOfLife;
          ::ara::com::Optional<::ara::stdtypes::String> vehicleIdentificationNumber;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->elementId, t.get());
            f(this->learningKeyValue, t.get());
            f(this->learnedKeyValue, t.get());
            f(this->isLocked, t.get());
            f(this->stateOfLife, t.get());
            f(this->vehicleIdentificationNumber, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 6U> v
            {
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 2),
              Structure_tag(Structure_tag::Wire_type::base_data_type_8bit, 3),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 4),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 5),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace immobilizer
  }// namespace services
}// namespace vwg

#endif
