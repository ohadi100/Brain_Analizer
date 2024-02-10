/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSETHERNETSENSOR_DATATYPES_IMPL_TYPE_DT_TRAFFICFLOWSAMPLES_STRUCT_H
#define VWG_SERVICES_IDSETHERNETSENSOR_DATATYPES_IMPL_TYPE_DT_TRAFFICFLOWSAMPLES_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_string.h"
#include "vwg/services/idsethernetsensor/datatypes/impl_type_dt_idsethernetsensor_trafficflowsamples_transportprotocol.h"
#include "ara/stdtypes/impl_type_uint32.h"

namespace vwg
{
  namespace services
  {
    namespace idsethernetsensor
    {
      namespace datatypes
      {
        struct DT_trafficFlowSamples_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<::ara::stdtypes::UInt16> sourceSwId;
          ::ara::com::Optional<::ara::stdtypes::UInt64> flowStartTime;
          ::ara::com::Optional<::ara::stdtypes::String> sourceIpAddr;
          ::ara::com::Optional<::ara::stdtypes::String> destinationIpAddr;
          ::ara::com::Optional<::ara::stdtypes::String> sourceMacAddr;
          ::ara::com::Optional<::ara::stdtypes::String> destinationMacAddr;
          ::ara::com::Optional<DT_IDSEthernetSensor_trafficFlowSamples_transportProtocol> transportProtocol;
          ::ara::com::Optional<::ara::stdtypes::UInt16> sourcePort;
          ::ara::com::Optional<::ara::stdtypes::UInt16> destinationPort;
          ::ara::com::Optional<::ara::stdtypes::UInt32> totalPacketsPassed;
          ::ara::com::Optional<::ara::stdtypes::UInt64> totalBytesPassed;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->sourceSwId, t.get());
            f(this->flowStartTime, t.get());
            f(this->sourceIpAddr, t.get());
            f(this->destinationIpAddr, t.get());
            f(this->sourceMacAddr, t.get());
            f(this->destinationMacAddr, t.get());
            f(this->transportProtocol, t.get());
            f(this->sourcePort, t.get());
            f(this->destinationPort, t.get());
            f(this->totalPacketsPassed, t.get());
            f(this->totalBytesPassed, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 12U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 2),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 3),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 4),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 5),
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 6),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 7),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 8),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 9),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 10),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 11),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace idsethernetsensor
  }// namespace services
}// namespace vwg

#endif
