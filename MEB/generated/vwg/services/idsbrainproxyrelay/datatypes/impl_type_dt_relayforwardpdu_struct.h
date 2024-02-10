/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSBRAINPROXYRELAY_DATATYPES_IMPL_TYPE_DT_RELAYFORWARDPDU_STRUCT_H
#define VWG_SERVICES_IDSBRAINPROXYRELAY_DATATYPES_IMPL_TYPE_DT_RELAYFORWARDPDU_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "ara/stdtypes/impl_type_uint32.h"
#include "vwg/services/idsbrainproxyrelay/datatypes/impl_type_dt_relayforwardpduframepayload.h"

namespace vwg
{
  namespace services
  {
    namespace idsbrainproxyrelay
    {
      namespace datatypes
      {
        struct DT_relayForwardPDU_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<::ara::stdtypes::UInt32> protocolCntrl;
          ::ara::com::Optional<::ara::stdtypes::UInt32> seqNum;
          ::ara::com::Optional<DT_relayForwardPDUframePayload> framePayload;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->protocolCntrl, t.get());
            f(this->seqNum, t.get());
            f(this->framePayload, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 4U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 2),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 3),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace idsbrainproxyrelay
  }// namespace services
}// namespace vwg

#endif
