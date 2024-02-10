/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_IDSETHERNETSENSOR_DATATYPES_IMPL_TYPE_DT_PORTSTATISTICS_STRUCT_H
#define VWG_SERVICES_IDSETHERNETSENSOR_DATATYPES_IMPL_TYPE_DT_PORTSTATISTICS_STRUCT_H

#include "ara/com/optional.hpp"
#include "ac/com/someip/serialization/structure_tag.hpp"
#include "vwg/stdtypes/impl_type_dt_uuid.h"
#include "ara/stdtypes/impl_type_uint16.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint32.h"

namespace vwg
{
  namespace services
  {
    namespace idsethernetsensor
    {
      namespace datatypes
      {
        struct DT_portStatistics_struct
        {
          ::ara::com::Optional<::vwg::stdtypes::DT_uuid> id;
          ::ara::com::Optional<::ara::stdtypes::UInt16> sourceSoftwareId;
          ::ara::com::Optional<::ara::stdtypes::UInt16> sourcePortId;
          ::ara::com::Optional<::ara::stdtypes::UInt64> captureTime;
          ::ara::com::Optional<::ara::stdtypes::UInt64> receivedDataVolume;
          ::ara::com::Optional<::ara::stdtypes::UInt64> transmittedDataVolume;
          ::ara::com::Optional<::ara::stdtypes::UInt32> receivedL2UnicastFrames;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedL2UnicastFrames;
          ::ara::com::Optional<::ara::stdtypes::UInt32> receivedL2MulticastFrames;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedL2MulticastFrames;
          ::ara::com::Optional<::ara::stdtypes::UInt32> receivedBroadcast;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedBroadcast;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue1;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue2;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue3;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue4;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue5;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue6;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue7;
          ::ara::com::Optional<::ara::stdtypes::UInt32> transmittedFramesViaQueue8;
          ::ara::com::Optional<::ara::stdtypes::UInt32> droppedFrames;
          ::ara::com::Optional<::ara::stdtypes::UInt32> filteredFrames;
          ::ara::com::Optional<::ara::stdtypes::UInt32> currentlyEnqueuedEgressFrames;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            ::ac::com::someip::serialization::Tagger t(get_tlv_tags());
            f(this->id, t.get());
            f(this->sourceSoftwareId, t.get());
            f(this->sourcePortId, t.get());
            f(this->captureTime, t.get());
            f(this->receivedDataVolume, t.get());
            f(this->transmittedDataVolume, t.get());
            f(this->receivedL2UnicastFrames, t.get());
            f(this->transmittedL2UnicastFrames, t.get());
            f(this->receivedL2MulticastFrames, t.get());
            f(this->transmittedL2MulticastFrames, t.get());
            f(this->receivedBroadcast, t.get());
            f(this->transmittedBroadcast, t.get());
            f(this->transmittedFramesViaQueue1, t.get());
            f(this->transmittedFramesViaQueue2, t.get());
            f(this->transmittedFramesViaQueue3, t.get());
            f(this->transmittedFramesViaQueue4, t.get());
            f(this->transmittedFramesViaQueue5, t.get());
            f(this->transmittedFramesViaQueue6, t.get());
            f(this->transmittedFramesViaQueue7, t.get());
            f(this->transmittedFramesViaQueue8, t.get());
            f(this->droppedFrames, t.get());
            f(this->filteredFrames, t.get());
            f(this->currentlyEnqueuedEgressFrames, t.get());
          }
          static ::ac::com::someip::serialization::Tag_list get_tlv_tags() noexcept 
          {
            using namespace ::ac::com::someip::serialization;
            static const std::array<Structure_tag, 23U> v
            {
              Structure_tag(Structure_tag::Wire_type::complex_data_type_length_field_32bit, 0),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 1),
              Structure_tag(Structure_tag::Wire_type::base_data_type_16bit, 2),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 3),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 4),
              Structure_tag(Structure_tag::Wire_type::base_data_type_64bit, 5),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 6),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 7),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 8),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 9),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 10),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 11),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 12),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 13),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 14),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 15),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 16),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 17),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 18),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 19),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 20),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 21),
              Structure_tag(Structure_tag::Wire_type::base_data_type_32bit, 22),
            };
            return Tag_list{v.data(), std::next(v.data(), static_cast<std::ptrdiff_t>(v.size()))};
          }
        };
      }// namespace datatypes
    }// namespace idsethernetsensor
  }// namespace services
}// namespace vwg

#endif
