#pragma once
/**
 * @file
 * @brief     This file contains the definition of the DiagnosticsManagerInterface class
 */

#include <memory>
#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"

namespace brain
{
namespace diagnostics
{
/**
 * @class   DiagnosticsManagerInterface
 * @brief   Initializes and stops all measurement values
 */
class DiagnosticsManagerInterface
{
public:
    using Pointer = std::shared_ptr<DiagnosticsManagerInterface>;

    /**
     * @brief   Constructor
     */
    DiagnosticsManagerInterface() = default;

    /**
     * @brief   Destructor
     */
    virtual ~DiagnosticsManagerInterface() = default;

    /**
     * @brief    default copy constructor
     */
    DiagnosticsManagerInterface(const DiagnosticsManagerInterface& other) = delete;

    /**
     * @brief    default move constructor
     */
    DiagnosticsManagerInterface(DiagnosticsManagerInterface&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    DiagnosticsManagerInterface& operator=(DiagnosticsManagerInterface const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    DiagnosticsManagerInterface& operator=(DiagnosticsManagerInterface&&) = delete;

    /**
     * @brief   Init Diag feature
     */
    virtual void Init() = 0;

    /**
     * @brief   Gets auto updated feature flag
     */
    virtual inline std::atomic<bool>& GetFeatureFlag(uint8_t adaptationId) = 0;

    /**
     * @brief   Updates diagnostic if brain crash
     */
    virtual void updateDiagnosticsOnCrash() = 0;

    /**
     * @brief   Updates diagnostic UDS event
     */
    virtual void updateDiagnosticsUDSEvent() = 0;


    /**
     * @brief   Updates diagnostic discovery status
     */
    virtual void UpdateServiceDiscoveryStatus(uint8_t communicatorId, bool serviceDiscoveryStatus) = 0;

    /**
     * @brief   Updates diagnostic registry status
     */
    virtual void UpdateServiceRegistyStatus(bool serviceRegistryStatus) = 0;
};

}  // namespace diagnostics
}  // namespace brain
