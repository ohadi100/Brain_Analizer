#pragma once
/**
 * @file
 * @brief       This file contains the definition of the PersistentMemoryManager class and its functionality.
 */
#include <mutex>
#include "common/persistent_memory/interface/PersistentMemoryManagerInterface.hpp"
#include "common/utils/CPP/Nonassignable.hpp"

namespace common
{
namespace memory
{
/**
 * @class    PersistentMemoryManager
 * @brief    This class is a wrapper class to a key-value pair based persistent memory.
 * @dataStructure    The class holds a persistent memory DB object
 * @postConditions   The PersistentMemoryManager class updates the persistent memory when writing/removing new key-value
 * pairs
 */
class FsPersistentMemoryManager
  : public PersistentMemoryManagerInterface
  , public common::utils::Nonassignable
{
public:
    /**
     * @brief    Ctor.
     *           Constructs a new key-value pairs persistent memory with the input name.
     * @param    dbName - the name of the newly constructed DB
     * @return   none.
     */
    explicit FsPersistentMemoryManager(std::string const& dbName);

    /**
     * @brief    Dtor.
     * @param    none.
     * @return   none.
     */
    virtual ~FsPersistentMemoryManager();

    /**
     * @brief    default copy constructor
     */
    FsPersistentMemoryManager(const FsPersistentMemoryManager& other) = delete;

    /**
     * @brief    default move constructor
     */
    FsPersistentMemoryManager(FsPersistentMemoryManager&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    FsPersistentMemoryManager& operator=(FsPersistentMemoryManager const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    FsPersistentMemoryManager& operator=(FsPersistentMemoryManager&&) = delete;

    /**
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    key - the key to save the new value with
     * @param    buf - the value to save
     * @return   TRUE - if the storring was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool StoreEntry(std::string const& key, std::vector<uint8_t> const& buf) override;

    /**
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    key - the key to save the new value with
     * @param    buf - the value to save
     * @return   TRUE - if the storring was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool StoreEntry(std::string const&& key, std::vector<uint8_t> const& buf) override;

    /**
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    key - the key to save the new value with
     * @param    buf - the value to save
     * @param    bufLen - the length of buf
     * @return   TRUE - if the storring was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool StoreEntry(std::string const& key, uint8_t const* buf, uint32_t bufLen) override;

    /**
     * @brief    Stores the new value in the persistent memory with the given key.
     * @param    key - the key to save the new value with
     * @param    buf - the value to save
     * @param    bufLen - the length of buf
     * @return   TRUE - if the storring was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool StoreEntry(std::string const&& key, uint8_t const* buf, uint32_t bufLen) override;


    /**
     * @brief    Retrieves the value stored in the DB with the input key.
     * @param    key - the key to get the value of.
     * @param    buf - OUT param - the value of the key is written here
     * @param    bufLen - the size of the value with the given key
     * @return   TRUE - if such key was found in the key-value storage
     *           FALSE - if no such key was found in the key-value storage
     */
    bool GetEntry(std::string const& key, uint8_t* buf, uint32_t bufLen) override;

    /**
     * @brief    Retrieves all the keys in the stored key-value DB
     * @param    keys - OUT param - the keys found will be writtem to this vector
     * @return   none.
     */
    void GetAllKeys(std::vector<std::string>& keys) override;

    /**
     * @brief    Removes the key and its value from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    key - the key to remove with its value
     * @return   none.
     */
    void RemoveEntry(std::string const& key) override;

    /**
     * @brief    Removes the key and its value from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    key - the key to remove with its value
     * @return   none.
     */
    void RemoveEntry(std::string const&& key) override;

    /**
     * @brief    Removes all keys from the persistent memory
     *           No affect, if the key is not found in the key-value storage.
     * @param    none.
     * @return   none.
     */
    void RemoveAllKeys() override;

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

    /**
     * @brief    Saves any internaly saved key-value pairs to the persistent memory
     * @return   true on operation success, else false
     */
    virtual bool SaveToFile() override;

    /**
     * @brief    Determines whether the given key is set in the persistent memory.
     * @param    std::string const& key - the given key to check.
     * @return   bool - true if the key is in the persistent memory, false otherwise.
     */
    virtual bool HasKey(std::string const& key) override;

private:
    /**
     * @brief    Internal function to store the new value in the persistent memory with the given key.
     * @param    key - the key to save the new value with
     * @param    buf - the value to save
     * @param    bufLen - the length of buf
     * @return   TRUE - if the storing was successful
     *           FALSE - if the data was not stored: if there was not enough memory or the key is not unique.
     */
    bool storeValue(std::string const& key, uint8_t const* buf, uint32_t bufLen);

    inline const std::string
    buildFilePath(std::string const& key) const noexcept
    {
        return (m_directory + key + m_extension);
    }

    std::mutex            m_lock;
    static constexpr char m_extension[]{".key"};
    std::string           m_directory;
    bool                  m_isEnabled{false};
};
}  // namespace memory
}  // namespace common
