/**
 * @file
 * @brief    This file contains the definition of SciCommunicator.
 */
#ifndef SCICOMMUNICATOR_HPP
#define SCICOMMUNICATOR_HPP

#include <map>
#include <memory>

#include "SciSignalGroupHandler.hpp"
#include "brain/communicator/Communicator.hpp"
#include <sci/frontend/api/ClientFactory.hpp>

namespace brain
{
namespace brain_communicator
{
namespace sci_communicator
{

using namespace vwg::e3p::com::sci;
using SciRXSignalGroups     = std::map<std::string, std::vector<std::string>>;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;


enum SignalIndexes : uint8_t
{
    kTimestamp = 0U,
    kEventFrame,
    kContextData1,
    kContextData2,
    kContextData3,
    kContextData4,
    kContextData5,
    kContextData6,
    // kSignatur // Not yet supported in E³
};

class SciCommunicator : public Communicator
{

public:
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using ConfigurationPtr  = common::configuration::Pointer;
    using NoiseFilterPtr    = std::shared_ptr<brain::brain_noise_filter::SensorNoiseFilter>;
    using SciRxSignalGroups = std::map<std::string, std::vector<std::string>>;

    /**
     *                          const& flushThreshold, NoiseFilterPtr sensorNoiseFilter=nullptr);
     * @brief   Ctor. Creates the signal handler, and initializes ara log with a mock logger required for scilib
     * internal usage.
     * @param   SensorDataQueuesManagerPtr  queuesManager - queue that manages all sensors, input for Communicator ctor
     * @param   CounterManagerPtr debugCounters - link to debug counters that are used in IDS, input for Communicator
     * ctor
     * @param   uint32_t flushThreshold - input for Communicator ctor
     * @param   NoiseFilterPtr sensorNoiseFilter - noise filter link
     */
    SciCommunicator(SensorDataQueuesManagerPtr queuesManager,
                    CounterManagerPtr          debugCounters,
                    uint32_t                   flushThreshold,
                    NoiseFilterPtr             sensorNoiseFilter = nullptr);

    /**
     * @brief   Dtor. Deregisters signal handlers.
     */
    ~SciCommunicator() override;

    /**
     * @brief    default copy constructor
     */
    SciCommunicator(const SciCommunicator& other) = delete;

    /**
     * @brief    default move constructor
     */
    SciCommunicator(SciCommunicator&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    SciCommunicator& operator=(SciCommunicator const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    SciCommunicator& operator=(SciCommunicator&&) = delete;

    /**
     * @brief   Starts the signal handling logic, which parses the configuration and registers m_signalHanlder to handle
     * each signal.
     */
    virtual void Start() override;

    /**
     * @brief   Deregisters the signal handling and resets the parsed signals objects.
     */
    virtual void Stop() override;

#ifndef TESTS
private:
#endif  // TESTS
    virtual UPSensorData FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData) override;

    /**
     * @brief   Registering the signal handler for each signal.
     * @return  true / false upon success / failure of registering each signal
     */
    bool registerSignalHandling();

    /**
     * @brief   Initializes sci signal client.
     * @return  true / false upon success / failure
     */
    bool initSignalClient();

    /**
     * @brief   Create libsci's Signal object and registers the signal handler.
     * @param   std::string const& signalName
     * @param   uint32_t syncRateMs
     * @return  std::shared_ptr<sci::ReceivedSignal> - created ReceivedSignal upon success, nullptr in case of failure
     */
    std::shared_ptr<sci::ReceivedSignal> registerRxSignal(std::string const& signalName, uint32_t syncRateMs);

    /**
     * @brief   Create libsci's Signal object for each signal in the group and registers a signal handler.
     * @param   std::string const& pduName
     * @param   std::vector<std::string> const& signals
     * @return  true / false upon success / failure
     */
    bool registerRxSignalGroup(std::string const& pduName, std::vector<std::string> const& signals);

    std::unique_ptr<api::Client> m_signalClient;
    std::map<std::shared_ptr<SciSignalGroupHandler>, std::unique_ptr<sci::ReceivedSignalGroup>> m_signalHandlers;
    std::vector<uint64_t> m_groupSignalValues;

    // counters
    CounterManagerPtr m_debugCounters;
    std::shared_ptr<EventCounter> m_receivedSciSignal;

protected:
    static const SciRxSignalGroups m_sciRxSignalGroups; 
};

} /* namespace sci_communicator */
} /* namespace brain_communicator */
} /* namespace brain */

#endif /* SCICOMMUNICATOR_HPP */
