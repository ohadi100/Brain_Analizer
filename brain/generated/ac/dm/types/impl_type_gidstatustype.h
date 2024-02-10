/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_AC_DM_TYPES_IMPL_TYPE_GIDSTATUSTYPE_H
#define INC_AC_DM_TYPES_IMPL_TYPE_GIDSTATUSTYPE_H

#include "ac/dm/types/impl_type_gidtype.h"
#include <cstdint>

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct GIDstatusType
      {
        GIDType GID{};
        std::uint8_t furtherActionReq{};
        std::uint8_t syncStatus{};
        using Generated_tag = void;
        // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
        // not.
        template<typename F> void visit(F& f)
        {
          f(this->GID);
          f(this->furtherActionReq);
          f(this->syncStatus);
        }
        // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
        // not.
        template<typename F> void visit(F& f) const
        {
          f(this->GID);
          f(this->furtherActionReq);
          f(this->syncStatus);
        }
      };
    } // namespace types
  } // namespace dm
} // namespace ac

#endif
