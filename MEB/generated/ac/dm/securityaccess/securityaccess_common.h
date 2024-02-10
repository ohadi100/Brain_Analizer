/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef AC_DM_SECURITYACCESS_SECURITYACCESS_COMMON_H
#define AC_DM_SECURITYACCESS_SECURITYACCESS_COMMON_H

#include "ara/com/types.h"
#include "securityaccess_types.h"
// -- Service namespace
namespace ac
{

  namespace dm
  {

    namespace securityaccess
    {

      // -- Service Identifier and Service Version Classes
      class SecurityAccess
      {
        public:
        static constexpr ::ara::com::ServiceIdentifierType id()
        { return ::ara::com::ServiceIdentifierType("ac::dm::securityaccess::SecurityAccess"); }

        static constexpr ::ara::com::ServiceVersionType version()
        { return ::ara::com::ServiceVersionType(::ac::com::cpp_binding::defaults::service_version); }

        // -- Method identifier and configuration
        struct Cancel
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 0u };

          using Output = void;
          using Signature = Output(::ac::dm::types::MetaInfoType const&);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        struct CompareKey
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

          struct Output;
          using Signature = Output(::ac::dm::types::ByteVectorType const&,
          ::ac::dm::types::MetaInfoType const&);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        struct GetSeed
        {
          static constexpr ::ac::com::cpp_binding::Method_id Id{ 2u };

          struct Output;
          using Signature = Output(::ac::dm::types::ByteVectorType const&,
          ::ac::dm::types::MetaInfoType const&);

          static std::exception_ptr GetApplicationErrorExceptionPtr(
          ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
        };

        class UDSServiceFailed : public ::ara::com::ApplicationErrorException
        {
          public:
          static constexpr ::ac::com::cpp_binding::Error_id Id{ 2u };
          struct Output
          {
            ::ac::dm::types::UDSResponseCodeType CompareKey_nrc;
            ::ac::dm::types::UDSResponseCodeType GetSeed_nrc;
            using Generated_tag = void;
            template<typename F> void visit(F& f)
            {
              f(this->CompareKey_nrc);
              f(this->GetSeed_nrc);
            }
          };

          /// ctor as per SWS
          UDSServiceFailed(::ac::dm::types::UDSResponseCodeType CompareKey_nrc,
          ::ac::dm::types::UDSResponseCodeType GetSeed_nrc);

          /// ctor, internal
          UDSServiceFailed(::ac::com::someip::serialization::buffer_t const& data);

          const char* what() const noexcept final override
          {
            return "SecurityAccess::UDSServiceFailed::2";
          }

          const ::ac::dm::types::UDSResponseCodeType& get_CompareKey_nrc() const
          {
            return m_Output.CompareKey_nrc;
          }

          const ::ac::dm::types::UDSResponseCodeType& get_GetSeed_nrc() const
          {
            return m_Output.GetSeed_nrc;
          }

          ::ac::com::cpp_binding::Error_id error() const noexcept override { return Id; }

          void serialize(::ac::com::someip::serialization::Serializer& serializer) const override
          {
            auto f = [&serializer](auto& member) { serializer.serialize(member); };
            // AXIVION AutosarC++14-A5.2.3 : We have one visit function that's used for both
            // serialization and deserialization. In the case of deserialization, the deserialized
            // outcome must be written back into m_output (which can possibly be a const value from a
            // user application perspective), therefore it's required to always cast away the constness
            // before calling the visit function.
            auto& non_const_val = const_cast<Output&>(m_Output);
            non_const_val.visit(f);
          }

          private:
          Output m_Output;
        };

        // aggregated number of events and fields
        static constexpr std::uint8_t number_of_events(){ return 0u; }
        // aggregated number of methods and field accessors
        static constexpr std::uint8_t number_of_methods(){ return 3u; }
      };

      struct SecurityAccess::CompareKey::Output
      {
        ::ac::dm::types::KeyCompareResultType result;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->result);
        }
      };

      struct SecurityAccess::GetSeed::Output
      {
        ::ac::dm::types::ByteVectorType seed;
        using Generated_tag = void;
        template<typename F> void visit(F& f)
        {
          f(this->seed);
        }
      };

      namespace application_errors
      {
        using UDSServiceFailed = SecurityAccess::UDSServiceFailed;
      }

    }// namespace securityaccess
  }// namespace dm
}// namespace ac
#endif

