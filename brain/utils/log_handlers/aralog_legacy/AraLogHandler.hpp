#ifndef __ARALOG_HANDLER_HPP__
#define __ARALOG_HANDLER_HPP__

#include <ara/log/logging.hpp>

#include <cstring>
#include <ctime>
#include <string>
#include <time/Time.hpp>
#include "Logger.hpp"

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
        class AraLogHandler : public common::utils::LogHandler
        {
        public:

            AraLogHandler(const char *appName, LogLevel minimalLevelToShow);

            void HandleLogLine(LogLevel level, __attribute__ ((unused)) uint64_t timeStampMs, const char * log) override;

        private:
            ara::log::Logger *m_logger;
            LogLevel m_minimalLevel;
        };

    } // namespace utils
} // namespace common

#endif
