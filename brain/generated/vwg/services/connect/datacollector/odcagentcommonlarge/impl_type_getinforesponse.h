/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_GETINFORESPONSE_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_GETINFORESPONSE_H

#include "ara/stdtypes/impl_type_uint16.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_version.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_resourcevector.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_abilities.h"

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
          struct GetInfoResponse
          {
            ::ara::stdtypes::UInt16 id{};
            Version version{};
            ResourceVector totalResources{};
            Abilities abilities{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->id);
              f(this->version);
              f(this->totalResources);
              f(this->abilities);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->id);
              f(this->version);
              f(this->totalResources);
              f(this->abilities);
            }
          };
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
