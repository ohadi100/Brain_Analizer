/**
 * @file
 * @brief     Defines conversion functions between IP address types.
 */
#include "IpUtils.hpp"
#include <sstream>
#include <iomanip>

using namespace brain::utils;

namespace brain
{
namespace utils
{
static uint16_t constexpr IPV4_ADDRESS_VERSION_INDICATOR{0xFFFF};
static size_t constexpr IPV4_ADDRESS_SIZE_BYTES{4UL};
static size_t constexpr IPV6_ADDRESS_SIZE_BYTES{16UL};
}  // namespace utils
}  // namespace brain

SECEV_ipaddr
brain::utils::ConvertSecevIpAddress(const uint8_t ipAddress[])
{
    SECEV_ipaddr secevIp;

    std::memcpy(&secevIp, ipAddress, IPV6_ADDRESS_SIZE_BYTES);

    return secevIp;
}

IpType brain::utils::ConvertIpAddress(SECEV_ipaddr const& secEvIpAddr)
{
    uint8_t const* it{nullptr};
    size_t offset{0U};
    if (IPV4_ADDRESS_VERSION_INDICATOR == secEvIpAddr.ipv4.indicator)
    {
        it = reinterpret_cast<uint8_t const*>(&secEvIpAddr.ipv4.ipv4.value);
        offset = sizeof(secEvIpAddr.ipv4.ipv4.value);
    }
    else
    {
        it = secEvIpAddr.ipv6.value;
        offset = sizeof(secEvIpAddr.ipv6.value);
    }
    return IpType(it, it + offset);;
}

SECEV_ipaddr brain::utils::ConvertIpType(IpType const& ipType)
{
    SECEV_ipaddr ipAddr{};
    if (IPV4_ADDRESS_SIZE_BYTES == ipType.size())
    {
        ipAddr.ipv4.indicator = IPV4_ADDRESS_VERSION_INDICATOR;
        std::ignore = std::copy(ipType.begin(), ipType.end(), reinterpret_cast<uint8_t*>(&ipAddr.ipv4.ipv4.value));
    }
    else if (IPV6_ADDRESS_SIZE_BYTES == ipType.size())
    {
        std::ignore = std::copy(ipType.begin(), ipType.end(), ipAddr.ipv6.value);
    }

    return ipAddr;
}

std::string
brain::utils::FormatIpType(IpType const& ipType)
{
    std::stringstream ss;
    static size_t constexpr MAC_ADDRESS_SIZE_BYTES{6U};
    switch (ipType.size())
    {
    case IPV4_ADDRESS_SIZE_BYTES:
        for (size_t i = 0U; i < ipType.size(); ++i)
        {
            if (0U != i)
            {
                ss << ".";
            }
            ss << static_cast<int>(ipType.at(i));
        }
        break;
    case IPV6_ADDRESS_SIZE_BYTES:
        for (size_t i = 0U; i < ipType.size(); ++i)
        {
            if ((0U != i) && (0U == i % 2U))
            {
                ss << ":";
            }
            ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(ipType.at(i));
        }
        break;
    case MAC_ADDRESS_SIZE_BYTES:
        for (size_t i = 0U; i < ipType.size(); ++i)
        {
            if (0U != i)
            {
                ss << ":";
            }
            ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(ipType.at(i));
        }
        break;
    default:;
    }
    return ss.str();
}
