/// @file
///
/// @author Elektrobit Automotive GmbH, 91058 Erlangen, Germany
///
/// @copyright 2024 Elektrobit Automotive GmbH
/// All rights exclusively reserved for Elektrobit Automotive GmbH,
/// unless otherwise expressly agreed.
/// This file is generated. Do not edit!
// -- Inclusion protection
#ifndef VWG_SERVICES_DIAG_D_1178_DATAIDENTIFIER_IDSSOMEIPDATABUSSERVICEIMPLAUSIBLE_COMMON_H
#define VWG_SERVICES_DIAG_D_1178_DATAIDENTIFIER_IDSSOMEIPDATABUSSERVICEIMPLAUSIBLE_COMMON_H

#include "ara/com/types.h"
#include "dataidentifier_idssomeipdatabusserviceimplausible_types.h"
// -- Service namespace
namespace vwg
{

  namespace services
  {

    namespace diag
    {

      namespace d_1178
      {

        // -- Service Identifier and Service Version Classes
        class DataIdentifier_IDSSomeipDataBusServiceImplausible
        {
          public:
          static constexpr ::ara::com::ServiceIdentifierType id()
          { return ::ara::com::ServiceIdentifierType("vwg::services::diag::d_1178::DataIdentifier_IDSSomeipDataBusServiceImplausible"); }

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

          struct Read
          {
            static constexpr ::ac::com::cpp_binding::Method_id Id{ 1u };

            struct Output;
            using Signature = Output(::ac::dm::types::MetaInfoType const&);

            static std::exception_ptr GetApplicationErrorExceptionPtr(
            ::ac::com::cpp_binding::Error_id error, std::vector<std::uint8_t> const& data);
          };

          class UDSServiceFailed : public ::ara::com::ApplicationErrorException
          {
            public:
            static constexpr ::ac::com::cpp_binding::Error_id Id{ 2u };
            struct Output
            {
              ::ac::dm::types::UDSResponseCodeType Read_nrc;
              using Generated_tag = void;
              template<typename F> void visit(F& f)
              {
                f(this->Read_nrc);
              }
            };

            /// ctor as per SWS
            UDSServiceFailed(::ac::dm::types::UDSResponseCodeType Read_nrc);

            /// ctor, internal
            UDSServiceFailed(::ac::com::someip::serialization::buffer_t const& data);

            const char* what() const noexcept final override
            {
              return "DataIdentifier_IDSSomeipDataBusServiceImplausible::UDSServiceFailed::2";
            }

            const ::ac::dm::types::UDSResponseCodeType& get_Read_nrc() const
            {
              return m_Output.Read_nrc;
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
          static constexpr std::uint8_t number_of_methods(){ return 2u; }
        };

        struct DataIdentifier_IDSSomeipDataBusServiceImplausible::Read::Output
        {
          ::vwg::services::diag::datatypes::fixed_size_array_with_1_uint8_items dataRecord_Count_of_services;
          ::ara::stdtypes::ByteArray dataRecord_Service_ID_Method_ID_Ipv6_address_Port;
          using Generated_tag = void;
          template<typename F> void visit(F& f)
          {
            f(this->dataRecord_Count_of_services);
            f(this->dataRecord_Service_ID_Method_ID_Ipv6_address_Port);
          }
        };

        namespace application_errors
        {
          using UDSServiceFailed = DataIdentifier_IDSSomeipDataBusServiceImplausible::UDSServiceFailed;
        }

      }// namespace d_1178
    }// namespace diag
  }// namespace services
}// namespace vwg
#endif

