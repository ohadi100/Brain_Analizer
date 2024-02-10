/**
 * @file
 * @brief     The Communicator is a base class for communicating with sensors, describing the common communication APIs
 */
#ifndef COMMUNICATOR_HPP
#define COMMUNICATOR_HPP

#include <memory>
#include <vector>
#include "common/notification_handler/SensorDataQueuesManager.hpp"
#include "common/utils/timer/Timer.hpp"
#include "noise_filter/sensor_noise_filter/SensorNoiseFilter.hpp"
#include "brain/engines/security_events/SecurityEventsHelper.hpp"

namespace brain
{
namespace brain_communicator
{

enum CommunicatorId : uint8_t
{
    INVALID = 0U,
    PERIODIC,
    SCI,
    DIAG_DATA,
    UDS,

    // SomeIp
    GSDP,
    HOST,
    SECURITY_EVENT,
    SECURITY_EVENT_SMALL,
    ETH,
    IMMOBILIZER,
    IP_SECURITY,
    PROXY_RELAY,
    CAN,

    COMMUNICATORS_COUNT
};

static constexpr uint64_t DEFAULT_FLUSH_INTERVAL = 60U;

/**
 * @class   Communicator
 * @brief   The Communicator is a base class for communicating with sensors, describing the common communication APIs
 */
class Communicator
{
public:
    using UPSensorData               = common::sensor_data::UPSensorData;
    using SensorDataTag              = common::sensor_data::SensorDataTag;
    using SensorDataChunk            = common::notification_handler::SDChunk;
    using SensorDataChunkPtr         = common::notification_handler::SDChunkPtr;
    using EventCounter               = common::counters::EventCounter;
    using NoiseFilterPtr             = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;
    using SDPriority                 = common::sensor_data::SDPriority;
    using DropReason                 = brain::engines::security_events::DropReason;
    using SensorDataQueuesManagerPtr = std::shared_ptr<common::notification_handler::SensorDataQueuesManager>;


    /**
     * @brief   Ctor
     * @param   SensorDataQueuesManagerPtr queuesManager
     * @param   uint32_t flushThreshold
     * @param   CommunicatorId const communicatorId
     * @param   NoiseFilterPtr sensorNoiseFilter
     */
    Communicator(SensorDataQueuesManagerPtr queuesManager,
                 uint32_t                   flushThreshold,
                 CommunicatorId const       communicatorId,
                 NoiseFilterPtr             sensorNoiseFilter = nullptr);

    Communicator() = default;

    /**
     * @brief   Dtor
     */
    virtual ~Communicator();

    /**
     * @brief    default copy constructor
     */
    Communicator(const Communicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    Communicator(Communicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    Communicator& operator=(Communicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    Communicator& operator=(Communicator&&) = delete;

    /**
     * @brief   Start communication with the sensor
     */
    virtual void Start() = 0;

    /**
     * @brief   Stop communication with the sensor
     */
    virtual void Stop() = 0;

    /**
     * @brief   Allow the incoming sensor data or block it.
     * @param   UPSensorData sd - the incoming sensor data.
     * @param   size_t const eventSize - Size of event to filter
     * @param   bool hasData - does contain data after filtering.
     * @return  The sd if it should be enqueued, nullptr otherwise
     */
    virtual UPSensorData FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData);

    /**
     * @brief   Sets periodic flush
     * @param   uint64_t const flushInterval - new flush interval
    */
    void SetPeriodicFlush(uint64_t const flushInterval);

    /**
     * @brief   Returns the Communicator's ID
     * @param   none.
     * @return  CommunicatorId
     */
    inline CommunicatorId GetId() const noexcept
    {
        return m_communicatorId;
    }

    /**
     * @brief   Poll ready samples
     */
    virtual void HandleNewSamples()
    {
        // SD Polling support
    }

    UPSensorData GetDroppedSensorData()
    {
        return std::move(m_droppedSensorData);
    }

    void SetIgnoreErrors(bool value)
    {
        m_ignoreErrors = value;
    }

#ifdef TESTS
#else
protected:
#endif

    // ToDo - remove feature specific code from base class 
    #if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION) && !defined(MEB_PLATFORM))
    virtual void handleQueueAddFailed(UPSensorData sd, DropReason dropReason);
    #endif

    /**
     * @brief   Insert an sd into the appropriate chunk.
     * @param   UPSensorData& sd
     * @param   bool const preventFlush - optional, defaults with false
     */
    void handle(UPSensorData sd, size_t const eventSize, bool const preventFlush = false);

    /**
     * @brief   Flush a specific chunk by tag.
     * @param   SensorDataChunkPtr sensorChunk
     * @param   SDPriority const priority
     */
    void flushChunk(SensorDataChunkPtr sensorChunk, SDPriority const priority);
    
    /**
     * @brief   Flush all chunks if required
     * @param   bool const forceFlush - optional, defaults to true
     */
    void flushAllChunks(bool const forceFlush = true);

    static constexpr uint32_t MAX_CHUNCKQ_SIZE = 10000U; // define max size on chuckQ for not allocating unlimited memory

    SensorDataQueuesManagerPtr m_queuesManager;
    uint32_t const m_flushTimedThreshold{0U};
    NoiseFilterPtr m_sensorNoiseFilter;
    std::array<SensorDataChunkPtr, common::sensor_data::PRIORITY_COUNT> m_sdChunks;
    uint32_t m_totalSDsInAllChunks{0U};

    std::shared_ptr<EventCounter> m_sdFilteredCounter;
    std::shared_ptr<EventCounter> m_sdNotFilteredCounter;

    CommunicatorId m_communicatorId{INVALID};
    uint64_t m_lastCreatedEventTS{0ULL};
    UPSensorData m_droppedSensorData;
    std::atomic<bool> m_ignoreErrors{false};
};

} // namespace brain_communicator
} // namespace brain


#endif /* COMMUNICATOR_HPP */
