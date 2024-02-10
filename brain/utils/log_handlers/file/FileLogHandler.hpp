#pragma once

#include "Logger.hpp"

namespace common
{
namespace utils
{

/**
* @class FileLogHandler
* @brief FileLogHandler class inherite from LogHandler.
         This class redirect the logging into a text file.
*/
class FileLogHandler : public LogHandler
{
public:
    /**
     * @brief   constructor
     * @param   std::string fileName - the output file name
     * @param   LogLevel minimalLevelToShow - the logging level to write
     */
    explicit FileLogHandler(std::string const& fileName);

    /**
     * @brief   destructor
     */
    virtual ~FileLogHandler();

    /**
     * @brief   prepare the log line with the logging level & time, and add it to the file.
     * @param   LogLevel level - The logging level
     * @param   const char * log - The log
     */
    void HandleLogLine(LogLevel level, uint64_t timeStampMs, const char* log) override;

#ifdef TESTS
    /**
     * @brief   clear data inside the file.
     */
    void ClearFile();
#endif  // TESTS

private:
    FileLogHandler(FileLogHandler const&) = default;

    FileLogHandler& operator=(FileLogHandler const&) = default;

    /**
     * @var     std::mutex m_mutex
     * @brief   mutex to handle the LogHandler
     */
#ifndef ENABLE_QUEUE_LOG
    std::mutex m_mutex;
#endif
    std::string   m_logString;
    std::string   m_fileName;
    std::ofstream m_outputFileStream;
};

}  // namespace utils
}  // namespace common