#pragma once
/**
 * @file
 * @brief     This file contains the definition of the Ipv6Address class and its functionality
 */
#include <string>

namespace brain
{
namespace utils
{
constexpr size_t NUM_OF_BYTES_IN_IP = 16U;
constexpr size_t NUM_OF_BYTES_IN_TEMP_BUFFER = (NUM_OF_BYTES_IN_IP * 3);

/**
 * @class               Ipv6Address
 * @brief               The Ipv6Address class holds a uint8 and a string representation of an Ipv6 address and also defines the
 *                      actions allowed on this type
 * @dataStructure       The class holds a uint8 array of fixed length to hold the IP address and a string with the same IP
 * @internalInterfaces  The Ipv6Address provides a type representation and functionality that can be done on this type
 *                      to other parts of the system, including engines and other type classes
 * @verifyCriteria      Create an Ipv6Address object using an uint8 array or a string and verify the created object
 *                      contains the correct IPv6 address
 */
class Ipv6Address final
{
public:
    /**
     * @brief   Default constructor initializes the internal data to zero and an empty string
     */
    Ipv6Address();

    /**
     * @brief   Default destructor
     */
    virtual ~Ipv6Address() = default;

    /**
     * @brief   Constructor from string
     *          Converts the string to a uint8 representation of the Ipv6 address and stores it internally
     * @param   std::string const& strAddr - the string to convert
     */
    Ipv6Address(std::string const& strAddr);

    /**
     * @brief   Constructor from a rvalue reference string
     *          Converts the string to a uint8 representation of the Ipv6 address and stores it internally
     * @param   std::string const&& strAddr - the string to convert
     */
    Ipv6Address(std::string const&& strAddr);

    /**
     * @brief   Constructor from a uint8 array
     *          Converts the uint8 array to string and stores it internally
     * @param   const uint8_t const* addr - the array representing the IPv6 address
     *          If addr is nullptr, the IP address can't be constructed
     * @param   size_t size - the size of the array. Must be NUM_OF_BYTES_IN_IP
     *          If the size is different than NUM_OF_BYTES_IN_IP, the IP address can't be constructed
     */
    Ipv6Address(uint8_t const * const addr, size_t size = NUM_OF_BYTES_IN_IP);

    /**
     * @brief   Copy constructor from another Ipv6Address object
     *          Copies the internal data to the new object
     * @param   const Ipv6Address& other - the Ipv6Address object to copy from
     */
    Ipv6Address(Ipv6Address const & other);

    /**
     * @brief    default move constructor
     */
    Ipv6Address(Ipv6Address&& other) = delete;

    /**
     * @brief   Assignment operator from another Ipv6Address object
     *          Copies the internal data to the current object
     * @param   const Ipv6Address& other - the Ipv6Address object to copy from
     * @return  Ipv6Address& - Reference to the updated Ipv6Address object
     */
    Ipv6Address& operator=(Ipv6Address const & other);

    /**
     * @brief   default move assignment operator
     */
    Ipv6Address& operator=(Ipv6Address&&) = delete;

    /**
     * @brief   Compare two Ipv6Address objects
     *          Objects are the same, if the IP address will be considered the same.
     *          Example: FFFF::1111 is the same as FFFF:0000:0000:0000:0000:0000:0000:1111
     * @param   const Ipv6Address& other - the Ipv6Address object to compare to
     * @return  bool - true if the addresses are the same. false otherwise
     */
    bool operator==(Ipv6Address const & other) const noexcept;

    /**
     * @brief   Compare two Ipv6Address objects
     *          Objects are the same, if the IP address will be considered the same
     * @param   const Ipv6Address& other - the Ipv6Address object to compare to
     * @return  bool - true if the addresses are different. false otherwise
     */
    bool operator!=(Ipv6Address const & other) const noexcept;

    /**
     * @brief   Compare two Ipv6Address objects
     *          One Ipv6Address is smaller that another Ipv6Address if compared from beginning of the address to end,
     *          one of its byte representation is smaller than the others'
     *          Mainly implemented so the class can be used as key in std::map
     * @param   const Ipv6Address& other - the Ipv6Address object to compare to
     * @return  bool - true if the addresses is smaller than the other, false if the addresses is equal or larger than the other
     */
    bool operator<(Ipv6Address const & other) const noexcept;

    /**
     * @brief   Set the Ipv6Address object using a string. Will also set its uint8 representation
     * @param   std::string const& strAddr - the string to set the address from
     */
    void Set(std::string const & strAddr);

    /**
     * @brief   Set the Ipv6Address object using a uint8 array. Will also set its string representation.
     * @param   const uint8_t* const addr - the array representing the IPv6 address
     *          size_t const& size - the size of the array. Must be NUM_OF_BYTES_IN_IP.
                If the size is different than NUM_OF_BYTES_IN_IP, the IP address can't be constructed.
     */
    void Set(uint8_t const * const addr, size_t size = NUM_OF_BYTES_IN_IP);

    /**
     * @brief   Getter of the string representation of the IPv6 address.
     * @return  std::string const& - The string representation of the IPv6 address.
     */
    std::string const& GetString() const noexcept;

    /**
     * @brief   Getter of the uint8 array representation of the IPv6 address.
     * @return  uint8_t const* - The uint8 array representation of the IPv6 address.
     */
    uint8_t const* GetByteArray() const noexcept;

#ifdef SIMULATION
    /**
     * @brief   Logs the IP address to standard output
     */
    void LogIpv6Address() const;
#endif // SIMULATION

protected:
    /**
     * @brief   parsing IP from string
     * @param   const char* const strAddr - the string to parse the address from
     */
    void parseIpFromString(char const * const strAddr) const;

    /**
     * @brief   copy the internal data
     * @param   Ipv6Address const& other - the Ipv6Address object to copy from
     * @return  none.
     */
    void copyInternalData(Ipv6Address const& other);

    /**
     * @brief   copy the internal data
     * @param   Ipv6Address const& other - the Ipv6Address object to check if equal
     * @return  bool - true if the addresses is equal, false otherwise
     */
    bool isEqual(Ipv6Address const& other) const noexcept;

    /**
     * @brief   convert the Ipv6Address to string
     */
    void convertToString();

private:
    uint8_t m_ipv6[NUM_OF_BYTES_IN_IP];
    std::string m_ipv6Str;
};

} // namespace utils
} // namespace brain
