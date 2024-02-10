/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_DIAGDATA_SENDDIAGCONTROLCOMMANDRESPONSE_EVENTDATA_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_DIAGDATA_SENDDIAGCONTROLCOMMANDRESPONSE_EVENTDATA_H

#include "ara/stdtypes/impl_type_string.h"

namespace vwg
{
  namespace services
  {
    namespace diagnostic
    {
      namespace diagdata
      {
        namespace diagdata
        {
          struct DiagData_sendDiagControlCommandResponse_eventData
          {
            ::ara::stdtypes::String accessID{};
            ::ara::stdtypes::String controlCommand{};
            ::ara::stdtypes::String controlMessage{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->accessID);
              f(this->controlCommand);
              f(this->controlMessage);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->accessID);
              f(this->controlCommand);
              f(this->controlMessage);
            }
          };
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg

#endif
