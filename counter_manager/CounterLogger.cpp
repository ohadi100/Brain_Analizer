/**
 * @file      CounterLogger.cpp
 * @brief     In charge of outputting all counters to the DLT
  
 */

#include <thread>
#include <memory>
#include <sstream>
#include <json/json.h>

#include "Logger.hpp"
#include "common/counter_manager/CounterLogger.hpp"
#include "common/counter_manager/BaseCounterManager.h"

using common::counters::CounterLogger;
using common::counters::BaseCounterManager;

constexpr size_t COUNTER_LOGGER_INTERVAL = 30U;

CounterLogger::CounterLogger(std::vector<std::shared_ptr<BaseCounterManager>> counterManagers) :
    m_counterManagers(counterManagers)
    ,m_thread(nullptr)
    ,m_runThread(false)
{
}

CounterLogger::~CounterLogger()
{
    
}

bool CounterLogger::RunThread()
{
    m_runThread.store(true);
    m_thread = std::make_unique<std::thread>([this]()
                                              {
                                                LogCounters();
                                              });
    return m_thread ? true : false;
}

void CounterLogger::Disable()
{
    m_runThread.store(false);
    m_sleeper.WakeUp();

    if (m_thread && m_thread->joinable())
    {
        m_thread->join();
        m_thread = nullptr;
    }
}

void CounterLogger::LogCounters()
{
    while (m_runThread)
    {
        static_cast<void>(LogManagers());

        static_cast<void>(m_sleeper.SleepWithTimeoutSec(COUNTER_LOGGER_INTERVAL));
    }
}

std::vector<std::vector<std::string>> CounterLogger::LogManagers()
{
    std::vector<std::vector<std::string>> logs;

    for (auto & counterManager : m_counterManagers)
    {
        std::vector<std::string> managerLogs;
        auto json = counterManager->GetCountersJson();

        Json::StreamWriterBuilder builder;
        for( Json::Value::const_iterator itr = json.begin() ; itr != json.end() ; itr++ )
        {
            auto jsonString = Json::writeString(builder, *itr);
            if (itr.key().isString())
            {
                LOG(CommonLogerLevel::kInfo) << "COUNTER_ENTRY: " << itr.key() << ": " << jsonString;
#ifdef TESTS
                std::stringstream stream;
                stream << "COUNTER_ENTRY: " << itr.key().asString() << ": " << jsonString.c_str();
                managerLogs.push_back(stream.str());
#endif //TESTS
            }
            else
            {
                LOG(CommonLogerLevel::kWarning) << "Counter entry key is not string!";
            }
        }

        logs.push_back(managerLogs);
    }

    return logs;
}

#ifdef TESTS
bool CounterLogger::IsThreadRunning() const noexcept
{
    return m_runThread;
}
#endif