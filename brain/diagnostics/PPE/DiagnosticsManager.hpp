#pragma once
/**
 * @file
 * @brief     This file contains the definition of the DiagnosticsManager class
 */

#include <memory>
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "common/utils/logger/Logger.hpp"
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#include "brain/diagnostics/dtc/DtcEvent.hpp"
#include "brain/diagnostics/dtc/DtcServiceDiscoveryEvent.hpp"
#include "brain/diagnostics/dtc/DtcServiceRegistryEvent.hpp"

namespace common
{
    namespace counters
    {
        class CounterManager;
    } // namespace counters

    namespace shutdown_and_enabler
    {
        class IDSEnabler;
    } // namespace shutdown_and_enabler

    namespace memory
    {
        class PersistentMemoryFactory;
    } // namespace memory

    namespace utils
    {
        class PersistentMap;
    } // namespace utils
} // namespace common

namespace brain
{
    namespace diagnostics
    {
        namespace measurement_values
        {
            class DiagMeasurementValuesManager;
        } // namespace measurement_values
        
        namespace diag_accessor
        {
            class DiagFeatureFlags;
        } // namespace diag_accessor

        namespace routines
        {
            class IDSResetLifeCycleRoutine;
        } // namespace routines
    } // namespace diagnostics
} // namespace brain


namespace brain
{
namespace diagnostics
{
/**
 * @class   DiagnosticsManager
 * @brief   Initializes and stops all measurement values
 */
class DiagnosticsManager : public DiagnosticsManagerInterface
{
public:

    using DiagMeasurementValuesManagerPtr = std::shared_ptr<brain::diagnostics::measurement_values::DiagMeasurementValuesManager>;
    using DiagFeatureFlagsPtr = std::shared_ptr<brain::diagnostics::diag_accessor::DiagFeatureFlags>;
    using IDSResetLifeCycleRoutinePtr = std::shared_ptr<brain::diagnostics::routines::IDSResetLifeCycleRoutine>;
    using AdaptationId = brain::adaptation_values_names::AdaptationId;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;
    using IdsEnablerPtr = std::shared_ptr<common::shutdown_and_enabler::IDSEnabler>;
    using PersistentMemoryFactoryPtr = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using PersistentMap = common::utils::PersistentMap;
    using PersistentMapPtr = std::shared_ptr<PersistentMap>;
    using DtcServiceDiscoveryEventPtr = brain::diagnostics::dtc::DtcServiceDiscoveryEvent;
    using DtcServiceRegistryEventPtr = brain::diagnostics::dtc::DtcServiceRegistryEvent;
    using TimerPtr = std::shared_ptr<common::Timer>;
    using DtcEvent = brain::diagnostics::dtc::DtcEvent;
    /**
     * @brief   Constructor
     * @param   CounterManagerPtr countersManager
     * @param   IdsEnablerPtr idsEnabler
     * @param   PersistentMemoryFactoryPtr persistentFactory - persistent memory for saving measurement values
     * @param   TimerPtr timer
     */
    DiagnosticsManager(
        CounterManagerPtr countersManager,
        IdsEnablerPtr idsEnabler,
        PersistentMemoryFactoryPtr persistentFactory,
        TimerPtr timer);

    virtual ~DiagnosticsManager();

    /**
     * @brief    default copy constructor
     */
    DiagnosticsManager(const DiagnosticsManager& other) = default;

    /**
     * @brief    default move constructor
     */
    DiagnosticsManager(DiagnosticsManager&& other) = default;

    /**
     * @brief    default copy assignment operator
     */
    DiagnosticsManager& operator=(DiagnosticsManager const&) = default;

    /**
     * @brief   default move assignment operator
     */
    DiagnosticsManager& operator=(DiagnosticsManager&&) = default;

    void Init() override;

    inline std::atomic<bool>&
    GetFeatureFlag(uint8_t adaptationId) override;

    void updateDiagnosticsOnCrash() override;

    void updateDiagnosticsUDSEvent() override;

    void UpdateServiceDiscoveryStatus(uint8_t communicatorId, bool serviceDiscoveryStatus) override;
    
    void UpdateServiceRegistyStatus(bool serviceRegistryStatus) override;
    
#ifndef TESTS
private:
#endif 
    void SetupCounterPublishers();
    void connectToPersistency(PersistentMemoryFactoryPtr persistentFactory);
    
    DiagMeasurementValuesManagerPtr m_diagMeasurementValuesManager;
    DiagFeatureFlagsPtr m_diagFeatureFlags;
    IDSResetLifeCycleRoutinePtr m_idsResetLifeCycleRoutine;
    DtcEvent m_idsFunctionStoppedDtc;   
    DtcEvent m_udsInterfaceUnavailableDtc;   // Diag DTC - 0x600508 - ids_function_stopped_working
    CounterManagerPtr m_debugCounters;
    PersistentMapPtr m_persistentMemory;
    DtcServiceDiscoveryEventPtr m_serviceDiscoveryDtc;
    DtcServiceRegistryEventPtr m_serviceRegistryDtc;
};

} // namespace diagnostics
} // namespace brain

