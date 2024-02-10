/**
 * @file      MebMessageCounter.h
 * @brief     Counter for MEB events
  
 */

#pragma once

#include <string>
#include <mutex>

#include <json/json.h>
#include "common/counter_manager/counters/EventBaseCounter.h"

namespace common
{
namespace counters
{
/**
 * @class   MebEventCounter
 * @brief   MEB's events counter. Inherite from EventBaseCounter class.
            Beside the EventBaseCounter functions, this class also set an event name.
 */
class MebEventCounter : public EventBaseCounter
{
public:

    using EventNameType = std::string;

    /**
     * @fn      MebEventCounter(EventNameType eventName)
     * @brief   constructor
     * @param   eventName
     * @return  none
     */
    MebEventCounter(EventNameType eventName)
    {
        m_eventName = eventName;
    }

    /**
     * @fn      MebEventCounter()
     * @brief   constructor
     * @param   none
     * @return  none
     */
    MebEventCounter()
    {
        m_eventName = "";
    }

    /**
     * @fn      bool CountEvent()
     * @brief   Count the event. Update event counter & time stamps.
     * @param   none
     * @return  bool - true if the operation succeeded, false otherwise
     */
    bool CountEvent()
    {
        std::lock_guard<std::mutex> lock(m_countMutex);

        bool res = false;

        if (IncreaseEventCounter())
        {
            UpdateTimeStamps();
            res = true;
        }
        
        return res;
    }

    /**
     * @fn      void SetEvent(EventCounterType value)
     * @brief   Set the event counter
     * @param   uint32_t value
     * @return  none
     */
    void SetEvent(EventCounterType value)
    {
        std::lock_guard<std::mutex> lock(m_countMutex);

        SetEventCounter(value);
        UpdateTimeStamps();
    }

    /**
     * @fn      EventNameType GetEventName()
     * @brief   Getter for event name
     * @param   none
     * @return  none
     */
    EventNameType GetEventName()
    {
        return m_eventName;
    }

    /**
     * @fn      void SetEventName(EventNameType eventName)
     * @brief   Setter for event name
     * @param   none
     * @return  none
     */
    void SetEventName(EventNameType eventName)
    {
        m_eventName = eventName;
    }

    /**
     * @fn      Json::Value GetCounterAsJson()
     * @brief   Get counters as JSON
     * @param   Json::Value
     * @return  none
     */
    Json::Value GetCounterAsJson()
    {
        Json::Value json;

        json["event_name"] = m_eventName;
        json["first_event_ts"] = m_firstEventTs.count();
        json["last_event_ts"] = m_lastEventTs.count();
        json["count"] = m_eventCounter;

        return json;
    }

private:

    EventNameType m_eventName;
    std::mutex m_countMutex;
};


} // namespace counters
} // namespace common

