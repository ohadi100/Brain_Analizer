/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_EVENT_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_EVENT_H

#include "ara/core/optional.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_eventtype.h"
#include "ara/stdtypes/impl_type_string.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_timestamp.h"

namespace vwg
{
  namespace services
  {
    namespace connect
    {
      namespace datacollector
      {
        namespace odcagentcommonlarge
        {
          struct Event
          {
            EventType type{};
            ::ara::stdtypes::String name{};
            Timestamp timestamp{};
            ::ara::core::Optional<::ara::stdtypes::String> description{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->type);
              f(this->name);
              f(this->timestamp);
              f(this->description);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->type);
              f(this->name);
              f(this->timestamp);
              f(this->description);
            }
          };
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
