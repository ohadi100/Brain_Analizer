#pragma once

#include <unordered_map>
#include "Logger.hpp"
namespace common
{
namespace utils
{
// parasoft-begin-suppress AUTOSAR-M3_4_1-b "False positive, this is used in more than one file, IcasLogHandler.hpp, SimulationLogHandler.cpp"
static std::unordered_map<common::utils::LogLevel, ara::log::LogLevel>&&
initAraLogLevels() noexcept
{
    static std::unordered_map<common::utils::LogLevel, ara::log::LogLevel> newMap{
        // convert the original log levels to ara:log levels
        {common::utils::LogLevel::LOG_LEVEL_CLEAN, ara::log::LogLevel::kOff},
        {common::utils::LogLevel::LOG_LEVEL_FATAL, ara::log::LogLevel::kFatal},
        {common::utils::LogLevel::LOG_LEVEL_ERROR, ara::log::LogLevel::kError},
        {common::utils::LogLevel::LOG_LEVEL_WARNING, ara::log::LogLevel::kWarn},
        {common::utils::LogLevel::LOG_LEVEL_INFO, ara::log::LogLevel::kInfo},
        {common::utils::LogLevel::LOG_LEVEL_DEBUG, ara::log::LogLevel::kDebug},
        {common::utils::LogLevel::LOG_LEVEL_VERBOSE, ara::log::LogLevel::kVerbose}};
    return std::move(newMap);
}
static std::unordered_map<common::utils::LogLevel, ara::log::LogLevel> araLogLevels = initAraLogLevels();
// parasoft-end-suppress AUTOSAR-M3_4_1-b
}
}  // namespace common
