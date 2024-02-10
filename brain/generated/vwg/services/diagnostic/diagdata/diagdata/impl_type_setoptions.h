/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_SETOPTIONS_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_SETOPTIONS_H

#include "ara/core/optional.h"
#include "vwg/services/diagnostic/diagdata/diagdata/impl_type_resultformat.h"

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
          struct SetOptions
          {
            ::ara::core::Optional<ResultFormat> resultFormat{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->resultFormat);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->resultFormat);
            }
          };
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg

#endif
