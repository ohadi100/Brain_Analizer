/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSIPSECURITYSENSOR_DATATYPES_IMPL_TYPE_DT_FIREWALLFILTERREPORTS_STRUCT_H
#define VWG_SERVICES_IDSIPSECURITYSENSOR_DATATYPES_IMPL_TYPE_DT_FIREWALLFILTERREPORTS_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_string.h"
#include "vwg/services/idsipsecuritysensor/datatypes/impl_type_dt_firewallfilterreportsframepayload.h"

namespace vwg
{
  namespace services
  {
    namespace idsipsecuritysensor
    {
      namespace datatypes
      {
        struct DT_firewallFilterReports_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<::ara::stdtypes::UInt16> firewallId;
          ::ara::com::Optional<::ara::stdtypes::UInt64> filterTime;
          ::ara::com::Optional<::ara::stdtypes::String> filterLog;
          ::ara::com::Optional<::ara::stdtypes::UInt16> classRuleId;
          ::ara::com::Optional<::ara::stdtypes::String> classRule;
          ::ara::com::Optional<DT_firewallFilterReportsframePayload> framePayload;
          ::ara::com::Optional<::ara::stdtypes::UInt16> bytesTruncated;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->firewallId, t.get());
            f(this->filterTime, t.get());
            f(this->filterLog, t.get());
            f(this->classRuleId, t.get());
            f(this->classRule, t.get());
            f(this->framePayload, t.get());
            f(this->bytesTruncated, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 8U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 2),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 3),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 4),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 5),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 6),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 7),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace idsipsecuritysensor
  }// namespace services
}// namespace vwg

#endif
