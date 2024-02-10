/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_IMPL_TYPE_CONTROLINFO_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICHUGE_IMPL_TYPE_CONTROLINFO_H

#include "ara/stdtypes/impl_type_boolean.h"

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
          struct ControlInfo
          {
            ::ara::stdtypes::Boolean acknowledge{};
            ::ara::stdtypes::Boolean continueTransmission{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->acknowledge);
              f(this->continueTransmission);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->acknowledge);
              f(this->continueTransmission);
            }
          };
        } // namespace odcagentgenerichuge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
