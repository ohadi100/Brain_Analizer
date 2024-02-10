#pragma once
/**
 * @file 
 * @brief       This file contains the definition of the AraPersistentDB class and it's functionality.
 */
#include <memory>
#include <string>

#include <Logger.hpp>
#include <optional/Optional.hpp>
#include <string.hpp>

#include "interface/PersistentMemoryManagerInterface.hpp"
#include "watchdog/PersistentMemoryWatchdog.hpp"

#ifdef EEE_PLATFORM
#include <ara/per/key_value_storage.h>
#endif

namespace common
{
namespace memory
{
/**
* @class    AraPersistentDB
* @brief    This class is a wrapper calss to a key-value pair based persistent memory. 
* @dataStructure    The class holds a persistent memory DB object
* @postConditions   The AraPersistentDB class updates the persistent memory when writing/removing new key-value pairs
*/
class AraPersistentDB : public common::utils::Nonassignable
{
public:

#if defined(EEE_PLATFORM)
    using KvsType = ara::per::KvsType;
#endif
public:

    /**
    * @brief    move Ctor. 
    *           The calss is unmoveable.
    * @param    AraPersistentDB && other - the AraPersistentDB object to move from
    * @return   none.
    */
    AraPersistentDB(AraPersistentDB &&) = default;

    /**
    * @brief    Dtor.
    * @param    none.
    * @return   none.
    */
    virtual ~AraPersistentDB() = default;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const& key - the key to save the new value with
    * @param    std::vector<uint8_t> const& data - The data to write
    * @return   bool - iff successful
    */
    virtual bool SetValue(common::types::string const& key, std::vector<uint8_t> const& data) = 0;

    /**
    * @brief    Stores the new value in the persistent memory with the given key.
    * @param    common::types::string const& key - the key to save the new value with
    * @param    uint8_t const* buf -  The data to write
    * @param    uint32_t bufLen - The length of the data
    * @return   bool - iff successful
    */
    virtual bool SetValue(common::types::string const& key, uint8_t const* buf, uint32_t bufLen) = 0;

    /**
    * @brief    Retrieves the value stored in the DB with the input key.
    * @param    common::types::string const& key - the key to get the value of.
    * @param    uint8_t* buf - buffer to write stored value in to.
    * @param    uint32_t bufLen - buffer length for the received buffer
    * @return   bool - iff successful
    */
    virtual bool GetValue(common::types::string const& key, uint8_t* buf, uint32_t bufLen) = 0;

    /**
    * @brief    Retrieves all the keys in the stored key-value DB
    * @param    none.
    * @return   cm::optional<std::vector<common::types::string>>
    */
    virtual cm::optional<std::vector<common::types::string>> GetAllKeys() = 0;

    /**
    * @brief    Removes the key and it's value from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    common::types::string const& key - the key to remove with it's value
    * @return   bool - iff successful.
    */
    virtual bool RemoveKey(common::types::string const& key) = 0;

    /**
    * @brief    Removes all keys from the persistent memory
    *           No affect, if the key is not found in the key-value storage.
    * @param    none.
    * @return   bool - iff sucessful.
    */
    virtual bool RemoveAllKeys() = 0;

    /**
    * @brief    Syncs the db to the storage
    * @param    none.
    * @return   bool - iff successful.
    */
    virtual bool SyncToStorage() = 0;

    /**
    * @brief    Determines whether the given key is set in the persistent memory.
    * @param    std::string const& key - the given key to check.
    * @return   bool - true if the key is in the persistent memory, false otherwise.
    */
	virtual bool HasKey(std::string const& key) = 0;

protected:
    
    /**
    * @brief    Default constructor
    *           The calss must have a name.
    * @param    none.
    * @return   none.
    */
    AraPersistentDB() = default;
};

} // nm memory
} // nm common
