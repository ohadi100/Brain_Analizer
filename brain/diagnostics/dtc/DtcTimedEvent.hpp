/**
 * @file
 * @brief    This file contains the definition of DtcTimeEvent.
 */
#ifndef DTC_TIME_QUALIFIED_EVENT_HPP
#define DTC_TIME_QUALIFIED_EVENT_HPP

#include "DtcEvent.hpp"
#include "common/utils/timer/Timer.hpp"


namespace brain
{
namespace diagnostics
{
namespace dtc
{

/**
 * @class   DtcTimedEvent
 * @brief   Manages DtcEvent with qualification time check
 *          Dtc event updates to true (failed) if qualification time passes.
 *          Dtc event updated to false (passed) if suspension time passes.
 */
class DtcTimedEvent : public DtcEvent
{
public:

using TimerRegisterKey = common::Timer::TimerRegisterKey;
using TimerPtr = std::shared_ptr<common::Timer>;

    /**
      * @brief      Constructor
      * @param      ara::core::InstanceSpecifier instanceId
      * @param      TimerPtr timer - used to register for qualification time check
      * @param      uint64_t const qualificationTime - Time to wait before setting Dtc event status from false to true.
      * @param      uint64_t const suspensionTime - Time to wait before resseting Dtc event status from true to false.
      */
    DtcTimedEvent(ara::core::InstanceSpecifier instanceId, TimerPtr timer, uint64_t const qualificationTime, uint64_t const suspensionTime):
        DtcEvent(instanceId, false),
        m_conditionStatus(false),
        m_qualificationTime(qualificationTime),
        m_suspensionTime(suspensionTime),
        m_timer(timer),
        m_qualificationTimerKey(common::Timer::INVALID_TIMER_REGISTRATION_KEY)
    {}

#ifndef TESTS
protected:
#endif
    
    /**
     * @brief   Updates dtc status.
     *          Starts timer to check if qualification time passed, before updating Dtc event.
     * @param   bool const newConditionStatus
     */
#ifdef TESTS
    virtual
#endif
    void updateConditionStatus(bool const newConditionStatus);

    bool m_conditionStatus;

#ifndef TESTS
private:
#endif

    uint64_t m_qualificationTime;
    uint64_t m_suspensionTime;

    TimerPtr m_timer;
    TimerRegisterKey m_qualificationTimerKey;
};

} // namespace dtc
} // namespace diagnostics
} // namespace brain

#endif // DTC_TIME_QUALIFIED_EVENT_HPP
