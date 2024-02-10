/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_IMPL_TYPE_DATA_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_IMPL_TYPE_DATA_H

#include "ara/core/optional.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint32.h"
#include "vwg/services/connect/datacollector/odcagentgenerichuge/impl_type_data_value.h"
#include "vwg/services/connect/datacollector/odcagentgenerichuge/impl_type_chunkinfo.h"

namespace vwg
{
  namespace services
  {
    namespace connect
    {
      namespace datacollector
      {
        namespace odcagentgenerichuge
        {
          struct Data
          {
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt32 keyID{};
            Data_value value{};
            ::ara::core::Optional<ChunkInfo> chunkInfo{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->timestamp);
              f(this->keyID);
              f(this->value);
              f(this->chunkInfo);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->timestamp);
              f(this->keyID);
              f(this->value);
              f(this->chunkInfo);
            }
          };
        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
