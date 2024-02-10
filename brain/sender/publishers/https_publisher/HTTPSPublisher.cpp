#include "HTTPSPublisher.hpp"

#include <unistd.h>

using namespace brain::publishers::https;

#if defined(SSP_SIMULATION)
static constexpr char SocketPath[] = "/tmp/data/e3/sockets/PublisherSocket.sock";
#else
static constexpr char SocketPath[] = "/data/e3/sockets/PublisherSocket.sock";
#endif  // defined(SSP_SIMULATION)


sockaddr_un CreateSocketInfo();

sockaddr_un
CreateSocketInfo()
{
    sockaddr_un socketInfo{AF_UNIX, {0}};
    strncpy(socketInfo.sun_path, SocketPath, sizeof(socketInfo.sun_path) - 1);
    return socketInfo;
}

static sockaddr_un SocketInfo = CreateSocketInfo();

bool
Publisher::Connect(ChangeModeCallback callback)
{
    m_callback = callback;
    Init();
    return true;
}

void
Publisher::Init()
{
    m_outSocket = socket(AF_UNIX, SOCK_STREAM, 0);
    if (m_outSocket < 0)
    {
        LOG_ERROR << "Failed to create the output communication socket" << LOG_NOOP;
        return;
    }

    const auto connectStat = connect(m_outSocket, reinterpret_cast<sockaddr*>(&SocketInfo), sizeof(SocketInfo));
    if (connectStat != 0)
    {
        const auto connectError = errno;
        LOG_ERROR << "Failed to connect the output socket with error " << errno << ": " << strerror(connectError)
                  << LOG_NOOP;
        close(m_outSocket);
        m_outSocket = -1;
    }
    m_callback(EventType::CONNECTED);
}
bool
Publisher::Disconnect()
{
    if (m_outSocket >= 0)
    {
        close(m_outSocket);
    }
    return true;
}

Publisher::~Publisher()
{
    Disconnect();
}

bool
Publisher::SendMessage(std::shared_ptr<std::vector<uint8_t>> payload)
{
    if (m_outSocket < 0)
    {
        LOG_DEBUG << "Invalid out socket, re-initializing" << LOG_NOOP;
        Init();

        if (m_outSocket < 0)
        {
            LOG_WARNING << "Failed publisher init, message skipped" << LOG_NOOP;

            return false;
        }
    }

    const auto bytes = payload->size();
    const auto sent  = send(m_outSocket, &bytes, sizeof(bytes), 0);

    if (sent < 0)
    {
        LOG_WARNING << "Failed to send the message size with " << errno << LOG_NOOP;
        return false;
    }

    if (sent != sizeof(bytes))
    {
        LOG_WARNING << "Failed to send the complete message size" << LOG_NOOP;
        return false;
    }

    const auto sentMessage = send(m_outSocket, payload->data(), bytes, 0);

    if (sentMessage < 0)
    {
        LOG_WARNING << "Failed to send the message size with " << errno << LOG_NOOP;
        return false;
    }

    if (sentMessage != sizeof(bytes))
    {
        LOG_WARNING << "Failed to send the complete message size" << LOG_NOOP;
        return false;
    }

    return true;
}