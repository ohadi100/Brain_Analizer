#include "Ipv6Address.hpp"  // implemented

#include "common/utils/logger/Logger.hpp"
#include "common/utils/os/linux/network.hpp"
#include <cstring>

using brain::utils::Ipv6Address;


Ipv6Address::Ipv6Address() :
    m_ipv6{0,0},
    m_ipv6Str("")
{
}

Ipv6Address::Ipv6Address(std::string const& strAddr) :
    m_ipv6{0,0},
    m_ipv6Str(strAddr)
{
    parseIpFromString(strAddr.c_str());
}


Ipv6Address::Ipv6Address(std::string const&& strAddr) :
    m_ipv6{0,0},
    m_ipv6Str(strAddr)
{
    parseIpFromString(strAddr.c_str());
}

Ipv6Address::Ipv6Address(uint8_t const * const addr, size_t size) :
    m_ipv6{},
    m_ipv6Str("")
{
    if ((nullptr != addr) && (NUM_OF_BYTES_IN_IP == size))
    {
        std::ignore = std::memcpy(m_ipv6, addr, NUM_OF_BYTES_IN_IP);
    }

    convertToString();
}

Ipv6Address::Ipv6Address(Ipv6Address const & other) :
    m_ipv6{},
    m_ipv6Str("")
{
    copyInternalData(other);
}

Ipv6Address & Ipv6Address::operator=(Ipv6Address const & other)
{
    copyInternalData(other);
    return *this;
}

bool Ipv6Address::operator==(Ipv6Address const & other) const noexcept
{
    return isEqual(other);
}

bool Ipv6Address::operator!=(Ipv6Address const & other) const noexcept
{
    return !isEqual(other);
}

bool Ipv6Address::operator<(Ipv6Address const & other) const noexcept
{
    uint8_t const * const otherIp = other.GetByteArray();
    for (uint32_t i = 0U; i < NUM_OF_BYTES_IN_IP; i++)
    {
        if (m_ipv6[i] < otherIp[i])
        {
            return true;
        }
        else
        {
            if (m_ipv6[i] > otherIp[i])
            {
                break;
            }
        }
    }

    return false;
}

void Ipv6Address::Set(std::string const& strAddr)
{
    m_ipv6Str = strAddr;
    parseIpFromString(strAddr.c_str());
}

void Ipv6Address::Set(uint8_t const * const addr, size_t size)
{
    if ((NUM_OF_BYTES_IN_IP ==  size) && (nullptr != addr))
    {
        std::ignore = std::memcpy(m_ipv6, addr, NUM_OF_BYTES_IN_IP);
        convertToString();
    }
    else
    {
        LOG_ERROR << "Can't create IP from input" << LOG_NOOP;
    }
}

std::string const& Ipv6Address::GetString() const noexcept
{
    return m_ipv6Str;
}

uint8_t const* Ipv6Address::GetByteArray() const noexcept
{
    return m_ipv6;
}

void Ipv6Address::copyInternalData(Ipv6Address const& other)
{
    if (this != &other)
    {
        uint8_t const * const otherIp = other.GetByteArray();
        std::ignore                   = std::memcpy(m_ipv6, otherIp, NUM_OF_BYTES_IN_IP);

        m_ipv6Str = other.GetString();
    }
}

bool Ipv6Address::isEqual(Ipv6Address const& other) const noexcept
{
    uint8_t const * const otherIp = other.GetByteArray();
    return (0 == std::memcmp(m_ipv6, otherIp, NUM_OF_BYTES_IN_IP));
}

void Ipv6Address::parseIpFromString(char const * const strAddr) const
{
    if (false == common::ipv6StrToAddr(strAddr, m_ipv6, sizeof(m_ipv6)))
    {
        LOG_ERROR << "Invalid IP address" << LOG_NOOP;
    }
}

void Ipv6Address::convertToString()
{
    m_ipv6Str.clear();

    char buffer[NUM_OF_BYTES_IN_TEMP_BUFFER] = {0};
    uint32_t j = 0U;
    for (uint32_t i = 0U ; i < NUM_OF_BYTES_IN_IP ; i++)
    {
        std::ignore = std::sprintf(&buffer[j], "%02X", m_ipv6[i]);
        j += 2;
    }

    m_ipv6Str = buffer;
}

#ifdef SIMULATION
void Ipv6Address::LogIpv6Address() const
{
    char buffer[NUM_OF_BYTES_IN_TEMP_BUFFER] = {0};
    uint32_t j = 0U;
    for (uint32_t i = 0U; i < NUM_OF_BYTES_IN_IP; i++)
    {
        static_cast<void>(std::sprintf(&buffer[j], "%02X", m_ipv6[i]));
        j += 2;
        if ((0 != i % 2) && ((NUM_OF_BYTES_IN_IP - 1) != i))
        {
            static_cast<void>(std::sprintf(&buffer[j], "%s", ":"));
            j++;
        }
    }

    std::string ipv6Addr = buffer;
    LOG_INFO << "IPv6Addr: " << ipv6Addr << LOG_NOOP;
}
#endif // SIMULATION
