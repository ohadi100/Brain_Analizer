/**
 * @file      CounterMapTemplate.h
 * @brief     Debug counter manager for MEB events
  
 */

#pragma once

#include <unordered_map>
#include <string>
#include <memory>
#include <json/json.h>

namespace common
{

namespace counters
{

/**
 * @class     CounterMapTemplate
 * @brief     This class is a wraper for std::map<>.
              This class can Clear(), Iterate(), AddCounter() & check if the counter already exist.
 */
template <class T>
class CounterMapTemplate
{
public:
    using CounterType = T;
    using CounterConstType = const T;
    using CounterTypeRef = T&;
    using CounterMapType = std::unordered_map<std::string, std::shared_ptr<CounterType>>;
    using CounterMapTypeIter = typename CounterMapType::iterator;
    using CounterMapTypeConstIter = typename CounterMapType::const_iterator;

    using CounterMapKeyType = std::string;
    using MapPairType = std::pair<CounterMapKeyType, std::shared_ptr<CounterType>>;

public:

    /**
     * @fn      CounterMapTypeIter AddCounter(CounterMapKeyType keyName)
     * @brief   Add new counter to the counters map
     * @param   CounterMapKeyType keyName
     * @return  CounterMapTypeIter - Iterator to the value in the map
     */
    CounterMapTypeIter AddCounter(CounterMapKeyType keyName)
    {
        auto newCounter = MapPairType(keyName, std::make_shared<CounterType>(keyName));
        auto insertRetVal = m_countersMap.insert(std::move(newCounter));
        return insertRetVal.first;
    }

    /**
     * @fn      bool CounterExists(std::string counterName)
     * @brief   Check if counter with giver name exists
     * @param   std::string counterName
     * @return  bool - true if counter exists
     */
    bool CounterExists(std::string counterName)
    {
        auto iter = m_countersMap.find(counterName);

        if (iter == m_countersMap.end())
        {
            return false;
        }

        return true;
    }

    /**
     * @fn      CounterMapTypeIter GetCounter(std::string counterName)
     * @brief   Returns iterator to the given counter
     * @param   std::string counterName
     * @return  CounterMapTypeIter - Iterator to the given counter
     */
    CounterMapTypeIter GetCounter(std::string counterName)
    {
        return m_countersMap.find(counterName);
    }

    /**
     * @fn      End
     * @brief   Returns iterator end
     * @param   None
     * @return  CounterMapTypeIter - Iterator to the counters end
     */
    CounterMapTypeIter End()
    {
        return m_countersMap.end();
    }

    /**
     * @fn      Json::Value GetCountersAsJson()
     * @brief   Returns counters as JSON
     * @param   None
     * @return  Json::Value
     */
    Json::Value GetCountersAsJson()
    {
        Json::Value json;

        for (auto& it : m_countersMap)
        {
            std::string tmp = { it.first };
            json[tmp] = it.second->GetCounterAsJson();
        }

        return json;
    }

    /**
     * @fn      void Clear()
     * @brief   Clear all content
     * @param   void
     * @return  void
     */
    void Clear()
    {
        m_countersMap.clear();
    }


private:

    /**
     * @brief   Map of the counters
     */
    CounterMapType m_countersMap;

};

} // namespace counters

} // namespace common