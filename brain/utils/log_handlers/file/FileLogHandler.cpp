#include "FileLogHandler.hpp"

using common::utils::FileLogHandler;

FileLogHandler::FileLogHandler(std::string const& fileName) :
    LogHandler(),
    m_logString(""),
    m_fileName(fileName)
{
    m_outputFileStream.exceptions(std::ios::badbit);
    try
    {
        m_outputFileStream.open(m_fileName, std::ofstream::app | std::ofstream::binary);
        m_logString.clear();
    }
    catch (std::ofstream::failure& e)
    {
        static_cast<void>(e);
    }
}

FileLogHandler::~FileLogHandler()
{
    try
    {
#ifndef ENABLE_QUEUE_LOG
        std::lock_guard<std::mutex> const lock(m_mutex);
#endif
        if (m_outputFileStream.is_open())
        {
            static_cast<void>(m_outputFileStream.write(m_logString.c_str(), static_cast<std::streamsize>(m_logString.length())));
            m_logString.clear();
            m_outputFileStream.close();
        }
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "failed destruction and got exception." << LOG_NOOP;
    } //only for parasoft violations    
}

void FileLogHandler::HandleLogLine(LogLevel level, uint64_t timeStampMs, const char* log)
{
    static size_t constexpr MAX_SIZE_LOG_PREFIX{128};
    static thread_local char logPrefix[MAX_SIZE_LOG_PREFIX];
    auto const               prefixLen = PrintTimeStamp(logPrefix, MAX_SIZE_LOG_PREFIX, timeStampMs);
    std::ignore                        = snprintf(
        logPrefix + prefixLen, MAX_SIZE_LOG_PREFIX - prefixLen, " | %-7s | ", common::utils::levelNames[level].c_str());
#ifndef ENABLE_QUEUE_LOG
    std::lock_guard<std::mutex> const lock(m_mutex);
#endif
    m_logString += logPrefix;
    m_logString += log;
    m_logString += "\n";

    static constexpr uint32_t LOGGER_BUFFER_SIZE_TO_FLUSH = 10000U;
    if (m_logString.length() > LOGGER_BUFFER_SIZE_TO_FLUSH)
    {
        if (m_outputFileStream.is_open())
        {
            try
            {
                static_cast<void>(m_outputFileStream.write(m_logString.c_str(), static_cast<std::streamsize>(m_logString.length())));
                m_logString.clear();
            }
            catch (std::ofstream::failure& e)
            {
                static_cast<void>(e);
            }
        }
    }
}

#ifdef TESTS
void FileLogHandler::ClearFile()
{
    try
    {
#ifndef ENABLE_QUEUE_LOG
        std::lock_guard<std::mutex> const lock(m_mutex);
#endif
        if (m_outputFileStream.is_open())
        {
            m_outputFileStream.close();
        }
        m_outputFileStream.open(m_fileName, std::ofstream::trunc | std::ofstream::binary);
    }
    catch (std::ofstream::failure& e)
    {
        static_cast<void>(e);
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& e)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "failed open/close file and got exception: " << e.what() << LOG_NOOP;
    } //only for parasoft violations
}
#endif // TESTS
