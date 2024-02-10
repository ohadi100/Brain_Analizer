#include <unistd.h>
#include "logUtility.hpp"
#include "brain/brain_app/BrainApp.hpp"

using brain::app_mng::BrainApp;

int32_t
runIdsCore()
{
    BrainApp brain;
    if (!brain.Init())
    {
        return 1;
    }

    brain.Run();

    return 0;
}

int main(int argc, char * argv[])
{
    std::cout << "Starting defcore main..." << std::endl;
    int32_t result{0};
    auto const logHandler = std::make_shared<SSPLogHandler>();
    common::utils::Logger::GetInstance().RegisterLogCallback(logHandler);

    LOG_INFO << "Log was started" << LOG_NOOP;

    common::register_signal_handler();

    try
    {
        result = runIdsCore();
    }
    catch (std::system_error const & e)
    {
        LOG_ERROR << "received system_error " << e.code().value() << "," << e.code().category().name() << ","
                  << e.code().message() << "," << e.what() << std::endl
                  << "terminating." << LOG_NOOP;
    }
    catch (std::exception const & e)
    {
        LOG_ERROR << "received exception: " << e.what() << std::endl << "terminating." << LOG_NOOP;
    }
    catch (...)
    {
        LOG_ERROR << "received severe unknown error" << std::endl << "terminating." << LOG_NOOP;
    }

    common::deregister_signal_handler();
    LOG_INFO << "IDS Core - exiting main" << LOG_NOOP;

    return result;
}
