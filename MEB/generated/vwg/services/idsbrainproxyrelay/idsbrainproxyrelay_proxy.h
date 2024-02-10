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
#ifndef VWG_SERVICES_IDSBRAINPROXYRELAY_IDSBRAINPROXYRELAY_PROXY_H
#define VWG_SERVICES_IDSBRAINPROXYRELAY_IDSBRAINPROXYRELAY_PROXY_H

// -- Inclusion of common header file
#include "idsbrainproxyrelay_common.h"

#include "ara/com/internal/proxy/field.hpp"
#include "ara/com/internal/proxy/proxy.hpp"

// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace idsbrainproxyrelay
    {

      // -- Service proxy namespace
      namespace proxy
      {

        // -- Service fields namespace
        namespace fields
        {
          using relayFeedbackPDU = ::ara::com::internal::proxy::Field<::vwg::services::idsbrainproxyrelay::IDSBrainProxyRelay::relayFeedbackPDU>;
          using relayForwardPDU = ::ara::com::internal::proxy::Field<::vwg::services::idsbrainproxyrelay::IDSBrainProxyRelay::relayForwardPDU>;
        }// namespace fields

        // -- Service proxy class
        class IDSBrainProxyRelayProxy : public ::ara::com::internal::proxy::Proxy<IDSBrainProxyRelay>
        {
          public:
          // -- HandleType class
          using HandleType = ::ara::com::internal::proxy::Proxy<IDSBrainProxyRelay>::HandleType;

          // -- Creation of service proxy
          explicit IDSBrainProxyRelayProxy(HandleType& handle)
          : Proxy<IDSBrainProxyRelay>(handle)
          , relayFeedbackPDU(handle.GetInstanceId(), port_link())
          , relayForwardPDU(handle.GetInstanceId(), port_link())
          {}

          public:
          // -- Fields
          fields::relayFeedbackPDU relayFeedbackPDU;
          fields::relayForwardPDU relayForwardPDU;

        };
      }// namespace proxy
    }// namespace idsbrainproxyrelay
  }// namespace services
}// namespace vwg
#endif
