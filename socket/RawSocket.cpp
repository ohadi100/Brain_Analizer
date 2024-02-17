#pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wcast-align"
#pragma GCC diagnostic ignored "-Wsign-conversion"

#include <errno.h>
#include <poll.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <linux/if_packet.h>
#include <net/ethernet.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <sys/socket.h>
#include <sys/types.h>

#include <string.h>
#include <Logger.hpp>

#include "RawSocket.hpp" // implemented

SET_LOG_MODULE_NAME("RawSocket")

using common::ids_socket::RawSocket;

RawSocket::RawSocket(const std::string& ifName, uint16_t ethType)
  : m_ifName(ifName)
  , m_ethType(ethType)
  , m_rawsockfd(-1)
  , m_isConnected(false)
  , m_mmap(NULL)
{
    LOG_INFO << "initializing RawSocket" << LOG_NOOP;
}

RawSocket::~RawSocket()
{
    try
    {
        Close();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "close socket failed and got exception." << LOG_NOOP;
    } //only for parasoft violations
}

bool RawSocket::Connect()
{
    LOG_INFO << "Trying to connect Raw socket" << LOG_NOOP;

    /* Create socket */
    m_rawsockfd = socket(AF_PACKET, SOCK_RAW, htons(m_ethType));
    if (0 > m_rawsockfd)
    {
        LOG_ERROR << "Could not create socket" << LOG_NOOP;
        return false;
    }

    /* Get interface index */
    struct ifreq ifr;
    std::ignore = memset(&ifr, 0, sizeof(ifr));
    std::ignore = strncpy(static_cast<char*>(static_cast<void *>(ifr.ifr_name)), m_ifName.c_str(), IFNAMSIZ - 1);
    if (-1 == ioctl(m_rawsockfd, SIOCGIFINDEX, &ifr))
    {
        LOG_ERROR << "Could not get interface index" << LOG_NOOP;
        Close();
        return false;
    }

    /* Set the socket's receive buffer size */
    int const version = TPACKET_V3;
    if (-1 == setsockopt(m_rawsockfd, SOL_PACKET, PACKET_VERSION, (const void *)&version, sizeof(version)))
    {
        LOG_ERROR << "Could not set packet version" << LOG_NOOP;
        Close();
        return false;
    }

    /* This is the maximal frame size. It should be at least: TPACKET_ALIGN(TPACKET3_HDRLEN + MAX_MESSAGE_LENGTH) */
    static constexpr uint32_t SOCKET_MAX_FRAME_SIZE = (1U << 13U);
    /* This is the time in milliseconds to retire a single block */
    static constexpr uint32_t SOCKET_BLOCK_TIMEOUT = 500U;

    struct tpacket_req3 req;
    std::ignore           = memset(&req, 0, sizeof(req));
    req.tp_block_size     = SOCKET_BLOCK_SIZE;
    req.tp_block_nr       = SOCKET_BLOCK_NUM;
    req.tp_frame_size     = SOCKET_MAX_FRAME_SIZE;
    req.tp_frame_nr       = (req.tp_block_size * req.tp_block_nr) / req.tp_frame_size;
    req.tp_retire_blk_tov = SOCKET_BLOCK_TIMEOUT;
    if (-1 == setsockopt(m_rawsockfd, SOL_PACKET, PACKET_RX_RING, (const void*)&req, sizeof(req)))
    {
        LOG_ERROR << "Could not set packet rx ring" << LOG_NOOP;
        Close();
        return false;
    }

    m_curBlock = 0U;
    m_curFrames = 0U;
    m_curFrameIdx = 0U;
    m_curOffset = 0U;

    /* This requires capability: CAP_IPC_LOCK */
    m_mmap = (uint8_t*)mmap(NULL,
                            SOCKET_BUFFER_SIZE,
                            static_cast<uint8_t>(PROT_READ) | static_cast<uint8_t>(PROT_WRITE),
                            static_cast<uint8_t>(MAP_SHARED) | static_cast<uint8_t>(MAP_LOCKED),
                            m_rawsockfd,
                            0);
    if (MAP_FAILED == m_mmap)
    {
        m_mmap = NULL;
        LOG_ERROR << "Could not mmap socket" << LOG_NOOP;
        Close();
        return false;
    }

    /* Bind socket to receive frames only from the given interface */
    struct sockaddr_ll ifaddress;
    std::ignore            = memset(&ifaddress, 0, sizeof(struct sockaddr_ll));
    ifaddress.sll_family   = AF_PACKET;
    ifaddress.sll_protocol = htons(m_ethType);
    ifaddress.sll_ifindex  = ifr.ifr_ifindex;

    if (-1 == bind(m_rawsockfd, (const struct sockaddr *)&ifaddress, sizeof(ifaddress)))
    {
        LOG_ERROR << "Could not bind" << LOG_NOOP;
        Close();
        return false;
    }

    /* Register the multicast address */
    struct packet_mreq mreq;
    std::ignore     = memset(&mreq, 0, sizeof(struct packet_mreq));
    mreq.mr_ifindex = ifaddress.sll_ifindex;
    mreq.mr_type    = PACKET_MR_MULTICAST;
    mreq.mr_alen    = MAC_LEN;
    std::ignore     = memcpy(mreq.mr_address, m_mrAddress, MAC_LEN);

    if (-1 == setsockopt(m_rawsockfd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, (const void *)&mreq, sizeof(struct packet_mreq)))
    {
        LOG_ERROR << "Could not register multicast address" << LOG_NOOP;
        Close();
        return false;
    }

    LOG_INFO << "Successfully connected to socket" << LOG_NOOP;
    m_isConnected = true;
    return true;
}

bool RawSocket::Receive(char * const buffer, uint32_t const bufLen, uint32_t const timeout)
{
    LOG_WARNING << "Using empty Receive implementation for Raw socket" << LOG_NOOP;
    /* Not relevant for this class */
    (void) buffer;
    (void) bufLen;
    (void) timeout;
    return false;
}

bool RawSocket::Receive(char ** const buffer, uint32_t * const bufLen)
{
    LOG_WARNING << "Using empty Receive implementation for Raw socket" << LOG_NOOP;
    /* Not relevant for this class */
    (void) buffer;
    (void) bufLen;
    return false;
}


struct tpacket_block_desc * RawSocket::getBlockPtr(void) noexcept
{
    return (struct tpacket_block_desc *) (m_mmap + (SOCKET_BLOCK_SIZE * m_curBlock));
}

void RawSocket::flushBlock(void) noexcept
{
    getBlockPtr()->hdr.bh1.block_status = TP_STATUS_KERNEL;

    m_curBlock = (m_curBlock + 1) % SOCKET_BLOCK_NUM;
    m_curFrames = 0U;
    m_curFrameIdx = 0U;
    m_curOffset = 0U;
}

bool RawSocket::Receive(char ** const buffer, uint32_t * const bufLen, uint32_t const timeout)
{
    auto pbd = getBlockPtr();

    /* Check if no more frames in current block */
    if (m_curFrameIdx >= m_curFrames)
    {
        /* Block finished - if it was actually started then flush it */
        if (0 != m_curFrames)
        {
            flushBlock();
            pbd = getBlockPtr();
        }

        /* Wait for next block */
        if (0U != (pbd->hdr.bh1.block_status & static_cast<uint8_t>(TP_STATUS_USER)))
        {
            struct pollfd pfd;
            std::ignore = memset(&pfd, 0, sizeof(pfd));
            pfd.fd      = m_rawsockfd;
            pfd.events  = static_cast<uint8_t>(POLLIN) | static_cast<uint8_t>(POLLERR);

            int const pollReturnValue = poll(&pfd, 1, timeout * 1000);

            static constexpr int POLL_ERROR_RETURN_VALUE = -1;
            if (POLL_ERROR_RETURN_VALUE == pollReturnValue)
            {
                LOG_ERROR << "poll failed with errno [" << errno << "] for Raw socket" << LOG_NOOP;
                return false;
            }

            /* TODO: properly handle errors such as (pfd.revents & POLLERR) */

            /* Check for timeout */
            if (0U != (pbd->hdr.bh1.block_status & static_cast<uint8_t>(TP_STATUS_USER)))
            {
                return false;
            }
        }

        /* Examine the new block */
        m_curFrames = pbd->hdr.bh1.num_pkts;
        /* Check for an empty block */
        if (0U != m_curFrames)
        {
            flushBlock();
            return false;
        }
    }

    /* Handle next frame in the block */
    auto const ppd = (struct tpacket3_hdr *)((char *)pbd + pbd->hdr.bh1.offset_to_first_pkt + m_curOffset);
    *buffer = (char *)ppd + ppd->tp_mac;
    *bufLen = ppd->tp_snaplen;

    m_curFrameIdx++;
    m_curOffset += ppd->tp_next_offset;
    return true;
}

void RawSocket::Close()
{
    LOG_INFO << "Closing raw socket" << LOG_NOOP;

    m_isConnected = false;
    if (nullptr != m_mmap)
    {
		if (-1 == munmap(m_mmap, SOCKET_BUFFER_SIZE))
        {
            LOG_ERROR << "Closing Raw socket - Failed to munmap for Raw socket" << LOG_NOOP;
        }
        m_mmap = NULL;
    }
    if (0 < m_rawsockfd)
    {
        if (-1 == close(m_rawsockfd))
        {
            LOG_ERROR << "Closing Raw socket - Failed to close the socket, errno = " << strerror(errno)
                      << " for Raw socket" << LOG_NOOP;
        }
        else
        {
            LOG_VERBOSE << "Raw socket is closed" << LOG_NOOP;
        }
        m_rawsockfd = 0;
    }

    LOG_VERBOSE << "Raw socket is closed" << LOG_NOOP;
}

char * RawSocket::GetBufferData(char * buffer, uint32_t& buflen, uint32_t const offset) const
{
    if(nullptr == buffer)
    {
        LOG_ERROR << "buffer is nullptr" << LOG_NOOP;
        return nullptr;
    }

    if(offset >= buflen)
    {
        return nullptr;
    }

    buflen -= offset; //Updating the buffer length
    return &buffer[offset]; //cutting the packet header (offset size)
}
