/**
 * @file
 * @brief     This file contains the functionality of the CommunicatorManager class
 */


#include "brain/communicator/SSP/CommunicatorManager.hpp"
#include <tuple>
#include "brain/brain_app/BrainApp.hpp"
#include "brain/communicator/ids_portal/PortalCommunicator/PortalCommunicator.hpp"
#include "brain/communicator/periodic/PeriodicReportCommunicator.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#include "brain/noise_filter/sensor_noise_filter/SensorNoiseFilter.hpp"
#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "utils/UtilsConstants.hpp"

using brain::app_mng::BrainApp;
using brain::brain_communicator::CommunicatorManager;
using brain::brain_communicator::periodic::PeriodicReportCommunicator;
using brain::brain_communicator::portal::PortalCommunicator;
using brain::brain_noise_filter::NoiseFilter;
using brain::brain_noise_filter::SensorNoiseFilter;
using common::configuration::Configuration;


CommunicatorManager::CommunicatorManager(SensorDataQueuesManagerPtr queuesManager,
                                         ConfigurationPtr           config,
                                         CounterManagerPtr          debugCounters,
                                         TimerPtr __attribute__ ((unused)) timer,
                                         DiagnosticsManagerPtr      diagnosticsManager)
  : m_queuesManager(queuesManager)
  , m_configuration(config)
  , m_debugCounters(debugCounters)
  , m_diagManager(diagnosticsManager)
{
}

void
CommunicatorManager::RegisterAllNotificationHandlers()
{
    LOG_INFO << "registering all notifications" << LOG_NOOP;
    auto periodicComm = std::make_unique<PeriodicReportCommunicator>(m_queuesManager, m_debugCounters, m_configuration);
    periodicComm->Start();
    m_comms.emplace_back(std::move(periodicComm));

#ifdef EEE_PLATFORM 
    auto     sensorNoiseFilter = std::make_shared<SensorNoiseFilter>(m_debugCounters, m_configuration);
    uint32_t flushThreshold    = 1U;
    auto     portalComm        = std::make_unique<PortalCommunicator>(
        m_queuesManager, m_debugCounters, flushThreshold, sensorNoiseFilter);
    portalComm->Start();
    m_comms.emplace_back(std::move(portalComm));
#endif //EEE_PLATFORM
}
