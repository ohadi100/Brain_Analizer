/**
 * @file      PassedDroppedAlertsNanoPB.hpp
 * @brief     This file contains helper structs and functions for serializing passed droppped alters
 */

#ifndef PASEED_DROPPED_ALERTS_NANOPB_HPP
#define PASEED_DROPPED_ALERTS_NANOPB_HPP

#include <string>
#include <vector>
#include "autogen/nanopb/NanoPbInclude.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{
namespace nanopb
{

using PassedDroppedAlertsDataNPB = com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedAlertsData;

using SecEventAlertPassedDroppedCountersNPB
    = com_vwg_connect_ids_idsperiodicreport_v1_SecEventAlertPassedDroppedCounters;
using PassedDroppedCountersNPB = com_vwg_connect_ids_idsperiodicreport_v1_PassedDroppedCounters;
using DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCountersNPB
    = com_vwg_connect_ids_idsperiodicreport_v1_DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters;

class SecEventAlertPassedDroppedCounters : public SecEventAlertPassedDroppedCountersNPB
{
public:
    SecEventAlertPassedDroppedCounters();
    /**
     * @brief default destructor
     */
    ~SecEventAlertPassedDroppedCounters() = default;

    SecEventAlertPassedDroppedCounters(const SecEventAlertPassedDroppedCounters&) = delete;
    SecEventAlertPassedDroppedCounters(SecEventAlertPassedDroppedCounters&& rhs) noexcept;

    /**
    * @brief    default copy assignment operator
    */
    SecEventAlertPassedDroppedCounters& operator=(SecEventAlertPassedDroppedCounters const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    SecEventAlertPassedDroppedCounters& operator=(SecEventAlertPassedDroppedCounters&&) = delete;
};

class DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters
  : public DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCountersNPB
{
public:
    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters();
    /**
     * @brief default destructor
     */
    ~DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters() = default;

    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters(
        const DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters&)
        = delete;
    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters(
        DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters&& rhs) noexcept;

    /**
     * @brief    default copy assignment operator
     */
    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters& operator=(
        DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters const&)
        = delete;

    /**
     * @brief   default move assignment operator
     */
    DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters& operator=(
        DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters&&)
        = delete;

    void PrepareForSerialization();

    std::string ConstraintId;
};

class PassedDroppedCounters : PassedDroppedCountersNPB
{
public:
    PassedDroppedCounters();
    /**
     * @brief default destructor
     */
    ~PassedDroppedCounters() = default;

    PassedDroppedCounters(const PassedDroppedCounters&) = delete;
    PassedDroppedCounters(PassedDroppedCounters&& rhs) noexcept;

    /**
    * @brief    default copy assignment operator
    */
    PassedDroppedCounters& operator=(PassedDroppedCounters const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    PassedDroppedCounters& operator=(PassedDroppedCounters&&) = delete;
};

class PassedDroppedAlertsData : public PassedDroppedAlertsDataNPB
{
public:
    PassedDroppedAlertsData();

    /**
     * @brief default destructor
     */
    ~PassedDroppedAlertsData() = default;

    PassedDroppedAlertsData(PassedDroppedAlertsData&& rhs) noexcept;
    PassedDroppedAlertsData(PassedDroppedAlertsData const& rhs) = delete;

    /**
    * @brief    default copy assignment operator
    */
    PassedDroppedAlertsData& operator=(PassedDroppedAlertsData const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    PassedDroppedAlertsData& operator=(PassedDroppedAlertsData&&) = delete;

    void PrepareForSerialization();

    inline void Clear()
    {
        CriticalSecurityEventAlertPassedDroppedCounters.clear();
        UnknownEventIdAlertPassedDroppedCounters.clear();
        DhmIncidentWithUnknownConstraintIdAlertCounters.clear();
    }

    std::vector<SecEventAlertPassedDroppedCounters> CriticalSecurityEventAlertPassedDroppedCounters;
    std::vector<SecEventAlertPassedDroppedCounters> UnknownEventIdAlertPassedDroppedCounters;
    std::vector<DhmIncidentWithUnknownConstraintIdAlertPassedDroppedCounters>
        DhmIncidentWithUnknownConstraintIdAlertCounters;
};
}  // namespace nanopb
}  // namespace security_events
}  // namespace engines
}  // namespace brain

#endif