/**
 * @file
 * @brief     This file contains the functionality of the NullEngine class
 */
#include "NullEngine.hpp"
#include "common/utils/logger/Logger.hpp"

using brain::engines::NullEngine;
using brain::engines::ReturnCode;

NullEngine::NullEngine(CounterManagerPtr countersManager) :
    m_nullCounter(nullptr)
{
    if (countersManager)
    {
        static std::string const NULL_SD_QUEUE("NULL SD - pop from queue");
        m_nullCounter = countersManager->CreateCounter(NULL_SD_QUEUE);
    }
}

ReturnCode NullEngine::processInternal(UPSensorData sd)
{
    LOG_DEBUG << "NullEngine::Process - SD with tag=" << static_cast<uint32_t>(sd->GetTag()) << " arrived to NullEngine"
              << LOG_NOOP;
    if (m_nullCounter)
    {
        m_nullCounter->CountEvent();
    }

    return ReturnCode::Success;
}
