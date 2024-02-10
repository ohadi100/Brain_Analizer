#pragma once
/**
 * @file 
 * @brief       This file contains the definition of the AraPersistentMemoryManager class and it's functionality.
 */
#include <mutex>

#include "common/persistent_memory/interface/PersistentMemoryManagerInterface.hpp"
#include "common/persistent_memory/watchdog/PersistentMemoryWatchdog.hpp"
#include "AraPersistentDB/AraPersistentDB.hpp"

#ifdef EEE_PLATFORM
#include "AraPersistentDB/AraPersistentDBEEE.hpp"
#endif

namespace common
{

namespace counters
{
class CounterManager;
}
namespace memory
{
/**
* @class    AraPersistentMemoryManager
* @brief    This class is a wrapper calss to a key-value pair based persistent memory. 
* @dataStructure    The class holds a persistent memory DB object
* @postConditions   The AraPersistentMemoryManager class updates the persistent memory when writing/removing new key-value pairs
*/
class AraPersistentMemoryManager : public  PersistentMemoryManagerInterface, public common::utils::Nonassignable
{
public:

    using PersistentMemoryWatchdogPtr = std::shared_ptr<common::memory::PersistentMemoryWatchdog>;
    using PMWTokenPtr = std::shared_ptr<common::memory::PMWToken>;
    using CounterManagerPtr = std::shared_ptr<common::counters::CounterManager>;

    /**
    * @brief    Ctor.
    *           Constructs a new key-value pairs persistent memory with the input name.
    * @param    PersistentMemoryWatchdogPtr & watchdog - persistent memory watchdog 
    * @param    std::string const& dbName - the name of the newly constructed DB
     * @param    CounterManagerPtr debugCounters
    * @return   none.
    */
    AraPersistentMemoryManager(PersistentMemoryWatchdogPtr watchdog, std::string const& dbName, CounterManagerPtr debugCounters);

    /**
    * @brief    Dtor.
    * @param    none.
    * @return   none.
    */
    virtual ~AraPersistentMemoryManager();

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const& key - the key to save the new value with
    * @param    std::vector<uint8_t> const& buf - the value to save
    * @return   TRUE - if the storring was successful
    *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
    */
    bool StoreEntry(common::types::string const& key, std::vector<uint8_t> const& buf) override;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const&& key - the key to save the new value with
    * @param    std::vector<uint8_t> const& buf - the value to save
    * @return   TRUE - if the storring was successful
    *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
    */
    bool StoreEntry(common::types::string const&& key, std::vector<uint8_t> const& buf) override;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const& key - the key to save the new value with
    * @param    uint8_t const* buf - the value to save
    * @param    uint32_t bufLen - the length of buf
    * @return   TRUE - if the storring was successful
    *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
    */
    bool StoreEntry(common::types::string const& key, uint8_t const* buf, uint32_t bufLen) override;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const&& key - the key to save the new value with
    * @param    uint8_t const* buf - the value to save
    * @param    uint32_t bufLen - the length of buf
    * @return   TRUE - if the storring was successful
    *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
    */
    bool StoreEntry(common::types::string const&& key, uint8_t const* buf, uint32_t bufLen) override;


    /**
    * @brief    Retrieves the value stored in the DB with the input key.
    * @param    common::types::string const& key - the key to get the value of.
    * @param    uint8_t * buf - OUT param - the value of the key is written here
    * @param    uint32_t bufLen - the size of the value with the given key
    * @return   TRUE - if such key was found in the key-value storage
    *           FALSE - if no such key was found in the key-value storage
    */
    bool GetEntry(common::types::string const& key, uint8_t * buf, uint32_t bufLen) override;

    /**
    * @brief    Retrieves all the keys in the stored key-value DB
    * @param    std::vector<common::types::string> & keys - OUT param - the keys found will be writtem to this vector
    * @return   none.
    */
    void GetAllKeys(std::vector<common::types::string> & keys) override;

    /**
    * @brief    Removes the key and it's value from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    common::types::string const& key - the key to remove with it's value
    * @return   none.
    */
    void RemoveEntry(common::types::string const& key) override;

    /**
    * @brief    Removes the key and it's value from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    common::types::string const&& key - the key to remove with it's value
    * @return   none.
    */
    void RemoveEntry(common::types::string const&& key) override;

    /**
    * @brief    Removes all keys from the persistent memory override
    *           No affect, if the key is not found in the key-value storage.
    * @param    none.
    * @return   none.
    */
    void RemoveAllKeys() override;

    /**
    * @brief    Saves any internaly saved key-value pairs to the persistent memory
    * @param    none.
    * @return   true iff the operation succeed.
    */
    bool SaveToFile() override;

#if defined(EEE_PLATFORM) || defined(SIMULATION)
    /**
    * @brief    Determines whether the given key is set in the persistent memory.
    * @param    std::string const& key - the given key to check.
    * @return   bool - true if the key is in the persistent memory, false otherwise.
    */
	bool HasKey(std::string const& key) override;
#endif

    /**
    * @brief    Disable persistent storage.
    * @param    void.
    * @return   void.
    */
    void Disable() override;

    /**
    * @brief    Enable persistent storage.
    * @param    void.
    * @return   void.
    */
    void Enable() override;

    /**
    * @brief    Check if the storage is enabled
    * @param    void.
    * @return   true iff storage is enabled.
    */
    bool IsEnabled() override;
#ifndef TESTS
private:
#endif // TESTS
    /**
    * @brief    Internal function to store the new value in the persistent memory with the given key.
    * @param    key - the key to save the new value with
    * @param    buf - the value to save
    * @return   TRUE - if the storring was successful
    *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
    */
    bool storeValue(common::types::string const& key, std::vector<uint8_t> const& buf);
    
    /**
    * @brief    Internal function to store the new value in the persistent memory with the given key.
    * @param    key - the key to save the new value with
    * @param    buf - the value to save
    * @param    bufLen - The size of the value
    * @return   TRUE - if the storring was successful
    *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
    */
    bool storeValue(common::types::string const& key, uint8_t const* buf, uint32_t bufLen);

    /**
    * @brief    Internal function to remove the key and it's value from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    common::types::string const& key - the key to remove with it's value
    * @return   none.
    */
    void removeValue(common::types::string const& key);

    /**
    * @brief    Re-open the persistent storage database.
    * @param    none.
    * @return   true iff operation succeed.
    */
    void reconnectToDatabase();

    /**
     * @var      std::unique_ptr<common::memory::AraPersistentDB> m_db
     * @brief    Database pointer
     */
    std::unique_ptr<common::memory::AraPersistentDB> m_db;

    /**
     * @var      std::string m_dbName
     * @brief    Database name
     */
    std::string m_dbName;

    /**
     * @var      std::recursive_mutex m_accessLock
     * @brief    DB access synchronization mutex
     */
    std::recursive_mutex m_accessLock;

    /**
     * @var      PersistentMemoryWatchdogPtr m_watchdog
     * @brief    Persistent memory watchdog
     */
    PersistentMemoryWatchdogPtr m_watchdog;

    /**
     * @var      PMWTokenPtr m_token
     * @brief    Database name
     */
    PMWTokenPtr m_token;

    CounterManagerPtr m_debugCounters;
};
} // nm memory
} // nm common
