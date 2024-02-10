/**
 * @file
 * @brief     This file contains the definition of the Creditor class and its functionality
*/
#ifndef CREDITOR_HPP
#define CREDITOR_HPP

#include <functional>
#include "brain/config/BrainConfigConstants.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "common/thread_handler/ThreadHandler.hpp"
#include <factory/PersistentMemoryFactory.hpp>
#include "brain/utils/TestsAdapters.hpp"

namespace brain
{
namespace sender
{

constexpr char CREDIT_SAVED[] = "ids_sender_credit";
constexpr char CREDITOR_LAST_UPDATE_SAVED[] = "ids_sender_creditor_update";

/**
 * @class Creditor
 * @brief saves and calculates the amount of credit the system has for sending data to the backend
 */
class Creditor
{

public:
    using PersistentMemoryFactoryPtr = std::shared_ptr<common::memory::PersistentMemoryFactory>;
    using IsRealTimePresentPredicate = std::function<bool(void)>;
    using ConfigurationPtr = common::configuration::Pointer;

    /**
     * @brief   constructor
     * @param   PersistentMemoryFactoryPtr const persistentMemoryFactory - factory for creating persistent memory objects
     * @param   std::shared_ptr<common::counters::CounterManager> debugCounters
     * @param   uint64_t dailyLimitInBytes - daily limit (default BASE_DAILY_CREDIT)
     */
    Creditor(
        PersistentMemoryFactoryPtr const persistentMemoryFactory,
        std::shared_ptr<common::counters::CounterManager> debugCounters,
		ConfigurationPtr config);
    
    /**
     * @brief   destructor
     */
    virtual ~Creditor();
    
    /**
     * @brief    default copy constructor
     */
    Creditor(const Creditor& other) = delete;

    /**
     * @brief    default move constructor
     */
    Creditor(Creditor&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    Creditor& operator=(Creditor const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    Creditor& operator=(Creditor&&) = delete;

    /**
     * @brief   gets the amount of credit left
     * @return  uint64_t the amount of credit available
     */
    VIRTUAL_FOR_TESTS uint64_t GetByteCredit();

    /**
     * @brief   uses credit in various amount
     * @param   uint64_t amountToUse - amount to use
     * @return  true if succeeded , false otherwise (also if we manage to credit only part from the amount to use).
     */
    VIRTUAL_FOR_TESTS bool UseCredit(uint64_t amountToUse);

    /**
     * @brief   Prepare module for shutdown
     */
    void PrepareToShutdown();

    /**
     * @brief   Cancel prepare module for shutdown
     */
    void CancelPrepareToShutdown();

#ifdef TESTS
    /**
     * @brief   if m_isActive is true
     * @return  bool - if m_isActive is true
     */
    inline bool GetIsActive() const noexcept
    {
        return m_isActive;
    }
#endif //TESTS

#ifndef TESTS
private:
#endif // TESTS

    /**
     * @brief   The function set the creditor daily limit and recharging time,
     *          either from configuration file or default.
     */
    void InitCredit(void);

    /**
     * @brief   The function check if the credit suppose to be updated (i.e. refilled).
     *          it checks if 24 hours passed from the prev udpate (@midnight), if so,
     *          the credit will be refilled.
     * @param   time_t curtime - current time in seconds.
     */
    void updateCreditRenewalTime(time_t curtime);

    /**
     * @brief   load last known credit and renewal time from PM (if valid).
     * @return  true if succeeded , false otherwise.
     */
    bool loadFromStorage();

    /**
     * @brief   store to PM  last known credit and renewal time.
     */
    void storeToStorage();

    /* maximum bytes allowed to send in a day */
    uint64_t m_dailyLimitInBytes{};

    /* the time of day in which the credit is re-charged */
    std::tm m_dailyReChargeTime;

    /* current amount of bytes sent */
    uint64_t m_creditLeft;

    /* time in seconds (from epoch) of previous credit renewal */
    time_t m_creditRenewalTime;

    /* time in seconds from last time we stored data to storage */
    time_t m_lastStoreTime;

    std::shared_ptr<common::memory::PersistentMemoryManagerInterface> m_creditorPersistencyStorage;

    bool m_isActive;

    ConfigurationPtr m_config;

    std::vector<std::shared_ptr<common::counters::EventCounter>> m_creditorAvailableCounters;
};

}//namespace sender
}//namespace brain

#endif // CREDITOR_HPP
