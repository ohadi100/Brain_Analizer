#include "AraLogHandler.hpp"

namespace common
{
    namespace utils
    {

    AraLogHandler::AraLogHandler(const char *appName, LogLevel minimalLevelToShow): m_minimalLevel(minimalLevelToShow)
    {
        ara::log::InitLogging("CYMO", appName, ara::log::LogLevel::kVerbose, ara::log::LogMode::kRemote);
        m_logger = &(ara::log::CreateLogger(appName, appName));
    }

    void AraLogHandler::HandleLogLine(LogLevel level, __attribute__ ((unused)) uint64_t timeStampMs, const char * log)
    {
        switch (level)
        {
        case LogLevel::LOG_LEVEL_FATAL:
            m_logger->LogFatal() << log;
            break;
        case LogLevel::LOG_LEVEL_ERROR:
            m_logger->LogError() << log;
            break;
        case LogLevel::LOG_LEVEL_WARNING:
            m_logger->LogWarn() << log;
            break;
        case LogLevel::LOG_LEVEL_INFO:
            m_logger->LogInfo() << log;
            break;
        case LogLevel::LOG_LEVEL_DEBUG:
            m_logger->LogDebug() << log;
            break;
        case LogLevel::LOG_LEVEL_VERBOSE:
            m_logger->LogVerbose() << log;
            break;
        default:
            m_logger->LogFatal() << "Unknown log level";
            break;
        }
    }

    } // namespace utils
} // namespace common

