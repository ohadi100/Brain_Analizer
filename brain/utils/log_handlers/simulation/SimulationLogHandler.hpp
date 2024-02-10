#pragma once

#include <mutex>
#include "Logger.hpp"

namespace common
{
namespace utils
{

class SimulationLogHandler : public LogHandler
{
    static thread_local std::string s_color_start;
    static bool s_nolog;

public:
    static void SetColor(std::string const color);

    static void setNoLog() noexcept;

    static void ResetColor();
    
    SimulationLogHandler();

    void HandleLogLine(LogLevel level, uint64_t timeStampMs, const char* log) override;

    // The following functions are used for UT to track events in IDS.

    /**
    * @brief   Checks the Presence of a particular log in the logs history.
    * @param   std::string subString - the subString to be found.
    * @return  bool - true if subString is found, false otherwise.
    */
    static bool FindInHistory(std::string const& subString) noexcept;

    /**
    * @brief   Set s_enableHistory to true or false.
    * @param   bool enableHistory - true to enable history saving, false for otherwise.
    */
    static void SetEnableHistory(bool enableHistory) noexcept;

    /**
    * @brief   Clears the log history.
    */
    static void ClearHistory();

private:

    /**
     * @var     std::mutex m_mutex
     * @brief   mutex to handle the LogHandler
     */
#ifndef ENABLE_QUEUE_LOG
    std::mutex  m_mutex;
#endif
    // The following members are used for UT to track events in IDS.
    static std::string  s_history;
    static bool         s_enableHistory;
};


}  // namespace utils
}  // namespace common