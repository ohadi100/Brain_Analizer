/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_ADDCAMPAIGNREQUEST_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_ADDCAMPAIGNREQUEST_H

#include "ara/stdtypes/impl_type_string.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_signature.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_campaign.h"

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
          struct AddCampaignRequest
          {
            ::ara::stdtypes::String uuid{};
            Signature signature{};
            Campaign campaign{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->uuid);
              f(this->signature);
              f(this->campaign);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->uuid);
              f(this->signature);
              f(this->campaign);
            }
          };
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
