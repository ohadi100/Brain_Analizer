/**
 * @file      BaseCounterManager.h
 * @brief     Abstract class allowing unified interface for all counter managers
  
 */

#pragma once

#include <string>
#include <json/json.h>

namespace common
{

namespace counters
{

/**
 * @class      BaseCounterManager.h
 * @brief      Abstract class for all counter managers.
               Any class that inheritance this class, can get serialized counters as a string or as a JSON.
 */
class BaseCounterManager
{
public:

    /**
     * @fn      BaseCounterManager()
     * @brief   constructor
     * @param   none
     * @return  none
     */
    BaseCounterManager() = default;

    /**
     * @fn      virtual ~BaseCounterManager()
     * @brief   desstructor
     * @param   none
     * @return  none
     */
    virtual ~BaseCounterManager() = default;

    /**
     * @fn      virtual std::string GetSerializedCounters()
     * @brief   returns serialized counters
     * @param   none
     * @return  std::string - serialized counters
     */
    virtual std::string GetSerializedCounters() = 0;

    /**
     * @fn      virtual Json::Value GetCountersJson()
     * @brief   returns Json with counters
     * @param   none
     * @return  Json::Value - Json with counters
     */
    virtual Json::Value GetCountersJson() = 0;
};

} //namespace counters

} //namespace common