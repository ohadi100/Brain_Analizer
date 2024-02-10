/**
 * @file
 * @brief     Generic socket communicator
 */
#ifndef SOCKET_COMMUNICATOR_HPP
#define SOCKET_COMMUNICATOR_HPP

#include <atomic>
#include "brain/communicator/Communicator.hpp"
#include "brain/utils/UtilsConstants.hpp"
#include "common/utils/socket/BaseSocket.hpp"
#include "common/utils/conditionalSleep/ConditionalSleep.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/thread_handler/ThreadHandler.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"

namespace brain
{
namespace brain_communicator
{

static constexpr uint32_t MAX_MESSAGE_LENGTH_BYTES{10240U}; // 10 * 1024 (10 Kilo)

/**
 * @class   SocketCommunicator
 * @brief   SocketCommunicator
 */
class SocketCommunicator : public Communicator
{
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using EventCounter = common::counters::EventCounter;
    using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
    using DiagnosticsManagerPtr = brain::diagnostics::DiagnosticsManagerInterface::Pointer;

public:
    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr queuesManager
     * @param   CounterManagerPtr debugCounters,
     * @param   uint32_t const& flushThreshold
     * @param   DiagnosticsManagerPtr diagnosticsManager,
     * @param   CommunicatorId const communicatorId,
     * @param   NoiseFilterPtr sensorNoiseFilter=nullptr
     */
    SocketCommunicator(SensorDataQueuesManagerPtr queuesManager,
                       CounterManagerPtr          debugCounters,
                       uint32_t                   flushThreshold,
                       DiagnosticsManagerPtr      diagnosticsManager,
                       CommunicatorId const       communicatorId,
                       NoiseFilterPtr             sensorNoiseFilter = nullptr);

    /**
     * @brief   Ctor
     */
    SocketCommunicator() = default;

    /**
     * @brief    default copy constructor
     */
    SocketCommunicator(const SocketCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    SocketCommunicator(SocketCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    SocketCommunicator& operator=(SocketCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    SocketCommunicator& operator=(SocketCommunicator&&) = delete;

    /**
     * @brief   Dtor
     */
    virtual ~SocketCommunicator();

    /**
     * @brief   Start communication with the sensor
     */
    void Start() override;

    /**
     * @brief   Stop communication with the sensor
     */
    void Stop() override;

    /**
     * @brief   Parses the sensor data and chunks it
     * @param   char const* incidents
     * @param   uint32_t buflen
     * @return  true / false - indicates whether SDs were found in the buffer.
     */
    virtual bool parseSensorData(char const* incidents, size_t const length) = 0;

#ifndef TESTS
protected:
#endif
    /**
     * @brief   Main thread for socket management
     *
     * @return  EThreadStatus::eSuccess if successful, EThreadStatus::eFatalError otherwise
     */
    common::thread_handler::EThreadStatus handleSocket();

    /**
     * @brief   handlePacket from UnixSocket, reads and parses a packet. Does not validate parseBuffer.
	 * @param   char[] parseBuffer
     * @return  void
     */
	void handlePacket(char* parseBuffer);

    /**
     * @brief   Read a packet from UnixSocket
     * @param   char[] parseBuffer
     * @param   uint32_t buflen
     * @return  true if successful
     */
    bool readPacket(char* parseBuffer, uint32_t &buflen);

    /**
     * @brief   Handle a packet read from UnixSocket
     * @param   char[] parseBuffer
     * @param   uint32_t buflen
     * @return  void
     */
    void parsePacket(char* parseBuffer, uint32_t buflen);

    std::atomic<bool> m_runThread;
    uint32_t m_curMessageSize = 0U;
    bool m_isCorruptedMessage = false;
    CounterManagerPtr m_debugCounters;
    std::shared_ptr<EventCounter> m_failConnectSocket;
    std::unique_ptr<common::ids_socket::IBaseSocket> m_socket;
    common::ConditionalSleep m_sleeper;
    std::unique_ptr<std::thread> m_thread;
    DiagnosticsManagerPtr m_diagnosticsManager;
    
};

} // namespace brain_communicator
} // namespace brain

#endif
