
//@file
//@brief       this is the entry point for the IDS brain
//@author      Multiple authors
//@version     1.0

#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>

#include <ac/com/runtime.hpp>
#include <ara/exec/execution_client.hpp>


#include <ara/exec/execution_client.hpp>
#include "ara/core/instance_specifier.h"
#include "ara/phm/supervised_entity.h"


#include "common/utils/logger/Logger.hpp"
#include "common/utils/os/signal_handlers.hpp"
#include "common/utils/os/linux/network.hpp"
#include "common/version/version.hpp"
#include "common/alive_supervision/AliveSupervision.hpp"

#include "brain/brain_app/BrainApp.hpp"
#include "brain/utils/UtilsConstants.hpp"

#if defined(EEE_PLATFORM)
#include "brain/utils/log_handlers/aralog/IcasLogHandler.hpp"
#else
#include "brain/utils/log_handlers/simulation/SimulationLogHandler.hpp"
#endif

/// PHM definitions. Must comply to the PHM_brain.json and HM_brain.json configurations.

using common::Timer;
using common::configuration::Configuration;
using common::alive_supervision::AliveSupervision;
using brain::app_mng::BrainApp;

#ifdef EEE_PLATFORM
void startAliveSupervision();
void startAliveSupervision()
{
    // start alive supervision
    constexpr std::uint16_t entity_id = 6010U; // As defined in brain_ARA_PHM.json, needs to be unique (chosen arbitrarily)
    static ara::core::InstanceSpecifier const phmInstanceSpecifier{"e3_ids"};
    static ara::phm::SupervisedEntity         phmSupervisionEntity{phmInstanceSpecifier};
    static ara::phm::Checkpoint const         phmCheckpointId{entity_id};

    AliveSupervision::GetInstance()->Start([&] 
    {
        try
        {
            phmSupervisionEntity.ReportCheckpoint(phmCheckpointId);
        }
        catch(std::exception const& e)
        {
            LOG_WARNING << "Exception when sending PHM report: " << e.what() << LOG_NOOP;
        }
    });
}
#endif

namespace common
{
int32_t runIdsCore(int argc, char* argv[]);

int32_t
runIdsCore(int argc, char* argv[])
{
    static_cast<void>(argc);
    static_cast<void>(argv);

    BrainApp brain;

    if (!brain.Init())
    {
        return 1;
    }

    brain.Run();

    return 0;
}
}  // namespace common


int32_t main(int argc, char * argv[])
{
#if defined(EEE_PLATFORM)
    auto const logHandler = std::make_shared<common::utils::IcasLogHandler>();
    common::utils::Logger::GetInstance().RegisterLogCallback(logHandler);
#else // SIMULATION
    auto const logHandler = std::make_shared<common::utils::SimulationLogHandler>();
    //remove the below line if you need to activate the logs. Logs are removed to allow a faster run of UT test suite.
    //logHandler->setNoLog();
    common::utils::Logger::GetInstance().RegisterLogCallback(logHandler);
#endif

    LOG_INFO << "SELF_TEST: IDS Core starting..." << LOG_NOOP;
    LOG_INFO << "IDS version info: " << common::version::Version::GetVersion() << LOG_NOOP;

#ifdef EEE_PLATFORM
    setenv("APP_INSTANCE_ID", "brain", 1);
    static ara::exec::ExecutionClient emClient;
    LOG_INFO << "Reporting application state is running to the Execution Manager" << LOG_NOOP;
    if (ara::exec::ExecutionReturnType::kSuccess != emClient.ReportExecutionState(ara::exec::ExecutionState::kRunning))
    {
        LOG_ERROR << "Failed to report application state is running to the Execution Manager" << LOG_NOOP;
    }
#endif // EEE_PLATFORM

    common::initializeNetworking();
#ifdef EEE_PLATFORM
    startAliveSupervision();
#endif
    int32_t res{};
    try
    {
        // main ids code
        res = common::runIdsCore(argc, argv);

        // stop alive supervision
        AliveSupervision::GetInstance()->Stop();
 
 #ifdef EEE_PLATFORM
        LOG_INFO << "Reporting application state is terminating to the Execution Manager" << LOG_NOOP;
        if (ara::exec::ExecutionReturnType::kSuccess != emClient.ReportExecutionState(ara::exec::ExecutionState::kTerminating))
        {
            LOG_ERROR << "Failed to report application state is terminating to the Execution Manager" << LOG_NOOP;
        }
#endif // EEE_PLATFORM

        LOG_INFO << "IDS Core - exiting main" << LOG_NOOP;
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

    return res;
}
