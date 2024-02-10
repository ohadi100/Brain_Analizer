/**
 * @file main.cpp
 * @brief Main entry to IDS, made agnostic to project type
 */


#include "IdsMainFlow.hpp" // Specify include in the project specific CMake file, avoid multiple 
#include "Logger.hpp"
#include "LoggerInit.hpp"
#include "version.hpp"
#include "ExecutionReporter.hpp"
#include "ThreadHandler.hpp"
#include "signal_handlers.hpp" 


/*
    Uniform main file for all projects
*/

int32_t main(int, char**)
{
    int res{0};

    // Initialize the logger before IDS Start run
    brain::utils::InitLogger();
    LOG_INFO << "SELF_TEST: IDS Core starting, version info: " << common::version::Version::GetVersion() << LOG_NOOP;

    brain::execution_reporter::ExecutionReporter reporter;
    reporter.ReportIdsStart();
    common::register_signal_handler();

    // Made to expanding the lifetime of thread handler and control it's stop
    auto threadHandler = common::thread_handler::ThreadHandler::GetInstance();

    {
        brain::main_flow::IdsMainFlow app;
        app.Init();

        LOG_INFO << "IDS Starting main run stage" << LOG_NOOP;

        app.Run();

        LOG_INFO << "IDS Finished main run stage" << LOG_NOOP;

        app.Destroy();
        // app Dtor called
    }

    threadHandler->Stop();
    common::deregister_signal_handler();
    reporter.ReportIdsTearDown();

    LOG_INFO << "SELF_TEST: IDS finished run, exiting with result: " << res << LOG_NOOP;
    return res;
}
