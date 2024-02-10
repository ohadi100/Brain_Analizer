#include "DiagnosticsManager.hpp"
#include "measurement_values/DiagMeasurementValuesManager.hpp"
#include "diag_accessor/DiagFeatureFlags.hpp"
#include "routines/IDSResetLifeCycleRoutine.hpp"

#include <factory/PersistentMemoryFactory.hpp>
#include <persistent_map/PersistentMap.h>
#include <DBNames.hpp>
#include "common/utils/logger/Logger.hpp"


using brain::diagnostics::DiagnosticsManager;


DiagnosticsManager::DiagnosticsManager(
    CounterManagerPtr countersManager,
    IdsEnablerPtr idsEnabler,
    PersistentMemoryFactoryPtr persistentFactory,
    TimerPtr timer)
    : m_idsFunctionStoppedDtc(ids_evt_EventIdsFunctionStoppedWorking)
    , m_udsInterfaceUnavailableDtc(ids_evt_EventIdsUdsInterfaceUnavailable)
    , m_debugCounters(countersManager)
    , m_serviceDiscoveryDtc(timer)
    , m_serviceRegistryDtc(timer)
{
    connectToPersistency(persistentFactory);

    m_diagMeasurementValuesManager = std::make_shared<brain::diagnostics::measurement_values::DiagMeasurementValuesManager>(countersManager);
    m_diagFeatureFlags = std::make_shared<brain::diagnostics::diag_accessor::DiagFeatureFlags>(idsEnabler);
    m_idsResetLifeCycleRoutine = std::make_shared<brain::diagnostics::routines::IDSResetLifeCycleRoutine>(m_diagMeasurementValuesManager);
}

void DiagnosticsManager::SetupCounterPublishers()
{
    m_diagMeasurementValuesManager->SetUpCounterPublishers(m_persistentMemory);
}

DiagnosticsManager::~DiagnosticsManager()
{
    if (nullptr != m_persistentMemory)
    {
        m_persistentMemory->Disable();
    }
}

void DiagnosticsManager::connectToPersistency(PersistentMemoryFactoryPtr persistentFactory)
{
    if (nullptr == persistentFactory)
    {
        LOG_WARNING << "persistentFactory is nullptr" << LOG_NOOP;
        return;
    }

    m_persistentMemory = std::make_shared<common::utils::PersistentMap>(persistentFactory,
                                                                        common::memory::PER_MEM_IDS_BRAIN_DIAGNOSTICS);

    if (!m_persistentMemory->Init())
    {
        LOG_WARNING << "Failed to initialize persistence map" << LOG_NOOP;
        return;
    }

}


void DiagnosticsManager::Init()
{
    SetupCounterPublishers();
    m_diagFeatureFlags->LoadDiagnosticData();
}

inline std::atomic<bool>&
DiagnosticsManager::GetFeatureFlag(uint8_t adaptationId)
{
    return m_diagFeatureFlags->GetFeatureFlag(static_cast<AdaptationId>(adaptationId));
}


void DiagnosticsManager::updateDiagnosticsOnCrash()
{
    // Diag DTC - 0x600508 - ids_function_stopped_working
    m_idsFunctionStoppedDtc.SetEvent(true);
}

void DiagnosticsManager::updateDiagnosticsUDSEvent()
{
    // Diag DTC - 0x600508 - ids_function_stopped_working
    m_udsInterfaceUnavailableDtc.SetEvent(true);
}

void DiagnosticsManager::UpdateServiceDiscoveryStatus(uint8_t communicatorId, bool serviceDiscoveryStatus)
{
    m_serviceDiscoveryDtc.UpdateServiceDiscoveryStatus(communicatorId, serviceDiscoveryStatus);
}

void DiagnosticsManager::UpdateServiceRegistyStatus(bool serviceRegistryStatus)
{
    m_serviceRegistryDtc.UpdateServiceRegistyStatus(serviceRegistryStatus);
}