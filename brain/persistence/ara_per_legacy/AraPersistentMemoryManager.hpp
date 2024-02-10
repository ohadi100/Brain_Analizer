/**
 * @file        AraPersistentMemoryManager.hpp
 * @brief       This file contains the definition of the AraPersistentMemoryManager class and it's functionality.
 */

#pragma once

#include <cstdint>
#include <memory>
#include <unordered_map>
#include <vector>

#include "PersistentMemoryManagerInterface.hpp"
#include "Noncopyable.hpp"

namespace common
{
namespace memory
{
class PersistentMemoryWatchdog;
class PMWToken;
}  // namespace memory
}  // namespace common

#include <ara/per/keyvaluestorage.h>

namespace brain
{
namespace memory
{
/**
 * @class    AraPersistentMemoryManager
 * @brief    This class is a wrapper calss to a key-value pair based persistent memory.
 * @dataStructure    The class holds a persistent memory DB object
 * @postConditions   The AraPersistentMemoryManager class updates the persistent memory when writing/removing new
 * key-value pairs
 */
class AraPersistentMemoryManager : public common::memory::PersistentMemoryManagerInterface, private common::utils::Noncopyable
{

public:
    using PersistentMemoryWatchdogPtr = std::shared_ptr<common::memory::PersistentMemoryWatchdog>;
    using PMWTokenPtr                 = std::shared_ptr<common::memory::PMWToken>;

    /**
     * @fn       AraPersistentMemoryManager(std::string const& dbName)
     * @brief    Ctor.
     *           Constructs a new key-value pairs persistent memory with the input name.
     * @param    PersistentMemoryWatchdogPtr & watchdog - persistent memory watchdog
     * @param    std::string const& dbName - the name of the newly constructed DB
     * @return   none.
     */
    AraPersistentMemoryManager(PersistentMemoryWatchdogPtr& watchdog, std::string const& dbName);

    /**
     * @fn       virtual ~AraPersistentMemoryManager()
     * @brief    Dtor.
     * @param    none.
     * @return   none.
     */
    virtual ~AraPersistentMemoryManager();

    /**
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    common::types::string const& key - the key to save the new value with
     * @param    uint8_t const* buf - the value to save
     * @return   bool - true if the storing was successful, false if there was not enough memory or the key is not
     * unique
     */
    bool StoreEntry(common::types::string const& key, std::vector<uint8_t> const& buf) override;

    /**
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    common::types::string const&& key - the key to save the new value with
     * @param    uint8_t const* buf - the value to save
     * @return   bool - true if the storing was successful, false if there was not enough memory or the key is not
     * unique
     */
    virtual bool StoreEntry(common::types::string const&& key, std::vector<uint8_t> const& buf) override;

    /**
     * @fn       bool StoreEntry(std::string && key, const uint8_t * buf, uint32_t bufLen)
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    std::string const && key - the key to save the new value with
     * @param    const uint8_t * buf - the value to save
     * @param    uint32_t bufLen - the length of buf
     * @return   TRUE - if the storring was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool StoreEntry(common::types::string const&& key, uint8_t const* buf, uint32_t bufLen) override;

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
     * @fn       bool GetEntry(std::string const& key, uint8_t * buf, uint32_t bufLen)
     * @brief    Retrieves the value stored in the DB with the input key.
     * @param    std::string const& key - the key to get the value of.
     * @param    uint8_t * buf - OUT param - the value of the key is written here
     * @param    uint32_t bufLen - the size of the value with the given key
     * @return   TRUE - if such key was found in the key-value storage
     *           FALSE - if no such key was found in the key-value storage
     */
    bool GetEntry(common::types::string const& key, uint8_t* buf, uint32_t bufLen);

    /**
     * @fn       void GetAllKeys(const std::vector<std::string> & keys)
     * @brief    Retrieves all the keys in the stored key-value DB
     * @param    std::vector<std::string> & keys - OUT param - the keys found will be writtem to this vector
     * @return   none.
     */
    void GetAllKeys(std::vector<std::string>& keys);

    /**
     * @fn       void RemoveEntry(std::vector<std::string> & keys)
     * @brief    Removes the key and it's value from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    std::string & key - the key to remove with it's value
     * @return   none.
     */
    void RemoveEntry(common::types::string const& key) override;

    /**
     * @fn       void GetAllKeys(std::vector<std::string> && keys)
     * @brief    Removes the key and it's value from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    std::string && key - the key to remove with it's value
     * @return   none.
     */
    void RemoveEntry(common::types::string const&& key) override;

    /**
     * @fn       void RemoveAllKeys()
     * @brief    Removes all keys from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    none.
     * @return   none.
     */
    void RemoveAllKeys();

    /**
     * @fn       Disable()
     * @brief    Disable persistent storage.
     * @param    void.
     * @return   void.
     */
    virtual void Disable();

    /**
     * @fn       Enable()
     * @brief    Enable persistent storage.
     * @param    void.
     * @return   void.
     */
    virtual void Enable();

    /**
     * @fn       IsEnabled()
     * @brief    Check if the storage is enabled
     * @param    void.
     * @return   true iff storage is enabled.
     */
    virtual bool IsEnabled();

    /**
     * @fn       virtual bool SaveToFile()
     * @brief    Saves any internaly saved key-value pairs to the persistent memory
     * @param    none.
     * @return   true iff the operation succeed
     */

    virtual bool SaveToFile();

private:
    /**
     * @fn       bool storeEntry(std::string const& key, const uint8_t * buf, uint32_t bufLen)
     * @brief    Internal function to store the new value in the persistent memory with the given key.
     * @param    key - the key to save the new value with
     * @param    buf - the value to save
     * @param    bufLen - the length of buf
     * @return   TRUE - if the storring was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool storeValue(std::string const& key, const uint8_t* buf, uint32_t bufLen);

    /**
     * @fn       void removeEntry(std::string & key)
     * @brief    Internal function to remove the key and it's value from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    std::string & key - the key to remove with it's value
     * @return   none.
     */
    void removeEntry(std::string const& key);

    /**
     * @fn       bool reconnectToDatabase()
     * @brief    Re-open the persistent storage database.
     * @param    none.
     * @return   true iff operation succeed.
     */
    void reconnectToDatabase();

    /**
     * @var      std::unique_ptr<ara::per::KeyValueStorage> m_db
     * @brief    Database pointer
     */
    std::unique_ptr<ara::per::KeyValueStorage> m_db;

    /**
     * @var      bool m_isEnabled
     * @brief    Is data base enabled
     */
    bool m_isEnabled;

    /**
     * @var      std::string m_dbName
     * @brief    Database name
     */
    std::string m_dbName;

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
};
}  // namespace memory
}  // namespace brain
