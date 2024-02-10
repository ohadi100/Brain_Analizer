#include "SimulationLogHandler.hpp"
#include <iostream>

using common::utils::SimulationLogHandler;

namespace common
{
namespace utils
{
static constexpr char COLOR_BLACK[]{"\033[30m"};              /* Black */
static constexpr char COLOR_RED[]{"\033[31m"};                /* Red */
static constexpr char COLOR_GREEN[]{"\033[32m"};              /* Green */
static constexpr char COLOR_YELLOW[]{"\033[33m"};             /* Yellow */
static constexpr char COLOR_BLUE[]{"\033[34m"};               /* Blue */
static constexpr char COLOR_MAGENTA[]{"\033[35m"};            /* Magenta */
static constexpr char COLOR_CYAN[]{"\033[36m"};               /* Cyan */
static constexpr char COLOR_WHITE[]{"\033[37m"};              /* White */
static constexpr char COLOR_BOLDBLACK[]{"\033[1m\033[30m"};   /* Bold Black */
static constexpr char COLOR_BOLDGREEN[]{"\033[1m\033[32m"};   /* Bold Green */
static constexpr char COLOR_BOLDYELLOW[]{"\033[1m\033[33m"};  /* Bold Yellow */
static constexpr char COLOR_BOLDBLUE[]{"\033[1m\033[34m"};    /* Bold Blue */
static constexpr char COLOR_BOLDMAGENTA[]{"\033[1m\033[35m"}; /* Bold Magenta */
static constexpr char COLOR_BOLDCYAN[]{"\033[1m\033[36m"};    /* Bold Cyan */
static constexpr char COLOR_BOLDWHITE[]{"\033[1m\033[37m"};   /* Bold White */
}  // namespace utils
}  // namespace common

static std::string
initEmptyString() noexcept
{
    return std::string{};
}
thread_local std::string common::utils::SimulationLogHandler::s_color_start = initEmptyString();
std::string common::utils::SimulationLogHandler::s_history = initEmptyString();
bool common::utils::SimulationLogHandler::s_nolog = false;
bool common::utils::SimulationLogHandler::s_enableHistory = false;

void SimulationLogHandler::SetColor(std::string const color)
{
	s_color_start = color;
}

void SimulationLogHandler::setNoLog() noexcept
{
    s_nolog = true;
}

void SimulationLogHandler::ResetColor()
{
    s_color_start = std::string();
}

SimulationLogHandler::SimulationLogHandler() :
    LogHandler()
{
}

void
SimulationLogHandler::HandleLogLine(LogLevel level, uint64_t timeStampMs, const char* log)
{
    static size_t constexpr LOG_PREFIX_LENGTH{128U};
    static thread_local char logPrefix[LOG_PREFIX_LENGTH];
    auto const               prefixLen = PrintTimeStamp(logPrefix, sizeof(logPrefix), timeStampMs);
    std::ignore                        = snprintf(
        logPrefix + prefixLen, sizeof(logPrefix) - prefixLen, " | %-7s | ", common::utils::levelNames[level].c_str());

    static size_t constexpr MAX_SIZE{30000U};
    if ((true == s_enableHistory) && (MAX_SIZE > s_history.size()))
    {
        s_history += log;
        s_history += '\n';
    }

#ifndef ENABLE_QUEUE_LOG
    std::lock_guard<std::mutex> const lock(m_mutex);
#endif
    std::string           color = s_color_start;
    static constexpr char COLOR_BOLDRED[]{"\033[1m\033[31m"}; /* Bold Red */
    if ((!color.empty()) && (level <= LogLevel::LOG_LEVEL_WARNING))
    {
        color = COLOR_BOLDRED;
    }

    static constexpr char COLOR_RESET[]{"\033[0m"};

    if (!s_nolog)
    {
        std::cout << color << logPrefix << log << COLOR_RESET << std::endl;
    }

#ifdef _WIN32
    OutputDebugString(log);
    OutputDebugString("\n");
#endif /* _WIN32 */
}

bool SimulationLogHandler::FindInHistory(std::string const& subString) noexcept
{
    return (std::string::npos != s_history.find(subString));
}

void SimulationLogHandler::SetEnableHistory(bool enableHistory) noexcept
{
    s_enableHistory = enableHistory;
}

void SimulationLogHandler::ClearHistory()
{
    s_history.clear();
}