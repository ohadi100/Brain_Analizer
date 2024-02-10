/**
 * @file      CounterLogger.hpp
 * @brief     In charge of outputting all counters to the DLT
  
 */

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <thread>
#include <atomic>

#include "common/counter_manager/BaseCounterManager.h"
#include "common/framework/ConditionalSleep.hpp"

namespace common
{

namespace counters
{

/**
 * @class     CounterLogger
 * @brief     Print all the event counters.
              This function run a thread in an infinity loop (with a flag), that every 30 seconds get
              the counter value from the counterManagers and print it.
              The class can terminate the thread any time by calling the Disable() function.
 */
class CounterLogger 
{
public:

    /**
     * @fn      CounterLogger(std::vector<std::shared_ptr<BaseCounterManager>> counterManagers)
     * @brief   constructor
     * @param   std::vector<std::share_ptr<BaseCounterManager>> counterManagers - Counter managers who's
     *              counters the class logs
     * @return  none
     */
    CounterLogger(std::vector<std::shared_ptr<BaseCounterManager>> counterManagers);

    /**
     * @fn      ~CounterLogger()
     * @brief   destructor
     * @param   none
     * @return  none
     */
    ~CounterLogger();

    /**
     * @fn      bool RunThread()
     * @brief   Runs the CounterLogger
     * @param   none
     * @return  bool - success
     */
    bool RunThread();

    /**
     * @fn      void Disable()
     * @brief   Disables the CounterLogger
     * @param   none
     * @return  none
     */
    void Disable();

#ifdef TESTS
    /**
     * @fn      bool IsThreadRunning() const noexcept
     * @brief   check if m_thread is running
     * @param   none
     * @return  bool - true if running, false otherwise.
     */
    bool IsThreadRunning() const noexcept;
#endif

    /**
     * @fn      std::vector<std::vector<std::string>> LogManagers()
     * @brief   Output the managers' counters
     * @param   none
     * @return  std::vector<std::vector<std::string>> - all counter logs per manager
     */
    std::vector<std::vector<std::string>> LogManagers();

private:

    void LogCounters();

    std::vector<std::shared_ptr<BaseCounterManager>> m_counterManagers;

    std::unique_ptr<std::thread> m_thread;
    
    std::atomic<bool> m_runThread;

    common::ConditionalSleep m_sleeper;
};

} // namespace counters

} // namespace common