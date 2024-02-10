/**
 * @file
 * @brief    This file contains the definition of DiagFeatureFlags.
 */
#ifndef DIAG_FEATURE_FLAGS_HANDLER_HPP
#define DIAG_FEATURE_FLAGS_HANDLER_HPP

#include <sourcecode/dal/ids/GeneratedDiagnosticAccessor.h>

#include "brain/diagnostics/PPE/AdaptationValuesConstants.hpp"
#include "brain/diagnostics/dtc/DtcEvent.hpp"
#include "common/shutdown_and_enabler/ids_enabler/IDSEnabler.hpp"
#include "common/utils/logger/Logger.hpp"

#include <array>
#include <atomic>

namespace brain
{
namespace diagnostics
{
namespace diag_accessor
{

/**
 * @brief Handler for reading Adaption & DataSet values using DAL.
 */
class DiagFeatureFlags : public common::utils::Nonassignable
{
public:
    using IdsEnablerPtr                  = std::shared_ptr<common::shutdown_and_enabler::IDSEnabler>;
    using AdaptationId                   = brain::adaptation_values_names::AdaptationId;
    using GeneratedDiagnosticAccessorPtr = std::shared_ptr<vwg::dal::GeneratedDiagnosticAccessor>;

    using SpecificFeatureAccessorFunc
        = vwg::dal::Either<vwg::dal::Error, bool> (vwg::dal::GeneratedDiagnosticAccessor::*)();
    using CallbackFunc = std::function<void(DiagFeatureFlags&)>;

    /**
     * @brief   Constructor
     * @param   IdsEnablerPtr idsEnabler
     * @param   GeneratedDiagnosticAccessorPtr diagnosticAccessor
     */
    DiagFeatureFlags(IdsEnablerPtr idsEnabler);
    virtual ~DiagFeatureFlags();

    /**
     * @brief    default copy constructor
     */
    DiagFeatureFlags(const DiagFeatureFlags& other) = delete;

    /**
     * @brief    default move constructor
     */
    DiagFeatureFlags(DiagFeatureFlags&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    DiagFeatureFlags& operator=(DiagFeatureFlags const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    DiagFeatureFlags& operator=(DiagFeatureFlags&&) = delete;

    /**
     * @brief   Registers diagAccessor by settings hash changed callback for adaptations and dataSets
     */
    void RegisterDiagAccessor();

    /**
     * @brief   Gets auto updated feature flag
     * @return  bool& - auto updated feature flag
     */
    inline std::atomic<bool>&
    GetFeatureFlag(AdaptationId const adaptationId)
    {
        if (adaptationId < AdaptationId::ADAPTATIONS_COUNT)
        {
            return m_featureFlags[adaptationId];
        }

        LOG_ERROR << "Invalid adaptation id %d supplied" << static_cast<uint8_t>(adaptationId) << LOG_NOOP;
        static std::atomic<bool> rc{false};
        return rc;
    }

    /**
     * @brief Get the Data Implausible Dtc object
     * @return brain::diagnostics::dtc::DtcEvent const& - get dtc event
     */
    inline brain::diagnostics::dtc::DtcEvent const&
    GetDataImplausibleDtc() const
    {
        return m_dataImplausibleDtc;
    }

    /**
     * @brief load the diagnostic data from diagnostic module
     */
    void LoadDiagnosticData();

private:
    void hashChangedCallback(vwg::dal::HashType const&,
                             vwg::dal::DiagnosticDataNamespace diagDataNamespace,
                             vwg::dal::DataIds const&          changedDids);

    void adaptationHashChangedCallback(vwg::dal::DataIds const& changedDids);

    void dataSetHashChangedCallback(vwg::dal::DataIds const& changedDids);

    void handleEnablingSpecificFeaturesAdaption();

    static std::function<void(DiagFeatureFlags&)>
    createUpdateFeatureCallback(SpecificFeatureAccessorFunc specificFeatureGetter, AdaptationId const adaptationId)
    {
        return [specificFeatureGetter, adaptationId](DiagFeatureFlags& diagFeatureFlagsInstance) {
            diagFeatureFlagsInstance.updateSpecificFeature(
                (diagFeatureFlagsInstance.m_diagnosticAccessor.*specificFeatureGetter)(), adaptationId);
        };
    }

    void updateSpecificFeature(vwg::dal::Either<vwg::dal::Error, bool> specificFeatureResult,
                               AdaptationId const                      adaptationId);

    void handleIntrusionDetectionSystemAdaptation();

    void handleIntrusionDetectionSystemDataSet();

    bool parseIntrusionDetectionSystemDataSet(vwg::dal::DiagnosticData const& value);

    void updateIdsMode(bool const idsMode);

    vwg::dal::GeneratedDiagnosticAccessor m_diagnosticAccessor{};
    std::atomic<vwg::dal::State>          m_dalState;

    IdsEnablerPtr m_idsEnabler;

    static constexpr size_t                                 SPECIFIC_FEATURE_COUNT = 10U;
    static std::array<CallbackFunc, SPECIFIC_FEATURE_COUNT> m_specificFeatureHandlers;

    std::array<std::atomic<bool>, static_cast<size_t>(AdaptationId::ADAPTATIONS_COUNT)> m_featureFlags;

    brain::diagnostics::dtc::DtcEvent m_dataImplausibleDtc;
};

}  // namespace diag_accessor
}  // namespace diagnostics
}  // namespace brain

#endif  // DIAG_FEATURE_FLAGS_HANDLER_HPP