/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// This file is generated. Do not edit!

#include "vwg/services/security/idssecurityevent/idssecurityeventsmall/idssecurityeventsmall_skeleton.h"
#include <utility>
#include "ara/com/com_error_domain.h"
#include "ac/com/cpp_binding/skeleton/event_defs.hpp"
#include "ac/com/cpp_binding/skeleton/skeleton_defs.hpp"

namespace ac
{
  namespace com
  {
    namespace cpp_binding
    {
      namespace skeleton
      {
        template class Event<::vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall::Events::securityEvent>;
        template class Skeleton<::vwg::services::security::idssecurityevent::idssecurityeventsmall::IDSSecurityEventSmall>;
      } // namespace skeleton
    } // namespace cpp_binding
  } // namespace com
} // namespace ac

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
            IDSSecurityEventSmallSkeleton::IDSSecurityEventSmallSkeleton(::ara::com::InstanceIdentifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{std::move(instance), mode}
            , securityEvent{port_link()}
            {
            }

            IDSSecurityEventSmallSkeleton::IDSSecurityEventSmallSkeleton(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instance, mode}
            , securityEvent{port_link()}
            {
            }

            IDSSecurityEventSmallSkeleton::IDSSecurityEventSmallSkeleton(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : Skeleton{instances, mode}
            , securityEvent{port_link()}
            {
            }

            IDSSecurityEventSmallSkeleton::IDSSecurityEventSmallSkeleton(ConstructionToken&& token) noexcept
            : Skeleton{std::move(token.skeleton_impl)}
            , securityEvent{std::move(token.securityEvent)}
            {
            }

            ::ara::core::Result<IDSSecurityEventSmallSkeleton::ConstructionToken>
            IDSSecurityEventSmallSkeleton::Preconstruct(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instance, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            ::ara::core::Result<IDSSecurityEventSmallSkeleton::ConstructionToken>
            IDSSecurityEventSmallSkeleton::Preconstruct(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instance, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            ::ara::core::Result<IDSSecurityEventSmallSkeleton::ConstructionToken>
            IDSSecurityEventSmallSkeleton::Preconstruct(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode) noexcept
            {
              try
              {
                return ConstructionToken{instances, mode};
              }
              catch (...)
              {
                return ::ara::core::Result<ConstructionToken>::FromError(
                ::ara::com::ComErrc::kNetworkBindingFailure);
              }
            }

            IDSSecurityEventSmallSkeleton::ConstructionToken::~ConstructionToken() = default;
            IDSSecurityEventSmallSkeleton::ConstructionToken::ConstructionToken(ConstructionToken&& /*unused*/) noexcept = default;
            IDSSecurityEventSmallSkeleton::ConstructionToken& IDSSecurityEventSmallSkeleton::ConstructionToken::operator=(ConstructionToken&& /*unused*/) & noexcept = default;

            IDSSecurityEventSmallSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifierContainer const& instances,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instances, mode)}
            , securityEvent{skeleton_impl->port_link()}
            {
            }

            IDSSecurityEventSmallSkeleton::ConstructionToken::ConstructionToken(::ara::com::InstanceIdentifier const& instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , securityEvent{skeleton_impl->port_link()}
            {
            }

            IDSSecurityEventSmallSkeleton::ConstructionToken::ConstructionToken(::ara::core::InstanceSpecifier instance,
            ::ara::com::MethodCallProcessingMode mode)
            : skeleton_impl{std::make_unique<Skeleton::Impl>(instance, mode)}
            , securityEvent{skeleton_impl->port_link()}
            {
            }

          } // namespace skeleton
        } // namespace idssecurityeventsmall
      } // namespace idssecurityevent
    } // namespace security
  } // namespace services
} // namespace vwg
