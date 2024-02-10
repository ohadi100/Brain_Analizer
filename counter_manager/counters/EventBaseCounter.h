/**
 * @file      EventBaseCounter.h
 * @brief     Base class for event counter
  
 */

#pragma once

#include <chrono>
#include <string>

#include "Logger.hpp"

namespace common
{
namespace counters
{
/**
 * @class   EventBaseCounter
 * @brief   Event counter, holds counter and timestamps.
            This object can increase the eventCounter, can set the eventCounter and update the last attack
            and the first event.
 */
class EventBaseCounter
{
public:
    using EventCounterType = uint64_t;
    using UnixTimeStampType = std::chrono::milliseconds;

    /**
    * @fn      EventBaseCounter()
    * @brief   constructor
    * @param   None
    * @return  None
    */
    EventBaseCounter()
    {
        m_eventCounter = 0;
        m_firstEventTs = UnixTimeStampType(0);
        m_lastEventTs = UnixTimeStampType(0);
    }

    /**
    * @fn      EventCounterType GetEventCounter()
    * @brief   Get counter value
    * @param   None
    * @return  EventCounterType
    */
    EventCounterType GetEventCounter()
    {
        return m_eventCounter;
    }

    /**
    * @fn      bool IncreaseEventCounter()
    * @brief   Increase counter value
    * @param   None
    * @return  bool - true if the operation succeeded, false otherwise
    */
    bool IncreaseEventCounter()
    {
        bool res = false;

        if (m_eventCounter < UINT64_MAX)
        {
            m_eventCounter++;
            res = true;
        }
        else
        {
            LOG(CommonLogerLevel::kError) << "counter reached its maximum value";
        }

        return res;
    }

    /**
    * @fn      void SetEventCounter(EventCounterType value)
    * @brief   set counter value
    * @param   EventCounterType value
    * @return  None
    */
    void SetEventCounter(EventCounterType value)
    {
        m_eventCounter = value;
    }

    /**
    * @fn      void UpdateTimeStamps()
    * @brief   Update time stamps of last/first update
    * @param   None
    * @return  None
    */
    void UpdateTimeStamps()
    {
        auto currentTs = getCurrentUnixTime();

        if (m_firstEventTs == UnixTimeStampType(0))
        {
            SetFirstEventTs(currentTs);
        }

        SetLastAttack(currentTs);
    }

    /**
    * @fn      void SetFirstEventTs(UnixTimeStampType timeStamp)
    * @brief   Setter for first update unix ts
    * @param   UnixTimeStampType timeStamp
    * @return  None
    */
    void SetFirstEventTs(UnixTimeStampType timeStamp)
    {
        m_firstEventTs = timeStamp;
    }

    /**
    * @fn      UnixTimeStampType GetFirstEventTs()
    * @brief   Getter for first update unix ts
    * @param   None
    * @return  UnixTimeStampType
    */
    UnixTimeStampType GetFirstEventTs()
    {
        return m_firstEventTs;
    }

    /**
    * @fn      void SetLastAttack(UnixTimeStampType timeStamp)
    * @brief   Setter for last update unix ts
    * @param   UnixTimeStampType timeStamp
    * @return  None
    */
    void SetLastAttack(UnixTimeStampType timeStamp)
    {
        m_lastEventTs = timeStamp;
    }

    /**
    * @fn      UnixTimeStampType GetLastAttack()
    * @brief   Getter for last update unix ts
    * @param   None
    * @return  UnixTimeStampType
    */
    UnixTimeStampType GetLastAttack()
    {
        return m_lastEventTs;
    }

protected:

    EventCounterType m_eventCounter;
    UnixTimeStampType m_firstEventTs;
    UnixTimeStampType m_lastEventTs;

    UnixTimeStampType getCurrentUnixTime()
    {
        auto msSinceEpoch =
            std::chrono::system_clock::now().time_since_epoch() /
            std::chrono::milliseconds(1);

        return UnixTimeStampType(msSinceEpoch);
    }
};
} // namespace counters
} // namespace common