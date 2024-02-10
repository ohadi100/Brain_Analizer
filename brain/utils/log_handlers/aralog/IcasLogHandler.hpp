#pragma once

#include "Logger.hpp"
#include <ara/log/logging.h>
#include "../AraConstants.hpp"

namespace common
{
namespace utils
{

/**
* @class IcasLogHandler
* @brief IcasLogHandler class inherite from LogHandler.
         This class manage the logger over the Icas Platform.
         HandleLogLine manage the logging via the logging level.
*/
class IcasLogHandler : public LogHandler
{
public:
    explicit IcasLogHandler(const char*             appName            = IDS_APP_NAME_LOGGER,
                   common::utils::LogLevel minimalLevelToShow = LOG_LEVEL_DEFAULT)
    {
        // Only the first argument (appName) is actually evaluated. The rest of the signature is mandated by the
        // ara::log standard, but not used.
        ara::log::InitLogging(
            appName, IDS_APP_DESCRIPTION, common::utils::araLogLevels[minimalLevelToShow], ara::log::LogMode::kRemote);
        m_logger = &(ara::log::CreateLogger(appName, appName, common::utils::araLogLevels[minimalLevelToShow]));
    }

    void
    HandleLogLine(LogLevel level, uint64_t timeStampMs, const char* log) override
    {
        static thread_local char logPrefix[32]{};
#ifdef ENABLE_QUEUE_LOG
        PrintTimeStamp(logPrefix, sizeof(logPrefix), timeStampMs);
#else
        (void)timeStampMs;
#endif

        switch (level)
        {
        case common::utils::LogLevel::LOG_LEVEL_FATAL:
            m_logger->LogFatal() << logPrefix << log;
            break;
        case common::utils::LogLevel::LOG_LEVEL_ERROR:
            m_logger->LogError() << logPrefix << log;
            break;
        case common::utils::LogLevel::LOG_LEVEL_WARNING:
            m_logger->LogWarn() << logPrefix << log;
            break;
        case common::utils::LogLevel::LOG_LEVEL_INFO:
            m_logger->LogInfo() << logPrefix << log;
            break;
        case common::utils::LogLevel::LOG_LEVEL_DEBUG:
            m_logger->LogInfo() << logPrefix << log;
            break;
        case common::utils::LogLevel::LOG_LEVEL_VERBOSE:
            m_logger->LogVerbose() << logPrefix << log;
            break;
        default:
            m_logger->LogFatal() << logPrefix << "Unknown log level";
        }
    }

private:
    ara::log::Logger* m_logger{nullptr};
};

}  // namespace utils
}  // namespace common