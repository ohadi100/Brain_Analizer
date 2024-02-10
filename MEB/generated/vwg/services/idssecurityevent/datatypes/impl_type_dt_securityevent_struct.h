/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSSECURITYEVENT_DATATYPES_IMPL_TYPE_DT_SECURITYEVENT_STRUCT_H
#define VWG_SERVICES_IDSSECURITYEVENT_DATATYPES_IMPL_TYPE_DT_SECURITYEVENT_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "vwg/services/idssecurityevent/datatypes/impl_type_dt_securityeventeventframe.h"
#include "vwg/services/idssecurityevent/datatypes/impl_type_dt_securityeventtimestamp.h"
#include "vwg/services/idssecurityevent/datatypes/impl_type_dt_securityeventcontextdata.h"

namespace vwg
{
  namespace services
  {
    namespace idssecurityevent
    {
      namespace datatypes
      {
        struct DT_securityEvent_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<DT_securityEventeventFrame> eventFrame;
          ::ara::com::Optional<DT_securityEventtimestamp> timestamp;
          ::ara::com::Optional<DT_securityEventcontextData> contextData;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->eventFrame, t.get());
            f(this->timestamp, t.get());
            f(this->contextData, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 4U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 1),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 2),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 3),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace idssecurityevent
  }// namespace services
}// namespace vwg

#endif
