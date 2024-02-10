/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_TYPES_IMPL_TYPE_SNAPSHOTDATARECORDTYPE_H
#define AC_DM_TYPES_IMPL_TYPE_SNAPSHOTDATARECORDTYPE_H

#include "ara/stdtypes/impl_type_uint8.h"
#include "ac/dm/types/impl_type_bytevectortype.h"

namespace ac
{
  namespace dm
  {
    namespace types
    {
      struct SnapshotDataRecordType
      {
        ::ara::stdtypes::UInt8 snapshotRecordNumber;
        ByteVectorType snapshotDataElements;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->snapshotRecordNumber);
          f(this->snapshotDataElements);
        }
      };
    }// namespace types
  }// namespace dm
}// namespace ac

#endif
