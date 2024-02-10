#pragma once

/**
 * @file IdsMainFlowBase.hpp
 * @brief Common functionality per projects for running and managing the IDS
 *
 */

#include <memory>
#include <string>
#include <utility>  // std::pair
#include <vector>

// Cannot forward declare inner types of classes, therefore including
#include "Configuration.hpp"
#include "MessageRepository.hpp"
#include "PowerStateAdapter.hpp"
#include "PublisherInterface.hpp"

namespace common
{

class Timer;

namespace shutdown_and_enabler
{
class IDSEnabler;
}

namespace notification_handler
{
class SensorDataQueuesManager;
}  // namespace notification_handler

namespace counters
{
class CounterManager;
}

namespace memory
{
class PersistentMemoryFactory;
class PersistentMemoryWatchdog;
}  // namespace memory

namespace thread_handler
{
class ThreadHandler;
class Reactor;
}  // namespace thread_handler
}  // namespace common

namespace brain
{

namespace supervision
{
class SupervisionAdapter;
}

namespace engines
{
class EngineDispatcher;
}

namespace sender_manager
{
class SenderManager;
}  // namespace sender_manager

namespace main_flow
{


class IdsMainFlowBase
{
public:
    // Public for both this class and its derived types
    using ConfigFilePaths = common::configuration::Configuration::PathsList;
    using MessageQueuesConfig
        = std::vector<brain::messageRepository::MessageRepositoryInterface::MessageRepositoryParameters>;

    static constexpr uint32_t LOOP_WAIT_TIME_MS{500U};
    static constexpr uint32_t LOOP_WAIT_INACTIVE_TIME_MS{5000U};
    static constexpr uint32_t SUPERVISION_REPORT_CYCLE{5000U};

    /**
     * @brief Class Constructor
     */
    IdsMainFlowBase();

    /**
     * @brief Class Destructor
     */
    virtual ~IdsMainFlowBase() = default;

    /**
     * @brief Init method is used for IDS initialization, mostly opening connections to the domain and opening threads.
     */
    inline void
    Init()
    {
        initDomainConnection();
        startMainFlow();
    }

    /**
     * @brief Run main control loop. Might be overriten per project needs.
     * @return IDS return code (unused, open for future extention).
     */
    inline void
    Run()
    {
        while (!shouldStop())
        {
            if (m_activeIds)
            {
                std::ignore = mainLoop();
            }
            else
            {
                runSuspended();
            }
        }
    }

    /**
     * @brief Method used for closing connection to the domain and closing threads.
     */
    inline void
    Destroy()
    {
        destroyDomainConnection();
    }

protected:
    /**
     * @brief This is where all domain related utilites get initalized - must be called first thing in Ctor of the
     * project
     *
     * @param idsNameIdDomain     Ids name identifier in the domain
     * @param idsIdInDoamin       Ids number identifier in the domain
     * @param configFilePath      Paths to find IDS configuration files
     * @param switchPowerStateCb  The procedure of the IDS at switching states
     */
    void buildDomainObjects(const std::string&                                         idsNameInDomain,
                            uint32_t                                                   idsIdInDoamin,
                            const ConfigFilePaths&                                     configFilePath,
                            brain::power_state::PowerStateAdapter::SwitchStateCallBack switchPowerStateCb);

    /**
     * Chaining of build functions, building from the end of the chain to the start
     * Methods API made to ensure right sequence of activation (as theit call must repeat per project)
     * With the Queues as input and output of the functions:
     *
     * buildSendChain -output-> MessageRepositoryInterface
     * MessageRepositoryInterface -input-> buildEngineChain -output-> SensorDataQueuesManager
     * SensorDataQueuesManager -input-> buildCommunicatorChain
     *
     **/

    /**
     * @brief Build the Sender chain - first part of the Flow Chain that needs to be built
     *
     * @param publisher Revelant publisher for the domain
     * @param msgQueuesConfig Layout of the Message Queues before the sender
     */
    virtual std::shared_ptr<messageRepository::MessageRepositoryInterface> buildSendChain(
        std::unique_ptr<PublisherInterface> publisher,
        const MessageQueuesConfig&          msgQueuesConfig = {{5U, 400U}, {1U, 200U}, {1U, 80U}, {1U, 40U}});

    virtual std::shared_ptr<common::notification_handler::SensorDataQueuesManager> buildEngineChain(
        std::shared_ptr<messageRepository::MessageRepositoryInterface> msgRepository);

    virtual void buildCommunicatorChain(
        std::shared_ptr<common::notification_handler::SensorDataQueuesManager> sdQueues);

    /**
     * @brief Initialize connection to the domain. Implementation might by overriten per platform type.
     */
    virtual void initDomainConnection();

    /**
     * @brief Finish the connection to the domain. Implementation might by overriten per platform type.
     */
    virtual void destroyDomainConnection();

    /**
     * @brief Initialize the threads in the system. Implementation might by overriten per platform type.
     */
    virtual void startMainFlow();

    /**
     * @brief Should IDS run stop
     */
    virtual bool shouldStop();

    /**
     * @brief Main loop activation
     */
    virtual bool mainLoop();

    /**
     * @brief Run in suspended mode
     */
    virtual void runSuspended();

    /**
     * @brief Suspend IDS run temporarily.
     */
    virtual void suspendIds();

    /**
     * @brief Resume IDS run of the suspend stage.
     */
    virtual void resumeIds();

    // Common build objects
    std::shared_ptr<common::Timer>                            m_timer;
    std::shared_ptr<common::thread_handler::ThreadHandler>    m_threadHandler;
    std::shared_ptr<common::counters::CounterManager>         m_debugCounters;
    std::shared_ptr<common::thread_handler::Reactor>          m_senderReactor;
    bool                                                      m_activeIds;

    // Adapters
    std::shared_ptr<supervision::SupervisionAdapter>         m_supervisionAdapter;
    std::shared_ptr<power_state::PowerStateAdapter>          m_powerStateAdapter;
    std::shared_ptr<common::memory::PersistentMemoryFactory> m_pmFactory;
    std::shared_ptr<common::configuration::Configuration>    m_configuration;

    // Main flow
    std::shared_ptr<sender_manager::SenderManager> m_sender;
    std::shared_ptr<engines::EngineDispatcher>     m_dispatcher;
};

}  // namespace main_flow
}  // namespace brain
