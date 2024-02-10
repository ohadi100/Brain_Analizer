/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_PERIODICSIGNALTYPE_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_PERIODICSIGNALTYPE_H

#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_cyclecounter.h"
#include "ara/stdtypes/impl_type_uint8.h"

namespace vwg
{
  namespace services
  {
    namespace security
    {
      namespace idspremiumservices
      {
        namespace idscansensor
        {
          struct PeriodicSignalType
          {
            CycleCounter keepAlive{};
            ::ara::stdtypes::UInt8 elementId{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->keepAlive);
              f(this->elementId);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->keepAlive);
              f(this->elementId);
            }
          };
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
