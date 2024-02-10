/**
 * @file
 * @brief     code for the generic EngineDispatcherBase
 */
#include "EngineDispatcherBase.hpp"
#include "common/thread_handler/ThreadHandler.hpp"
#include "common/thread_handler/ThreadNamesConstants.hpp"

#if defined(tests) || defined(SIMULATION)
#include "brain/engines/NullEngine.hpp"
#endif //defined(tests) || defined(SIMULATION)

using brain::engines::EngineDispatcherBase;
using brain::events::EventPriority;
using common::thread_handler::EThreadStatus;
using common::thread_handler::ThreadHandler;

bool
EngineDispatcherBase::HandleData(bool const stopAfterSingleFail)
{
    auto chunk = m_queuesManager->Dequeue();
    if (chunk->empty())
    {
        LOG_WARNING << "Engine Dispatcher - Tried to handle data with no data to dequeue!" << LOG_NOOP;
        return false;
    }

    for (auto& sd : *chunk)
    {
        LOG_VERBOSE << "Dequeued sd with tag=" << static_cast<uint32_t>(sd->GetTag()) << LOG_NOOP;

        bool const success = handleSD(std::move(sd));
        // Used mainly for tests
        if (stopAfterSingleFail && !success)
        {
            if (stopAfterSingleFail)
            {
                return false;
            }
        }
    }
    return true;
}

bool
EngineDispatcherBase::handleSD(UPSensorData sd)
{
    uint32_t const tag = static_cast<uint32_t>(sd->GetTag());
    if (static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS) <= tag)
    {
        LOG_ERROR << "SD With bad tag encountered! SD tag is " << tag << LOG_NOOP;
        return false;
    }

    LOG_DEBUG << "Sensor Data with tag = " << tag
              << ", arrived into the EngineDispatcherBase and will be processed by the relevant engine" << LOG_NOOP;

    if (ReturnCode::Success != (m_engines[tag]->Process(std::move(sd))))
    {
        LOG_WARNING << "SD processing failed for sd with tag=" << tag << LOG_NOOP;
        common::counters::IncreaseCounter(m_failedProcessSDCounter);
        return false;
    }

    return true;
}

void
EngineDispatcherBase::loadEventPriorities(ConfigurationPtr config)
{
    for (auto const& eventIdConfigPair : m_eventPriorityConfigKeys)
    {
        uint32_t priority{};
        if (config->GetValue(eventIdConfigPair.second, priority))
        {
            m_priorityMap[eventIdConfigPair.first] = static_cast<EventPriority>(priority);
        }
    }
}

void
EngineDispatcherBase::StartDispatcher()
{
    LOG_INFO << "RulesEngine: StartDispatcher" << LOG_NOOP;

    auto const dataArrivedEvent = m_queuesManager->GetDataArrivedEvent();

    if (!dataArrivedEvent)
    {
        LOG_ERROR << "StartDispatcher: dataArrivedEvent is nullptr" << LOG_NOOP;
        return;
    }

    auto const waitPredicate = [this]() {
        return (m_queuesManager->CountAllQueuesContent() > 0);
    };

    m_runningFlag.store(true);

    while(m_runningFlag.load())
    {
        static constexpr int32_t DATA_ARRIVED_EVENT_TIMEOUT = 1000;
        dataArrivedEvent->WaitWithTimeout(std::chrono::milliseconds(DATA_ARRIVED_EVENT_TIMEOUT), waitPredicate);

        if (this->HandleData())
        {
            LOG_DEBUG << "RulesEngine: data arrived and dispatched" << LOG_NOOP;
            common::counters::IncreaseCounter(m_counterArrivedEventWithSignal);
        }
    }
    LOG_DEBUG << "RulesEngine: stop run" << LOG_NOOP;
}

void
EngineDispatcherBase::StopDispatcher()
{
    m_runningFlag.store(false);

    auto const dataArrivedEvent = m_queuesManager->GetDataArrivedEvent();
    if (dataArrivedEvent)
    {
        dataArrivedEvent->Notify();
    }
    else
    {
        LOG_ERROR << "StopDispatcher: dataArrivedEvent is nullptr" << LOG_NOOP;
    }
}

void
EngineDispatcherBase::CreateRulesEngineThread(EngineDispatcherBasePtr engineDispatcherBasePtr)
{
    auto startRulesEngineFunc = [engineDispatcherBasePtr]() -> EThreadStatus {
        engineDispatcherBasePtr->StartDispatcher();
        return EThreadStatus::eSuccess;
    };

    auto stopRulesEngineFunc = [engineDispatcherBasePtr]() -> EThreadStatus {
        engineDispatcherBasePtr->StopDispatcher();
        return EThreadStatus::eSuccess;
    };

    ThreadHandler::GetInstance()->StartThread(
        startRulesEngineFunc, stopRulesEngineFunc, std::string(threads_names::ids::RULES_ENGINE));
}
