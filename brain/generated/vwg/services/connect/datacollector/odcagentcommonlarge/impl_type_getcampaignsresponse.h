/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_GETCAMPAIGNSRESPONSE_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_GETCAMPAIGNSRESPONSE_H

#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_getcampaignsresponse_uuids.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_resourcevector.h"

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
          struct GetCampaignsResponse
          {
            GetCampaignsResponse_uuids uuids{};
            ResourceVector consumedResources{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->uuids);
              f(this->consumedResources);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->uuids);
              f(this->consumedResources);
            }
          };
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
