#include "brain/communicator/uds/SocketCommunicator.hpp"
#include "common/thread_handler/ThreadNamesConstants.hpp"
#include "common/counter_manager/CounterNames.hpp"

#include <string.h>
#include <sys/prctl.h>

using brain::brain_communicator::SocketCommunicator;
using common::thread_handler::EThreadStatus;

SocketCommunicator::SocketCommunicator(SensorDataQueuesManagerPtr queuesManager,
                                       CounterManagerPtr          debugCounters,
                                       uint32_t                   flushThreshold,
                                       DiagnosticsManagerPtr      diagnosticsManager,
                                       CommunicatorId const       communicatorId,
                                       NoiseFilterPtr             sensorNoiseFilter)
  : Communicator(queuesManager, flushThreshold, communicatorId, sensorNoiseFilter)
  , m_runThread(false)
  , m_debugCounters(debugCounters)
  , m_diagnosticsManager(diagnosticsManager)
{
    if (m_debugCounters)
    {
        m_failConnectSocket = m_debugCounters->CreateCounter(common::counters::errors::FAIL_CONNECT_TO_SOCKET,
                                                             EventCounterLevelType::COUNTER_ERROR);
    }
}

SocketCommunicator::~SocketCommunicator()
{
    try
    {
        Stop();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& e)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "Stop communication failed and got exception " << e.what() << LOG_NOOP;
    }  // only for parasoft violations
}

void SocketCommunicator::Start()
{
    if (m_runThread)
    {
        LOG_WARNING << "Communicator to start, with thread already running. Stopping and starting again!" << LOG_NOOP;
        Stop();
    }

    m_runThread = true;
    m_thread = std::make_unique<std::thread>(&SocketCommunicator::handleSocket, this);
}

void SocketCommunicator::Stop()
{
    if (m_thread)
    {
        m_runThread = false;
        m_sleeper.WakeUp();
        if (m_thread->joinable())
        {
            m_thread->join();
        }
    }

    // Handle SDs before shutting down
    flushAllChunks();
}

EThreadStatus SocketCommunicator::handleSocket()
{
    std::ignore = prctl(PR_SET_NAME, threads_names::ids::SOCKET_COMMUNICATOR, 0, 0, 0);

    if (nullptr == m_socket)
    {
        LOG_FATAL << "Communicator handles with nullptr socket!" << LOG_NOOP;
        return EThreadStatus::eFatalError;
    }

    std::array<char, MAX_MESSAGE_LENGTH_BYTES> parseBuffer = {};
    bool wasConnected = false;

    while (m_runThread)
    {
        try
        {
            bool shouldParse = true;
            if (!m_socket->IsConnected())
            {
                LOG_VERBOSE << "Socket not connected" << LOG_NOOP;
                if (wasConnected)
                {
                    LOG_WARNING << "Socket was disconnected, connecting" << LOG_NOOP;
                    wasConnected = false;
                }

                bool connectionSuccess = m_socket->Connect();
                if (connectionSuccess)
                {
                    LOG_INFO << "Socket connected" << LOG_NOOP;
                }
                else
                {
                    LOG_DEBUG << "Can't connect to socket!" << LOG_NOOP;
                    common::counters::IncreaseCounter(m_failConnectSocket);

                    static constexpr uint32_t RECONNECT_SOCKET_TIMEOUT_SEC{10U};

                    auto const reason = m_sleeper.SleepSeconds(RECONNECT_SOCKET_TIMEOUT_SEC);
                    if (common::ConditionalSleep::WakeUpReason::SIGNAL == reason)
                    {
                        LOG_WARNING << "After unsuccessful connect exit from conditional sleep with signal" << LOG_NOOP;
                        break;  // exit immediatelly on signal
                    }
                    shouldParse = false;

                    // Diag DTC - 0x600504 - ids_uds_interface_unavailable
                    m_diagnosticsManager->updateDiagnosticsUDSEvent();
                }

                // Diag DTC - 0x600501 - ids_evt_EventIdsBackendCommunicationUnavailable
                m_diagnosticsManager->UpdateServiceDiscoveryStatus(m_communicatorId, connectionSuccess);
            }

            if (shouldParse)
            {
                wasConnected = true;
                handlePacket(parseBuffer.data());
            }
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (std::exception const& e)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "Got exception in loop: " << e.what() << LOG_NOOP;
        }
    }

    m_socket->Close();
    LOG_DEBUG << "End UDS handler" << LOG_NOOP;
    return EThreadStatus::eSuccess;
}

void SocketCommunicator::handlePacket(char* parseBuffer)
{
    if (nullptr == m_socket)
    {
        LOG_ERROR << "Handling packet with nullptr m_socket!" << LOG_NOOP;
        return;
    }

    // An underflow can't happen here, since at this point buflen is the maximum buffer size (in this file's context, 10k).
    // m_curMessageSize is a subset of that same buffer (or lower, if smaller size was read previously from the socket)
    uint32_t buflen = MAX_MESSAGE_LENGTH_BYTES - m_curMessageSize;
    char* offsettedBuffer = parseBuffer + m_curMessageSize;
    if (!readPacket(offsettedBuffer, buflen))
    {
        LOG_ERROR << "Failed with error to read packet" << LOG_NOOP;
        flushAllChunks();
        m_socket->Close();
        return;
    }

    if (!m_runThread)
    {
        LOG_INFO << "Handling packet - run thread was called to shutdown" << LOG_NOOP;
        return;
    }

    LOG_VERBOSE << "Incident with the size of " << buflen << " is being processed"
                << LOG_NOOP;  // TODO - Omit the log after verifying it is being printed.
    buflen += m_curMessageSize;
    parsePacket(parseBuffer, buflen);
}

bool SocketCommunicator::readPacket(char* parseBuffer, uint32_t &buflen)
{
    bool result{false};
    uint8_t i{0U};
    uint8_t delayIdx{1U};
    static constexpr uint8_t MAX_RETRIES_ON_ERROR{10U};
    
    for (; (i < MAX_RETRIES_ON_ERROR) && !result && m_runThread; ++i)
    {
        try
        {
            // using a non-blocking read
            result = m_socket->Receive(&parseBuffer, &buflen);
            if (!result && !m_socket->IsReceiveError())
            {
                static constexpr uint32_t READ_SOCKET_TIMEOUT_MS{250U};
                auto const reason = m_sleeper.SleepMilliseconds(delayIdx * READ_SOCKET_TIMEOUT_MS);
                if (common::ConditionalSleep::WakeUpReason::SIGNAL == reason)
                {
                    LOG_WARNING << "After empty receive exit from conditional sleep with signal" << LOG_NOOP;
                    return false;  // exit immediatelly on signal
                }
                if (MAX_RETRIES_ON_ERROR == (i + 1U))
                {
                    //reset counter -> wait to receive data
                    i = 0U;
                    //increase sleep delay
                    static constexpr uint8_t READ_SOCKET_MAX_DELAY_COUNT{4U};
                    if (delayIdx < READ_SOCKET_MAX_DELAY_COUNT)
                    {
                        ++delayIdx;
                    }
                }
            }
        }
        catch (std::exception const& e)
        {
            LOG_ERROR << "Parsing packet - got exception when trying to read m_socket->Receive: " << e.what()
                      << LOG_NOOP;
            return false;
        }
    }
    if ((MAX_RETRIES_ON_ERROR == i) && !result && m_socket->IsReceiveError())
    {
        LOG_WARNING << "Maximum number of retries on error exceeded" << LOG_NOOP;
    }

    return result;
}

void SocketCommunicator::parsePacket(char* parseBuffer, uint32_t buflen)
{
    static constexpr char END_OF_MSG_DELIMITER = '\n';

    for (uint32_t i = m_curMessageSize; i < buflen; ++i)
    {
        ++m_curMessageSize;
        if (END_OF_MSG_DELIMITER == parseBuffer[i])
        {
            if (m_isCorruptedMessage)
            {
                m_curMessageSize = 0U;
                m_isCorruptedMessage = false;
                continue;
            }

            std::ignore      = parseSensorData(parseBuffer + i - (m_curMessageSize - 1), m_curMessageSize);
            m_curMessageSize = 0U;
        }
    }

    if (MAX_MESSAGE_LENGTH_BYTES <= m_curMessageSize)
    {
        LOG_ERROR << "Message reached maximum message size" << LOG_NOOP;
        m_curMessageSize = 0U;
        m_isCorruptedMessage = true;
    }

    if ((0U != m_curMessageSize) && (m_curMessageSize != buflen))
    {
        static_cast<void>(memmove(parseBuffer, parseBuffer + buflen - m_curMessageSize, m_curMessageSize));
        LOG_WARNING << "The beginning of the incident was copied to the start of the buffer" << LOG_NOOP;
    }
}
