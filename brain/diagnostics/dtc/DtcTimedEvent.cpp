/**
 * @file
 * @brief    This file contains the implementation of DtcTimedEvent.
 */
#include "DtcTimedEvent.hpp"
#include <Logger.hpp>


using brain::diagnostics::dtc::DtcTimedEvent;
using common::Timer;


void DtcTimedEvent::updateConditionStatus(bool const newConditionStatus)
{
    if (newConditionStatus == m_conditionStatus)
    {
        return;
    }

    if (common::Timer::INVALID_TIMER_REGISTRATION_KEY != m_qualificationTimerKey)
    {
        std::ignore             = m_timer->Deregister(m_qualificationTimerKey);
        m_qualificationTimerKey = common::Timer::INVALID_TIMER_REGISTRATION_KEY;
    }

    m_conditionStatus = newConditionStatus;

    if (newConditionStatus == m_currentDtcStatus)
    {
        return;
    }

    uint64_t const qualificationTimeout = newConditionStatus ? m_qualificationTime : m_suspensionTime;
    m_qualificationTimerKey = m_timer->Register(common::S_TO_MS(qualificationTimeout), [this, newConditionStatus]()
    {
        SetEvent(newConditionStatus);
        m_qualificationTimerKey = common::Timer::INVALID_TIMER_REGISTRATION_KEY;
    }, false);

    if (0xFFFFU == m_qualificationTimerKey)
    {
        m_qualificationTimerKey = common::Timer::INVALID_TIMER_REGISTRATION_KEY;
        LOG_WARNING << "Failed to register timer for dtc qualification check function" << LOG_NOOP;
    }
}
