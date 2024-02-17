#ifndef RAW_SOCKET_HPP
#define RAW_SOCKET_HPP

/**
 * @file 
 * @brief     A class that deals with opening and reading from a Raw Socket
 */
#include <network.hpp>

#include "BaseSocket.hpp" // implemented

namespace common
{
namespace ids_socket
{

    /* This is the byte size we wait for in a single poll. It is expected to contain multiple frames */
    constexpr uint32_t SOCKET_BLOCK_SIZE = (1 << 18);
    /* This is the number of blocks in the entire buffer we use for the socket */
    constexpr uint32_t SOCKET_BLOCK_NUM = 10U;
    /* This is the total buffer size we use for the socket */
    constexpr size_t SOCKET_BUFFER_SIZE = (SOCKET_BLOCK_SIZE * SOCKET_BLOCK_NUM);

    constexpr char INTERFACE_NAME[] = "eth0.2066";
    constexpr uint16_t ETH_TYPE = 0x08ff;

    constexpr uint16_t MAC_LEN = 6U;

 /* @brief   The RawSocket class is implement the IBaseSocket interface.
            The RawSocket class implement the all abstract class of IBaseSocket.
            It allocate socket, bind it and wait for a connection.
            It also wait to receive packets and data messages.
 */
class RawSocket : public IBaseSocket
{

public:

    /**
     * @brief   Constructor
     */
    RawSocket(const std::string& ifName, uint16_t ethType);

    /**
     * @brief   Destructor
     */
    virtual ~RawSocket();

    /**
     * @brief    default copy constructor
     */
    RawSocket(const RawSocket& other) = delete;

    /**
     * @brief    default move constructor
     */
    RawSocket(RawSocket&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    RawSocket& operator=(RawSocket const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    RawSocket& operator=(RawSocket&&) = delete;

    /**
     * @brief   Connect to the Unix Domain Socket. The socket is changed to non-blocking mode
     * @return  bool - true if successful, false otherwise
     */
    bool Connect() override;

    /**
     * @brief   Allocates a new buffer for the received data. Should be fread by the user of this function
     * @param   char * buffer as outval buffer
     * @return  bool - true if successful, false otherwise
     */
    bool Receive(char * const buffer, uint32_t const bufLen, uint32_t const timeout) override;

    /**
     * @brief   Receive data and allocate a buffer. The buffer is valid until next call to Receive or Close
     * @param   char ** buffer as outval buffer
     * @return  true if successful, false otherwise
     */
    bool Receive(char ** const buffer, uint32_t * const bufLen, uint32_t const timeout) override;

	/**
     * @brief   Receive data and allocate a buffer. The buffer is valid until next call to Receive or Close
     * @param   char ** buffer as outval buffer
     * @return  true if successful, false otherwise
     */
    bool Receive(char ** const buffer, uint32_t * const bufLen) override;

    /**
     * @brief   Close the socket
     */
    void Close() override;

    /**
     * @brief   return the right offset of the buffer data.
     * @param   char * buffer the original pointer.
     * @param   uint32_t& buflen the buffer length.
     * @param   uint32_t const offset
     * @return  char * the pointer to the right offset.
     */
    char * GetBufferData(char * buffer, uint32_t& buflen, uint32_t const offset) const override;

    /**
     * @brief   return is the socket connected
     * @return  true iff connected
     */
    inline bool IsConnected() const override
    {
        return m_isConnected;
    }

    /**
     * @brief   Get the receive error status of the socket
     * @param   none
     * @return  true if an error occured, false otherwise
     */
    bool IsReceiveError() const override
    {
        return false;//not used
    }

private:

    struct tpacket_block_desc * getBlockPtr(void) noexcept;
    void flushBlock(void) noexcept;

    std::string m_ifName;
    uint16_t m_ethType {};
    unsigned char const m_mrAddress[MAC_LEN] = { 0x33, 0x33, 0x00, 0x00, 0x00, 0x10 };
    int m_rawsockfd;

    std::string const m_fileName;
    bool m_isConnected {};

    uint8_t * m_mmap;           /* RX ring memory map */
    unsigned int m_curBlock {};    /* Block index inside the ring that we currently read from */
    unsigned int m_curFrames {};   /* Total frames inside the block that we currently read from */
    unsigned int m_curFrameIdx {}; /* Next frame index inside the block that we currently read from */
    unsigned int m_curOffset {};   /* Offset of next frame inside the block that we currently read from */
};

} //nm ids_socket
} //nm common
#endif //RAW_SOCKET_HPP