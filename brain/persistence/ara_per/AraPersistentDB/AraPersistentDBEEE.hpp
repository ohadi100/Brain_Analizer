#pragma once
/**
 * @file 
 * @brief       This file contains the definition of the AraPersistentDBEEE class and it's functionality.
 */
#include <CounterManager.hpp>

#include "AraPersistentDB.hpp" // extended

namespace common
{
namespace memory
{
/**
* @class    AraPersistentDBEEE
* @brief    This class is a wrapper calss to a key-value pair based persistent memory. 
* @dataStructure    The class holds a persistent memory DB object
* @postConditions   The AraPersistentDBEEE class updates the persistent memory when writing/removing new key-value pairs
*/
class AraPersistentDBEEE : public AraPersistentDB
{
public:
    using CounterManagerPtr = common::counters::CounterManagerPtr;
    
    /**
    * @brief    Ctor.
    *           Constructs a new key-value pairs persistent memory with the input name.
    * @param    std::string const& dbName - the name of the newly constructed DB
     * @param    CounterManagerPtr debugCounters
    * @return   none.
    */
    AraPersistentDBEEE(std::string const& dbName, CounterManagerPtr debugCounters);

    AraPersistentDBEEE(AraPersistentDBEEE &&) = default;
    
    /**
    * @brief    Dtor.
    * @param    none.
    * @return   none.
    */
    virtual ~AraPersistentDBEEE() override;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const& key - the key to save the new value with
    * @param    std::vector<uint8_t> const& data - The data to write
    * @return   bool - iff successful
    */
    virtual bool SetValue(common::types::string const& key, std::vector<uint8_t> const& data) override;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const& key - the key to save the new value with
    * @param    uint8_t const* buf -  The data to write
    * @param    uint32_t bufLen - The length of the data
    * @return   bool - iff successful
    */
    virtual bool SetValue(common::types::string const& key, uint8_t const* buf, uint32_t bufLen) override;

    /**
    * @brief    Retrieves the value stored in the DB with the input key.
    * @param    common::types::string const& key - the key to get the value of.
    * @param    uint8_t* buf - buffer to write stored value in to.
    * @param    uint32_t bufLen - buffer length for the received buffer
    * @return   bool - iff successful
    */
    virtual bool GetValue(common::types::string const& key, uint8_t* buf, uint32_t bufLen) override;

    /**
    * @brief    Retrieves all the keys in the stored key-value DB
    * @param    none.
    * @return   cm::optional<std::vector<common::types::string>>
    */
    virtual cm::optional<std::vector<common::types::string>> GetAllKeys() override;

    /**
    * @brief    Removes the key and it's value from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    common::types::string const& key - the key to remove with it's value
    * @return   bool - iff successful.
    */
    virtual bool RemoveKey(common::types::string const& key) override;

    /**
    * @brief    Removes all keys from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    none.
    * @return   bool - iff sucessful.
    */
    virtual bool RemoveAllKeys() override;

    /**
    * @brief    Syncs the db to the storage
    * @param    none.
    * @return   bool - iff successful.
    */
    virtual bool SyncToStorage() override;

    /**
    * @brief    Determines whether the given key is set in the persistent memory.
    * @param    const std::string& key - the given key to check.
    * @return   bool - true if the key is in the persistent memory, false otherwise.
    */
	bool HasKey(const std::string& key) override;

private:
    
    /**
    * @brief    Default constructor
    *           The calss must have a name.
    * @param    none.
    * @return   none.
    */
    AraPersistentDBEEE() = delete;

    /**
    * @brief    Initializes m_db member
    * @param    std::string const& dbName - db name 
    * @return   bool - true if managed to initialize, otherwise false
    */
    bool InitializeDB(std::string const& dbName);

    /**
     * @var      SharedHandle<ara::per::KeyValueStorage> m_db
     * @brief    Database pointer
     */
    ara::per::SharedHandle<ara::per::KeyValueStorage> m_db;

    // counters
    CounterManagerPtr m_debugCounters;
    std::shared_ptr<common::counters::EventCounter> m_errorSetPM;
    std::shared_ptr<common::counters::EventCounter> m_errorSyncPM;

};
} // nm memory
} // nm common
