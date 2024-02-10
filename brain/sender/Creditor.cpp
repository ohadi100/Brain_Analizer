/**
 * @file
 * @brief       This file contains the functionality of the Creditor class
*/
#include "brain/sender/Creditor.hpp"
#include <DBNames.hpp>
#include <iomanip>
#include <sstream>

#include <DBNames.hpp>

#include "common/configuration/Configuration.hpp"
#include "common/counter_manager/CounterNames.hpp"
#include "common/utils/logger/Logger.hpp"
#include "common/utils/os/time/Time.hpp"

#include "Creditor.hpp"

using brain::sender::Creditor;
using namespace common::memory;

namespace brain
{
namespace sender
{
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;
}
}  // namespace brain

Creditor::Creditor(
    PersistentMemoryFactoryPtr persistentMemoryFactory,
    std::shared_ptr<common::counters::CounterManager> debugCounters,
    ConfigurationPtr config) :
    m_creditRenewalTime(0), /* initialize the last known renewal time to 0 as default (will get updated by updateCreditRenewalTime */
    m_lastStoreTime(0), /* initialize the last known time we store data top persistent memory */
    m_creditorPersistencyStorage(persistentMemoryFactory->CreatePersistentMemory(PER_MEM_IDS_BRAIN_CREDITOR)),
    m_isActive(true),
    m_config(config)
{
    InitCredit();

    m_creditLeft = m_dailyLimitInBytes;

    m_creditorPersistencyStorage->Enable();

    /* update the last time credit was refilled */
    updateCreditRenewalTime(static_cast<time_t>(common::Time::GetCurrentTimeSec()));

    /* load data from storage if valid */
    std::ignore = loadFromStorage();

    /* create and update AVAILABLE_CREDIT counter */
    m_creditorAvailableCounters.emplace_back(debugCounters->CreateCounter(common::counters::info::AVAILABLE_CREDIT(0), EventCounterLevelType::COUNTER_INFO));
    m_creditorAvailableCounters[0]->SetEventCounter(m_creditLeft);

    LOG_INFO << "Creditor: credit " << m_creditLeft << " renewal-time " << m_creditRenewalTime << LOG_NOOP;
}

Creditor::~Creditor()
{
    try
    {
        if (m_isActive)
        {
            PrepareToShutdown();
        }
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the Creditor failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

void Creditor::InitCredit(void)
{
    uint32_t dailyLimitInBytes{};
    std::string dailyReChargeTime;
    std::ostringstream oss;

    if (!m_config->GetValue(brain::config_keys::CREDIT_DAY_LIMIT_BYTES, dailyLimitInBytes))
    {
        m_dailyLimitInBytes = common::BASE_DAILY_CREDIT;
    }
    else
    {
        m_dailyLimitInBytes = dailyLimitInBytes;
    }

    if (!m_config->GetValue(brain::config_keys::CREDIT_RECHARGE_TIME_IN_DAY, dailyReChargeTime))
    {
        m_dailyReChargeTime.tm_hour = 0;
        m_dailyReChargeTime.tm_min = 0;
        m_dailyReChargeTime.tm_sec = 0;
    }
    else
    {
        std::istringstream ss(dailyReChargeTime.c_str());
        ss >> std::get_time(&m_dailyReChargeTime, "%H:%M:%S");
    }

    oss << std::put_time(&m_dailyReChargeTime, "%H:%M:%S");
    LOG_INFO << "Creditor: init credit " << m_dailyLimitInBytes << " renewal-time " << oss.str() << LOG_NOOP;
}

uint64_t Creditor::GetByteCredit()
{
    /* check if we need to renew the credit */
    updateCreditRenewalTime(static_cast<time_t>(common::Time::GetCurrentTimeSec()));

    LOG_INFO << "Creditor: credit " << m_creditLeft << LOG_NOOP;

    return m_creditLeft;
}

bool Creditor::UseCredit(uint64_t amountToUse)
{
    bool isCreditUsed = false;
    /* check if we have enough credit */
    if (m_creditLeft < amountToUse)
    {
        LOG_DEBUG << "Creditor: not enough credit " << m_creditLeft << LOG_NOOP;
    }
    else
    {
        // reduce used size from credit
        m_creditLeft -= amountToUse;
        LOG_INFO << "Creditor: used " << amountToUse << " credit " << m_creditLeft << LOG_NOOP;
        isCreditUsed = true;

        // update the counter
        if (m_creditorAvailableCounters[0])
        {
            m_creditorAvailableCounters[0]->SetEventCounter(m_creditLeft);
        }

        time_t curtime = static_cast<time_t>(common::Time::GetCurrentTimeSec());
        if (curtime < m_lastStoreTime)
        {
            LOG_WARNING << "Creditor: system time is not synchronize with last Stored time" << LOG_NOOP;
        }
        else if (static_cast<uint64_t>(curtime - m_lastStoreTime) >= common::STORAGE_UPDATE_TIME_SECONDS)
        {
            /* store to storage every 60 secs */
            storeToStorage();
            m_lastStoreTime = curtime;
        }
    }

    return isCreditUsed;
}

void Creditor::PrepareToShutdown()
{
    LOG_INFO << "Creditor: Prepare to shutdown" << LOG_NOOP;
    m_isActive = false;
    storeToStorage();
    m_creditorPersistencyStorage->Disable();
}

void Creditor::CancelPrepareToShutdown()
{
    LOG_INFO << "Creditor: Cancel prepare to shutdown" << LOG_NOOP;
    m_creditorPersistencyStorage->Enable();
    std::ignore = loadFromStorage();
    m_isActive = true;
}

void Creditor::updateCreditRenewalTime(time_t curtime)
{
    std::tm tmCreditRenewal{};
    time_t m_prevCreditRenewalTime = m_creditRenewalTime;
    std::ostringstream oss;

    /* check if the current time is smaller then last known renewal time.
     * if so, something is wrong with the system time, cuases can be:
     * 1. manually updated to past time
     * 2. system was booted with past time (not yet synced with gps).
     * in such case no update will take place and we continue with current
     * know values */
    if (curtime < m_creditRenewalTime)
    {
        LOG_WARNING << "Creditor: system timer error - current time is not later then last known renewal time"
                    << LOG_NOOP;
        return;
    }

    /* check if 24Hrs or more passed since last renewal time */
    if ((curtime - m_creditRenewalTime) <= static_cast<time_t>(common::NUM_OF_SEC_IN_DAY))
    {        
        return;
    }

    LOG_DEBUG << "Creditor: 24Hrs or more passed since last renewal time." << LOG_NOOP;

    /* convert time in secs (time_t) to tm struct */
    std::ignore = gmtime_r(&curtime, &tmCreditRenewal); /* TODO: add to TIME classs */

    /* zero the secs, mins & hours, i.e. midnight */
    tmCreditRenewal.tm_sec = m_dailyReChargeTime.tm_sec;
    tmCreditRenewal.tm_min = m_dailyReChargeTime.tm_min;
    tmCreditRenewal.tm_hour = m_dailyReChargeTime.tm_hour;

    /* convert tm struct to time in secs (time_t) */
    m_creditRenewalTime = timegm(&tmCreditRenewal);

    /* try to load data from storage */
    if (!loadFromStorage())
    {
        /* only update the credit if m_prevCreditRenewalTime is set.
         * if it isn't set, that means only clock update occurred so we
         * want to keep the credit value, not update it */
        if (m_prevCreditRenewalTime)
        {
            m_creditLeft = m_dailyLimitInBytes;
        }

        storeToStorage();
    }

    oss << std::put_time(&tmCreditRenewal, "%d-%m-%Y %H:%M:%S");
    LOG_INFO << "Creditor: update credit " << m_creditLeft << " renewal-time " << m_creditRenewalTime << " ("
             << oss.str() << ")" << LOG_NOOP;
}

bool Creditor::loadFromStorage()
{
    uint64_t storedCreditLeft = 0;
    time_t storedCreditRenewalTime = 0;

    if (!m_creditorPersistencyStorage->GetEntry(
        CREDIT_SAVED,
        reinterpret_cast<uint8_t*>(&storedCreditLeft),
        sizeof(storedCreditLeft)))
    {
        LOG_DEBUG << "Creditor: failed loading [" << CREDIT_SAVED << "]" << LOG_NOOP;
        return false;
    }

    if (!m_creditorPersistencyStorage->GetEntry(
        CREDITOR_LAST_UPDATE_SAVED,
        reinterpret_cast<uint8_t*>(&storedCreditRenewalTime),
        sizeof(storedCreditRenewalTime)))
    {
        LOG_DEBUG << "Creditor: failed loading [" << CREDITOR_LAST_UPDATE_SAVED << "]" << LOG_NOOP;
        return false;
    }

    /* if creditRenewalTime exists but is in the future, set credit to zero.
     * we dont know the current time but we know that we run in the past, dont take
     * chances and set credit to 0. */
    if (storedCreditRenewalTime > m_creditRenewalTime)
    {
        LOG_INFO << "current RenewalTime (" << m_creditRenewalTime << ") in past (stored credit RT "
                 << storedCreditRenewalTime << ")" << LOG_NOOP;
        m_creditLeft = 0;
        return true;
    }

    /* if creditRenewalTime exists but is in the past, irrelevant */
    if (storedCreditRenewalTime < m_creditRenewalTime)
    {
        LOG_DEBUG << "Creditor: irrelevant stored data ... current RenewalTime (" << m_creditRenewalTime
                  << ") in future (stored credit RT " << storedCreditRenewalTime << "), set credit to 0" << LOG_NOOP;
        return false;
    }

    /* update credit with stored value */
    m_creditLeft = storedCreditLeft;

    LOG_INFO << "Creditor: finished loading from storage. credit = " << m_creditLeft << ", time " << m_creditRenewalTime
             << LOG_NOOP;

    return true;
}

void Creditor::storeToStorage()
{
    if (!m_creditorPersistencyStorage->IsEnabled())
    {
        LOG_WARNING << "Creditor persistent memory is disabled" << LOG_NOOP;
        return;
    }

    if (!m_creditorPersistencyStorage->StoreEntry(
        CREDIT_SAVED,
        reinterpret_cast<const uint8_t*>(&m_creditLeft),
        sizeof(m_creditLeft)))
    {
        LOG_ERROR << "Creditor: failed to set [" << CREDIT_SAVED << "] to storage" << LOG_NOOP;
        return;
    }

    if (!m_creditorPersistencyStorage->StoreEntry(
        CREDITOR_LAST_UPDATE_SAVED,
        reinterpret_cast<const uint8_t*>(&m_creditRenewalTime),
        sizeof(m_creditRenewalTime)))
    {
        LOG_ERROR << "Creditor: failed to set [" << CREDITOR_LAST_UPDATE_SAVED << "] to storage" << LOG_NOOP;
        return;
    }

    if (!m_creditorPersistencyStorage->SaveToFile())
    {
        LOG_ERROR << "Creditor failed to save credit and timestamp to persistent memory" << LOG_NOOP;
        return;
    }

    LOG_INFO << "Creditor: finished storing to storage. credit = " << m_creditLeft << ", time " << m_creditRenewalTime
             << LOG_NOOP;
}
