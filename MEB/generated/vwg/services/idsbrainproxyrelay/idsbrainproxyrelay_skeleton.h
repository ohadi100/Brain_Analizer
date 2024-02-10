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
#ifndef VWG_SERVICES_IDSBRAINPROXYRELAY_IDSBRAINPROXYRELAY_SKELETON_H
#define VWG_SERVICES_IDSBRAINPROXYRELAY_IDSBRAINPROXYRELAY_SKELETON_H

// -- Inclusion of common header file
#include "idsbrainproxyrelay_common.h"

#include "ara/com/internal/skeleton/field.hpp"
#include "ara/com/internal/skeleton/skeleton.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idsbrainproxyrelay
    {

      // -- Service skeleton namespace
      namespace skeleton
      {
        // -- Service fields namespace
        namespace fields
        {
          using relayFeedbackPDU = ::ara::com::internal::skeleton::Field<::vwg::services::idsbrainproxyrelay::IDSBrainProxyRelay::relayFeedbackPDU>;
          using relayForwardPDU = ::ara::com::internal::skeleton::Field<::vwg::services::idsbrainproxyrelay::IDSBrainProxyRelay::relayForwardPDU>;
        }// namespace fields

        // -- Service skeleton class
        class IDSBrainProxyRelaySkeleton : public ::ara::com::internal::skeleton::Skeleton<IDSBrainProxyRelay>
        {
          public:
          // -- Creation of service skeleton
          IDSBrainProxyRelaySkeleton(
          ::ara::com::InstanceIdentifier instance,
          ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent)
          : Skeleton(instance, mode)
          , relayFeedbackPDU (field_handler(), method_dispatcher())
          , relayForwardPDU (field_handler(), method_dispatcher())
          {}

          public:
          // -- Fields
          fields::relayFeedbackPDU relayFeedbackPDU;
          fields::relayForwardPDU relayForwardPDU;
        };
      }// namespace skeleton
    }// namespace idsbrainproxyrelay
  }// namespace services
}// namespace vwg
#endif
