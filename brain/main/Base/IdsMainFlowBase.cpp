#include "IdsMainFlowBase.hpp"
#include "AliveSupervision.hpp"
#include "Configuration.hpp"
#include "CounterManager.hpp"
#include "Creditor.hpp"
#include "DBNames.hpp"
#include "EngineDispatcher.hpp"  // Each platform with it's own absolute path
#include "EventsStorage.hpp"  // Needed for MessageRepositoryPriorityQueue compilation, currently EventsStorage pointer input is nullptr (default)
#include "ExceededMessageSizeCheck.hpp"
#include "Logger.hpp"
#include "MessageRepositoryPriorityQueue.hpp"
#include "PeriodicReportCommunicator.hpp"
#include "Reactor.hpp"
#include "SafeCall.hpp"
#include "SenderManager.hpp"
#include "SensorDataQueuesManager.hpp"
#include "SupervisionAdapter.hpp"
#include "Timer.hpp"
#include "signal_handlers.hpp"

namespace brain
{
namespace main_flow
{

using ReactorConfig = std::vector<std::pair<uint32_t, uint32_t>>;
static ReactorConfig const&
getReactorConfig() noexcept
{
    static ReactorConfig reactorSizeWeight{{10U, 1U}};
    return reactorSizeWeight;
}

/*
    API Methods
*/

IdsMainFlowBase::IdsMainFlowBase()
  : m_timer(std::make_shared<common::Timer>())
  , m_threadHandler(common::thread_handler::ThreadHandler::GetInstance())
  , m_debugCounters(std::make_shared<common::counters::CounterManager>())
  , m_senderReactor(std::make_shared<common::thread_handler::Reactor>(getReactorConfig()))
  , m_activeIds(true)
{
}

/*
    Protected Methods
*/

void
IdsMainFlowBase::buildDomainObjects(const std::string&                                         idsNameInDomain,
                                    uint32_t                                                   idsIdInDoamin,
                                    const ConfigFilePaths&                                     configFilePaths,
                                    brain::power_state::PowerStateAdapter::SwitchStateCallBack onPowerStateSwitch)
{
    m_supervisionAdapter = std::make_unique<brain::supervision::SupervisionAdapter>(idsNameInDomain, idsIdInDoamin);
    m_powerStateAdapter  = std::make_unique<brain::power_state::PowerStateAdapter>(onPowerStateSwitch, idsNameInDomain);

    // Persisntence
    common::memory::PersistentMemoryManagerBuilder persistanceBuilder{
        std::make_shared<common::memory::PersistentMemoryWatchdog>(), m_debugCounters};
    m_pmFactory = std::make_shared<common::memory::PersistentMemoryFactory>(false, persistanceBuilder);

    // Ideally Configuration would be built in Initialization list, but it has dependency with PM (not ideal) and it
    // should be assigned here
    m_configuration = common::configuration::Configuration::CreateConfig(
        configFilePaths, m_pmFactory, common::memory::PER_MEM_IDS_BRAIN_CONFIGURATION_DATA, false);
}

std::shared_ptr<messageRepository::MessageRepositoryInterface>
IdsMainFlowBase::buildSendChain(std::unique_ptr<PublisherInterface>         publisher,
                                const IdsMainFlowBase::MessageQueuesConfig& msgQueuesConfig)
{
    auto msgRepository = std::make_shared<messageRepository::MessageRepositoryPriorityQueue>(m_debugCounters);
    m_sender      = std::make_shared<sender_manager::SenderManager>(
        m_pmFactory,
        m_debugCounters,
        m_configuration,
        m_senderReactor,
        msgRepository,
        std::move(std::make_unique<sender::Creditor>(m_pmFactory, m_debugCounters, m_configuration)),
        std::move(publisher),
        std::make_shared<publishers::utils::ExceededMessageSizeCheck>(m_configuration));
    msgRepository->Init(msgQueuesConfig);  // In m_msgRepository class' Init is extending the Ctor
    return msgRepository;
}

std::shared_ptr<common::notification_handler::SensorDataQueuesManager>
IdsMainFlowBase::buildEngineChain(std::shared_ptr<messageRepository::MessageRepositoryInterface> msgRepository)
{
    auto queuesManager
        = std::make_shared<common::notification_handler::SensorDataQueuesManager>(m_configuration, m_debugCounters);
    m_dispatcher = std::make_shared<engines::EngineDispatcher>(msgRepository, queuesManager, m_configuration);
    return queuesManager;
}

void
IdsMainFlowBase::buildCommunicatorChain(std::shared_ptr<common::notification_handler::SensorDataQueuesManager> sdQueues)
{
    (void)sdQueues;
    // ToDo - Build CommunicatorManager
}

void
IdsMainFlowBase::startMainFlow()
{
    m_sender->Enable();
    engines::EngineDispatcher::CreateRulesEngineThread(m_dispatcher);
}

void
IdsMainFlowBase::initDomainConnection()
{
    m_configuration->Init();
    m_supervisionAdapter->RegisterSupervision();

    common::alive_supervision::AliveSupervision::GetInstance()->Start(
        [this] {
            m_supervisionAdapter->ReportToSuperviser();
        },
        std::chrono::milliseconds(IdsMainFlowBase::SUPERVISION_REPORT_CYCLE));

    m_powerStateAdapter->Register();
}

void
IdsMainFlowBase::destroyDomainConnection()
{
    common::alive_supervision::AliveSupervision::GetInstance()->Stop();
}

bool
IdsMainFlowBase::shouldStop()
{
    return common::should_stop() || m_threadHandler->ShouldStop();
}

bool
IdsMainFlowBase::mainLoop()
{
    m_timer->ProcessTimerEntries();
    bool returnByEvent = m_threadHandler->TryWait(std::chrono::milliseconds(LOOP_WAIT_TIME_MS));
    LOG_DEBUG << "Brain main loop triggered by " << (returnByEvent ? "EVENT" : "TIMEOUT TIMER") << LOG_NOOP;
    return returnByEvent;
}

void
IdsMainFlowBase::runSuspended()
{
    m_threadHandler->TryWait(std::chrono::milliseconds(LOOP_WAIT_INACTIVE_TIME_MS));
}

void
IdsMainFlowBase::suspendIds()
{
    m_activeIds = false;
    m_sender->Disable();
}

void
IdsMainFlowBase::resumeIds()
{
    m_activeIds = true;
    m_sender->Enable();
}

}  // namespace main_flow
}  // namespace brain
