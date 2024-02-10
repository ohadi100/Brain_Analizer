/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_IMPL_TYPE_ODCAGENTGENERICLARGE_DATA_EVENTDATA_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_IMPL_TYPE_ODCAGENTGENERICLARGE_DATA_EVENTDATA_H

#include "ara/stdtypes/impl_type_uint8.h"
#include "vwg/services/connect/datacollector/odcagentgenericlarge/impl_type_data.h"

namespace vwg
{
  namespace services
  {
    namespace connect
    {
      namespace datacollector
      {
        namespace odcagentgenericlarge
        {
          struct OdcAgentGenericLarge_data_eventData
          {
            ::ara::stdtypes::UInt8 sequenceCounter{};
            Data data{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sequenceCounter);
              f(this->data);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sequenceCounter);
              f(this->data);
            }
          };
        } // namespace odcagentgenericlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
