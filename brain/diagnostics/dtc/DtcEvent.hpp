/**
* @file
* @brief    This file contains the definition of DtcEvent.
*/
#ifndef DTC_EVENT_HPP
#define DTC_EVENT_HPP


#include "CPP/optional/Optional.hpp"
#include "CPP/Nonassignable.hpp"
#include <ara/diag/monitor.h>
#include <ara/diag/app_ids.h>


namespace brain
{
namespace diagnostics
{
namespace dtc
{

using MonitorActionType = ::ara::diag::Monitor::MonitorAction;

/**
 * @class  DtcEvent
 * @brief  Sends dtcEvents
 */
class DtcEvent : public common::utils::Nonassignable
{
public:

    /**
      * @brief    Constructor
      * @param    instanceId
      */
    explicit DtcEvent(ara::core::InstanceSpecifier const& instanceId, bool const resetEnabled=true);
    /**
     * @brief   Destructor
     */
    virtual ~DtcEvent() = default;

    /**
     * @brief    default copy constructor
     */
    DtcEvent(const DtcEvent& other) = delete;

    /**
     * @brief    default move constructor
     */
    DtcEvent(DtcEvent&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    DtcEvent& operator=(DtcEvent const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    DtcEvent& operator=(DtcEvent&&) = delete;

    /**
     * @brief    Sets Dtc event status
     * @param    bool const status
     */
    void SetEvent(bool const status);

#ifdef TESTS
    virtual void publishMonitorEventToDM();
#else
private:
    void publishMonitorEventToDM();
#endif

    void monitorInitCallback(ara::diag::Monitor::InitMonitorReason reason);

    bool m_resetEnabled;
    cm::optional<ara::diag::Monitor> m_monitor;

#ifndef TESTS
protected:
#endif

    bool m_currentDtcStatus;
};
} // namespace dtc
} // namespace diagnostics
} // namespace brain

#endif // DTC_EVENT_HPP
