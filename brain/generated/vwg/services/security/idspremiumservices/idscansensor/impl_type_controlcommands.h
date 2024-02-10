/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_CONTROLCOMMANDS_H
#define INC_VWG_SERVICES_SECURITY_IDSPREMIUMSERVICES_IDSCANSENSOR_IMPL_TYPE_CONTROLCOMMANDS_H

#include "vwg/services/security/idspremiumservices/idscansensor/impl_type_controlcommands_sourceidentifier.h"
#include "ara/stdtypes/impl_type_uint64.h"
#include "ara/stdtypes/impl_type_uint16.h"

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
          struct ControlCommands
          {
            ControlCommands_sourceIdentifier sourceIdentifier{};
            ::ara::stdtypes::UInt64 timestamp{};
            ::ara::stdtypes::UInt16 commandIdentifier{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->sourceIdentifier);
              f(this->timestamp);
              f(this->commandIdentifier);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->sourceIdentifier);
              f(this->timestamp);
              f(this->commandIdentifier);
            }
          };
        } // namespace idscansensor
      } // namespace idspremiumservices
    } // namespace security
  } // namespace services
} // namespace vwg

#endif
