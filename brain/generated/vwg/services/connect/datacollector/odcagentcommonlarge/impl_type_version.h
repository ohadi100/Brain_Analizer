/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_VERSION_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_VERSION_H

#include "ara/stdtypes/impl_type_uint8.h"
#include "ara/stdtypes/impl_type_uint16.h"

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
          struct Version
          {
            ::ara::stdtypes::UInt8 major{};
            ::ara::stdtypes::UInt8 minor{};
            ::ara::stdtypes::UInt16 release{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->major);
              f(this->minor);
              f(this->release);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->major);
              f(this->minor);
              f(this->release);
            }
          };
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
