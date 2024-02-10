/**
 * @file      MebCounterManager.h
 * @brief     Debug counter manager for MEB events
  
 */

#pragma once

#include <atomic>  

#include "common/counter_manager/CounterMapTemplate.h"
#include "common/counter_manager/BaseCounterManager.h"
#include "common/counter_manager/counters/MebEventCounter.h"

#include <json/json.h>

namespace common
{

namespace counters
{

/**
 * @class     MebCounterManager
 * @brief     Manage all MEB event counters. This class inheritance BaseCounterManager.
              Beside implementing the BaseCounterManager abstarct functions, this class
              can return a counter for a specific event. It also can clear all the event counters.
 */
class MebCounterManager : public BaseCounterManager
{
public:

    /**
     * @fn      MebCounterManager()
     * @brief   constructor
     * @param   none
     * @return  none
     */
    MebCounterManager();

    /**
     * @fn      CountNotification
     * @brief   Count MEB event
     * @param   eventName
     * @return  None
     */
    void CountNotification(std::string const & eventName);

    /**
     * @fn      GetCounter
     * @brief   Get MEB event counter, creates one if not exists
     * @param   eventName
     * @return  shared_ptr of the counter object
     */
    std::shared_ptr<MebEventCounter> GetCounter(std::string const & eventName);

    /**
     * @fn      GetCountersAsJson
     * @brief   Generate JSON of the counters values
     * @param   void
     * @return  Json::Value
     */
    Json::Value GetCountersAsJson();

    /**
     * @fn      GetCountersAsJsonString
     * @brief   Get counters JSON as string
     * @param   void
     * @return  std::string
     */
    std::string GetCountersAsJsonString();

    /**
     * @fn      ClearAll
     * @brief   Drop all counters
     * @param   void
     * @return  void
     */
    void ClearAll();

    /**
     * @fn      MarkForReset
     * @brief   Mark counters table for reset.
     *          This method is used for thread safety.
     *          Thread A can mark the table for reset, while Thread B will actually reset it.
     *          This allows thread A to keep only reading the counters, while thread B will write to it.
     * @param   void
     * @return  void
     */
    void MarkForReset() noexcept;

    /**
     * @fn      MarkForReset
     * @brief   Is counters table for reset
     * @param   void
     * @return  std::atomic<bool>
     */
    bool IsMarkedForReset() noexcept;

    /**
     * @fn      std::string GetSerializedCounters() override
     * @brief   Implements serialize interface for counter logging
     * @param   none
     * @return  std::string - serilized counters
     */
    std::string GetSerializedCounters() override;
    
    /**
     * @fn      Json::Value GetCountersJson() override
     * @brief   Implements json interface for counter logging
     * @param   none
     * @return  Json::Value - Json with the counters
     */
    Json::Value GetCountersJson() override;

private:

    /**
    * @var: CounterMapTemplate<MebEventCounter> m_counterManager
    * @brief Manager of counters values
    */
    CounterMapTemplate<MebEventCounter> m_counterManager;

    /**
     * @var: std::atomic<bool> mIsMarkedForReset
     * @brief Manager of counters values
     */
    std::atomic<bool> mIsMarkedForReset;
};

} //namespace counters

} //namespace common