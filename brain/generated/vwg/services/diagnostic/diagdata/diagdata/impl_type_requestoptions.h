/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_REQUESTOPTIONS_H
#define INC_VWG_SERVICES_DIAGNOSTIC_DIAGDATA_DIAGDATA_IMPL_TYPE_REQUESTOPTIONS_H

#include "ara/core/optional.h"
#include "vwg/services/diagnostic/diagdata/diagdata/impl_type_detaillevel.h"
#include "vwg/services/diagnostic/diagdata/diagdata/impl_type_hashalgorithm.h"
#include "vwg/services/diagnostic/diagdata/diagdata/impl_type_requestoptions_diagnodes.h"

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
          struct RequestOptions
          {
            DetailLevel detailLevel{};
            ::ara::core::Optional<HashAlgorithm> hashAlgorithm{};
            ::ara::core::Optional<RequestOptions_diagNodes> diagNodes{};
            using Generated_tag = void;
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f)
            {
              f(this->detailLevel);
              f(this->hashAlgorithm);
              f(this->diagNodes);
            }
            // AXIVION AutosarC++18_10-A8.4.9: Tool defect. Axivion can not know if f needs to be const or
            // not.
            template<typename F> void visit(F& f) const
            {
              f(this->detailLevel);
              f(this->hashAlgorithm);
              f(this->diagNodes);
            }
          };
        } // namespace diagdata
      } // namespace diagdata
    } // namespace diagnostic
  } // namespace services
} // namespace vwg

#endif
