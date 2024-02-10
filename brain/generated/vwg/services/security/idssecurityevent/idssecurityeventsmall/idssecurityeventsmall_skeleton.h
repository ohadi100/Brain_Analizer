/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

// -- Inclusion protection
#ifndef INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IDSSECURITYEVENTSMALL_SKELETON_H
#define INC_VWG_SERVICES_SECURITY_IDSSECURITYEVENT_IDSSECURITYEVENTSMALL_IDSSECURITYEVENTSMALL_SKELETON_H

#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_common.h"

#include <memory>
#include "ac/com/cpp_binding/skeleton/event.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton.hpp"
#include "ara/com/types.h"
#include "ara/core/instance_specifier.h"
#include "ara/core/result.h"

namespace vwg
{

  namespace services
  {

    namespace security
    {

      namespace idssecurityevent
      {

        namespace idssecurityeventsmall
        {

          namespace skeleton
          {
            namespace events
            {
              using securityEvent = ::ac::com::cpp_binding::skeleton::Event<::vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall::Events::securityEvent>;
            } // namespace events

            class IDSSecurityEventSmallSkeleton
            : public ::ac::com::cpp_binding::skeleton::Skeleton<IDSSecurityEventSmall>
            {
              public:
              struct ConstructionToken
              {
                std::unique_ptr<Skeleton::Impl> skeleton_impl;
                events::securityEvent securityEvent;

                ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances, ::ara::com::MethodCallProcessingMode mode);
                ConstructionToken(::ara::com::InstanceIdentifier const& instance, ::ara::com::MethodCallProcessingMode mode);
                ConstructionToken(::ara::core::InstanceSpecifier instance, ::ara::com::MethodCallProcessingMode mode);
                ~ConstructionToken();
                ConstructionToken(ConstructionToken&& /*unused*/) noexcept;
                ConstructionToken& operator=(ConstructionToken&& /*unused*/) & noexcept;

                ConstructionToken(ConstructionToken const&) = delete;
                ConstructionToken& operator=(ConstructionToken const&) = delete;
              };

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::com::InstanceIdentifierContainer const& /*instances*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::com::InstanceIdentifier const& /*instance*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              static ::ara::core::Result<ConstructionToken>
              Preconstruct(::ara::core::InstanceSpecifier /*instance*/,
              ::ara::com::MethodCallProcessingMode /*mode*/ =
              ::ara::com::MethodCallProcessingMode::kEvent) noexcept;

              explicit IDSSecurityEventSmallSkeleton(
              ::ara::com::InstanceIdentifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IDSSecurityEventSmallSkeleton(
              ::ara::core::InstanceSpecifier instance,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IDSSecurityEventSmallSkeleton(
              ::ara::com::InstanceIdentifierContainer const& instances,
              ::ara::com::MethodCallProcessingMode mode = ::ara::com::MethodCallProcessingMode::kEvent);

              explicit IDSSecurityEventSmallSkeleton(ConstructionToken&& token) noexcept;

              events::securityEvent securityEvent;

            };
          } // namespace skeleton
        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
#endif
