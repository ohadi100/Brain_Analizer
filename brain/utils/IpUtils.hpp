/**
 * @file
 * @brief     Defines ip constants and declares conversion functions between IP address types.
 */
#ifndef IP_UTILS_HPP
#define IP_UTILS_HPP

#include "autogen/gsep/SecurityEvents.hpp"
#include <vector>
#include <string>

namespace brain
{
namespace utils
{
using MacType = std::vector<uint8_t>;
using IpType = std::vector<uint8_t>;
using AddressType = std::vector<uint8_t>;
using brain::engines::security_events::SECEV_ipaddr;

/**
 * @fn  SECEV_ipaddr ConvertSecevIpAddress(const uint8_t ipAddress[]);
 * @brief convert array of uint8_t into IDS format to Security Events format
 * @param
 * @return SECEV_ipaddr - IP address in Security Events format
 */
SECEV_ipaddr ConvertSecevIpAddress(const uint8_t ipAddress[]);

/**
 * @brief   Conversion from IP address in Security Events format to IDS format
 * @param   SECEV_ipaddr const& secEvIpAddr - IP address in Security Events format
 * @return  IpType - IP address in IDS format
 */
IpType ConvertIpAddress(SECEV_ipaddr const& secEvIpAddr);

/**
 * @brief   Conversion from IP address in IDS format to Security Events format
 * @param   IpType const& ipType - IP address in IDS format
 * @return  SECEV_ipaddr - IP address in Security Events format
 */
SECEV_ipaddr ConvertIpType(IpType const& ipType);

/**
 * @brief   Conversion of an IP address in IDS format into a string (for logging purposes)
 * @param   IpType const& ipType - IP address in IDS format
 * @return  std::string
 */
std::string FormatIpType(IpType const& ipType);

} // namespace utils
} // namespace brain

namespace std
{
using brain::utils::IpType;

template <>
class hash<IpType>
{
public:
    size_t
    operator()(const IpType& ipAddress) const
    {
        // Those are just some random calculation for generating random values with optimal distribution
        std::size_t hashResult = ipAddress.size();
        for (const uint8_t& i : ipAddress)
        {
            hashResult ^= static_cast<size_t>(i) + (hashResult << 2) + (hashResult >> 2);
        }

        return hashResult;
    }
};
} // namespace std

#endif // IP_UTILS_HPP
