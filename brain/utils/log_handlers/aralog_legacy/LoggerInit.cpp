#include "../LoggerInit.hpp"
#include "Logger.hpp"
#include "AraLogHandler.hpp"

namespace brain
{
namespace utils
{
    constexpr char IDS_NAME_IN_ICAS_LOG[] = "Brain";

    void InitLogger()
    {
        auto logHandler = std::make_shared<common::utils::AraLogHandler>(IDS_NAME_IN_ICAS_LOG, common::utils::LogLevel::LOG_LEVEL_INFO);
        common::utils::Logger::GetInstance().RegisterLogCallback(logHandler);
    }
} // namespace utils
} // namespace brain
