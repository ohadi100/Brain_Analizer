/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_GETDATARESPONSE_H
#define INC_VWG_SERVICES_CONNECT_DATACOLLECTOR_ODCAGENTCOMMONLARGE_IMPL_TYPE_GETDATARESPONSE_H

#include "ara/core/optional.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_status.h"
#include "vwg/services/connect/datacollector/odcagentcommonlarge/impl_type_data.h"

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
          struct GetDataResponse
          {
            Status status{};
            ::ara::core::Optional<Data> response{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->status);
              f(this->response);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->status);
              f(this->response);
            }
          };
        } // namespace odcagentcommonlarge
      } // namespace datacollector
    } // namespace connect
  } // namespace services
} // namespace vwg

#endif
