#pragma once
/**
 * @file
 * @brief     This file contains the definition of the DiagnosticsManager class
 */


#include <factory/PersistentMemoryFactory.hpp>
#include <memory>
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/timer/Timer.hpp"

namespace common
{
namespace counters
{
class CounterManager;
}  // namespace counters

namespace shutdown_and_enabler
{
class IDSEnabler;
}  // namespace shutdown_and_enabler

namespace memory
{
class PersistentMemoryFactory;
}  // namespace memory

namespace utils
{
class PersistentMap;
}  // namespace utils
}  // namespace common


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
    using CounterManagerPtr          = std::shared_ptr<common::counters::CounterManager>;
    using IdsEnablerPtr              = std::shared_ptr<common::shutdown_and_enabler::IDSEnabler>;
    using PersistentMemoryFactoryPtr = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using TimerPtr               = std::shared_ptr<common::Timer>;

    /**
     * @brief   Constructor a DiagnosticsManager from given CounterManagerPtr countersManager,IdsEnablerPtr idsEnabler, PersistentMemoryFactoryPtr persistentFactory,TimerPtr timer
     * @param   countersManager counters Manager for diagnositcs  
     * @param   idsEnabler ids enable/disable
     * @param   persistentFactory persistentFactory - persistent memory for saving measurement values
     * @param   timer for dtc events 
     */
    DiagnosticsManager(CounterManagerPtr,
                       IdsEnablerPtr,
                       PersistentMemoryFactoryPtr,
                       TimerPtr) {};

    /**
     * @brief   Destructor
     */
    virtual ~DiagnosticsManager() = default;

    /**
     * @brief    default copy constructor
     */
    DiagnosticsManager(const DiagnosticsManager& other) = delete;

    /**
     * @brief    default move constructor
     */
    DiagnosticsManager(DiagnosticsManager&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    DiagnosticsManager& operator=(DiagnosticsManager const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    DiagnosticsManager& operator=(DiagnosticsManager&&) = delete;

    void Init() override;

    /**
     * @brief   Gets auto updated feature flag
     */
    inline std::atomic<bool>& GetFeatureFlag(uint8_t /*adaptationId*/) override;

    void
    updateDiagnosticsOnCrash() override
    {
        LOG_DEBUG << "updateDiagnosticsOnCrash" << LOG_NOOP;
    }

    void
    updateDiagnosticsUDSEvent() override
    {
        LOG_DEBUG << "updateDiagnosticsUDSEvent" << LOG_NOOP;
    }

    void
    UpdateServiceDiscoveryStatus(uint8_t __attribute__ ((unused)) communicatorId, bool __attribute__ ((unused)) serviceDiscoveryStatus) override
    {
        LOG_DEBUG << "UpdateServiceDiscoveryStatus" << LOG_NOOP;
    }

    void
    UpdateServiceRegistyStatus(bool __attribute__ ((unused)) serviceRegistryStatus) override
    {
        LOG_DEBUG << "UpdateServiceDiscoveryStatus" << LOG_NOOP;
    }
};

}  // namespace diagnostics
}  // namespace brain
