#pragma once
/**
 * @file
 * @brief    This file contains the logger handle for the SSP platform.
 */
#include <iostream>

#include "brain/utils/UtilsConstants.hpp"
#include "common/utils/logger/Logger.hpp"

using common::utils::LogLevel;
using common::utils::LogHandler;
using common::utils::levelNames;

class SSPLogHandler : public LogHandler
{
public:
    void HandleLogLine(LogLevel level, uint64_t timeStampMs, const char * log) override
    {
        std::cout << "[" << levelNames[level] << "]" << "defcore_detection(" << timeStampMs << ")" << log << std::endl;
    }
};
