/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Service header files existence

// -- Inclusion protection
#ifndef VWG_SERVICES_IDSSECURITYEVENT_IDSSECURITYEVENT_SKELETON_H
#define VWG_SERVICES_IDSSECURITYEVENT_IDSSECURITYEVENT_SKELETON_H

// -- Inclusion of common header file
#include "idssecurityevent_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idssecurityevent
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using securityEvent = ::ara::com::internal::skeleton::Field<::vwg::services::idssecurityevent::IDSSecurityEvent::securityEvent>;
        }// namespace fields

        // -- Service skeleton class
        class IDSSecurityEventSkeleton : public ::ara::com::internal::skeleton::Skeleton<IDSSecurityEvent>
        {
          public:
          // -- Creation of service skeleton
          IDSSecurityEventSkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , securityEvent (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::securityEvent securityEvent;
        };
      }// namespace skeleton
    }// namespace idssecurityevent
  }// namespace services
}// namespace vwg
#endif
