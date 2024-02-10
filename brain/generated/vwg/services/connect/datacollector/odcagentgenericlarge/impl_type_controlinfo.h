/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_IMPL_TYPE_CONTROLINFO_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTGENERICLARGE_IMPL_TYPE_CONTROLINFO_H

#include "ara/core/optional.h"
#include "ara/stdtypes/impl_type_boolean.h"
#include "ara/stdtypes/impl_type_uint8.h"

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
          struct ControlInfo
          {
            ::ara::stdtypes::Boolean continueTransmission{};
            ::ara::core::Optional<::ara::stdtypes::UInt8> acknowledge{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->continueTransmission);
              f(this->acknowledge);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->continueTransmission);
              f(this->acknowledge);
            }
          };
        } // namespace odcagentgenericlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
