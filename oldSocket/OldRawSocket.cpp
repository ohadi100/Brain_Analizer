/**
 * @file      RawSocket.cpp
 * @brief     A base class that deals with opening and reading from a Raw Socket

 */
#include "common/ids_socket/RawSocket.hpp"
#include "Logger.hpp"
#include "common/os/network.hpp"
#include "common/counter_manager/MebCounterManager.h"
#include "brain/brain_manager/BrainApp.hpp"

#include <string.h>
#include <poll.h>
#include <errno.h>
#include <sys/mman.h>

/* This is the byte size we wait for in a single poll. It is expected to contain multiple frames */
#define SOCKET_BLOCK_SIZE (1 << 18)
/* This is the number of blocks in the entire buffer we use for the socket */
#define SOCKET_BLOCK_NUM 10
/* This is the total buffer size we use for the socket */
#define SOCKET_BUFFER_SIZE (SOCKET_BLOCK_SIZE * SOCKET_BLOCK_NUM)
/* This is the maximal frame size. It should be at least: TPACKET_ALIGN(TPACKET3_HDRLEN + MAX_MESSAGE_LENGTH) */
#define SOCKET_MAX_FRAME_SIZE (1 << 13)
/* This is the time in milliseconds to retire a single block */
#define SOCKET_BLOCK_TIMEOUT 500

constexpr int POLL_ERROR_RETURN_VALUE = -1;
constexpr uint8_t CAN_PDU_HEADER_SIZE = 14U;

using common::ids_socket::RawSocket;

RawSocket::RawSocket(const std::string& ifName, const int& ethType) : m_ifName(ifName), m_ethType(ethType), m_rawsockfd(-1), m_mmap(NULL)
{
    LOG(CommonLogerLevel::kInfo) << "initializing RawSocket";
}

RawSocket::~RawSocket()
{
    Close();
}

bool RawSocket::Connect()
{
    LOG(CommonLogerLevel::kDebug) << "trying to connect socket";

    /* Create socket */
    m_rawsockfd = socket(AF_PACKET, SOCK_RAW, htons(m_ethType));
    if (m_rawsockfd < 0)
    {
        LOG(CommonLogerLevel::kError) << "Could not create socket";
        return false;
    }

    /* Get interface index */
    struct ifreq ifr;
    static_cast<void>(memset(&ifr, 0, sizeof(ifr)));
    static_cast<void>(strncpy((char *)ifr.ifr_name, m_ifName.c_str(), IFNAMSIZ - 1));
    if (ioctl(m_rawsockfd, SIOCGIFINDEX, &ifr) == -1)
    {
        LOG(CommonLogerLevel::kError) << "Could not get interface index";
        Close();
        return false;
    }

    /* Set the socket's receive buffer size */
    int const version = TPACKET_V3;
    if (setsockopt(m_rawsockfd, SOL_PACKET, PACKET_VERSION, (const void *)&version, sizeof(version)) == -1)
    {
        LOG(CommonLogerLevel::kError) << "Could not set packet version";
        Close();
        return false;
    }

    struct tpacket_req3 req;
    static_cast<void>(memset(&req, 0, sizeof(req)));
    req.tp_block_size = SOCKET_BLOCK_SIZE;
    req.tp_block_nr = SOCKET_BLOCK_NUM;
    req.tp_frame_size = SOCKET_MAX_FRAME_SIZE;
    req.tp_frame_nr = (req.tp_block_size * req.tp_block_nr) / req.tp_frame_size;
    req.tp_retire_blk_tov = SOCKET_BLOCK_TIMEOUT;
    if (setsockopt(m_rawsockfd, SOL_PACKET, PACKET_RX_RING, (const void *)&req, sizeof(req)) == -1)
    {
        LOG(CommonLogerLevel::kError) << "Could not set packet rx ring";
        Close();
        return false;
    }

    m_curBlock = 0;
    m_curFrames = 0;
    m_curFrameIdx = 0;
    m_curOffset = 0;

    /* This requires capability: CAP_IPC_LOCK */
    m_mmap = (uint8_t *)mmap(NULL, SOCKET_BUFFER_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_LOCKED, m_rawsockfd, 0);
    if (m_mmap == MAP_FAILED)
    {
        m_mmap = NULL;
        LOG(CommonLogerLevel::kError) << "Could not mmap socket";
        Close();
        return false;
    }

    /* Bind socket to receive frames only from the given interface */
    struct sockaddr_ll ifaddress;
    static_cast<void>(memset(&ifaddress, 0, sizeof(struct sockaddr_ll)));
    ifaddress.sll_family = AF_PACKET;
    ifaddress.sll_protocol = htons(m_ethType);
    ifaddress.sll_ifindex = ifr.ifr_ifindex;

    if (bind(m_rawsockfd, (const struct sockaddr *)&ifaddress, sizeof(ifaddress)) == -1)
    {
        LOG(CommonLogerLevel::kError) << "Could not bind";
        Close();
        return false;
    }

    /* Register the multicast address */
    struct packet_mreq mreq;
    static_cast<void>(memset(&mreq, 0, sizeof(struct packet_mreq)));
    mreq.mr_ifindex = ifaddress.sll_ifindex;
    mreq.mr_type = PACKET_MR_MULTICAST;
    mreq.mr_alen = MAC_LEN;
    static_cast<void>(memcpy(mreq.mr_address, m_mrAddress, MAC_LEN));

    if (setsockopt(m_rawsockfd, SOL_PACKET, PACKET_ADD_MEMBERSHIP, (const void *)&mreq, sizeof(struct packet_mreq)) == -1)
    {
        LOG(CommonLogerLevel::kError) << "Could not register multicast address";
        Close();
        return false;
    }

    LOG(CommonLogerLevel::kInfo) << "Successfully connected to socket: " << std::hex << m_ethType;
    m_isConnected = true;
    return true;
}

bool RawSocket::Receive(char *const buffer, uint32_t const bufLen, uint32_t const timeout)
{
    LOG(CommonLogerLevel::kWarning) << "RawSocket::Receive - Using empty Receive implementation.";
    /* Not relevant for this class */
    static_cast<void>(buffer);
    static_cast<void>(bufLen);
    static_cast<void>(timeout);
    return false;
}

bool RawSocket::Receive(char **const buffer, uint32_t *const bufLen)
{
    LOG(CommonLogerLevel::kWarning) << "RawSocket::Receive - Using empty Receive implementation.";
    /* Not relevant for this class */
    static_cast<void>(buffer);
    static_cast<void>(bufLen);
    return false;
}

struct tpacket_block_desc *RawSocket::getBlockPtr(void) noexcept
{
    return (struct tpacket_block_desc *)(m_mmap + (SOCKET_BLOCK_SIZE * m_curBlock));
}

void RawSocket::flushBlock(void)
{
    getBlockPtr()->hdr.bh1.block_status = TP_STATUS_KERNEL;

    m_curBlock = (m_curBlock + 1) % SOCKET_BLOCK_NUM;
    m_curFrames = 0;
    m_curFrameIdx = 0;
    m_curOffset = 0;
}

bool RawSocket::Receive(char **const buffer, uint32_t *const bufLen, uint32_t const timeout)
{
    auto pbd = getBlockPtr();

    /* Check if no more frames in current block */
    if (m_curFrameIdx >= m_curFrames)
    {
        /* Block finished - if it was actually started then flush it */
        if (m_curFrames != 0)
        {
            flushBlock();
            pbd = getBlockPtr();
        }

        /* Wait for next block */
        if (!(pbd->hdr.bh1.block_status & TP_STATUS_USER))
        {
            struct pollfd pfd;
            static_cast<void>(memset(&pfd, 0, sizeof(pfd)));
            pfd.fd = m_rawsockfd;
            pfd.events = POLLIN | POLLERR;

            int const pollReturnValue = poll(&pfd, 1, timeout * 1000);

            if (pollReturnValue == POLL_ERROR_RETURN_VALUE)
            {
                LOG(CommonLogerLevel::kError) << "RawSocket::Receive - poll failed with errno: " << errno;
                return false;
            }

            /* TODO: properly handle errors such as (pfd.revents & POLLERR) */

            /* Check for timeout */
            if (!(pbd->hdr.bh1.block_status & TP_STATUS_USER))
                return false;
        }

        /* Examine the new block */
        m_curFrames = pbd->hdr.bh1.num_pkts;
        /* Check for an empty block */
        if (!m_curFrames)
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
    LOG(CommonLogerLevel::kDebug) << "RawSocket::Close - Closing raw socket";

    m_isConnected = false;
    if (m_mmap != nullptr)
    {
        if (static_cast<int>(munmap(m_mmap, SOCKET_BUFFER_SIZE)) == -1)
        {
            LOG(CommonLogerLevel::kError) << "RawSocket - failed to unmap";
        }
        m_mmap = NULL;
    }

    if (m_rawsockfd > 0)
    {
        if (close(m_rawsockfd) == -1)
        {
            LOG(CommonLogerLevel::kError) << "RawSocket - failed to close the socket, errorno = " << strerror(errno);
        }
        else
        {
            LOG(CommonLogerLevel::kDebug) << "RawSocket::Close - Row socket is closed";
        }
        m_rawsockfd = 0;
    }
}

char *RawSocket::GetBufferData(char *buffer, uint32_t &buflen, uint32_t const offset)
{
    if (nullptr == buffer)
    {
        LOG(CommonLogerLevel::kError) << "buffer is nullptr";
        return nullptr;
    }

    if (offset >= buflen)
    {
        return nullptr;
    }

    buflen -= offset;       // Updating the buffer length
    return &buffer[offset]; // cutting the packet header (offset size)
}

bool RawSocket::IsConnected()
{
    return m_isConnected;
}
