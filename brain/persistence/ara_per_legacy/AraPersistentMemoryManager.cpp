/**
 * @file      AraPersistentMemoryManager.cpp
 * @brief     AraPersistentMemoryManager functionality
  
 */

#include "AraPersistentMemoryManager.hpp"
#include "PersistentMemoryWatchdog.hpp"

#include <ara/per/perexceptions.h>
#include <ara/per/keyvaluestorage.h>

#include "Logger.hpp"

namespace brain
{

namespace memory
{

AraPersistentMemoryManager::AraPersistentMemoryManager(PersistentMemoryWatchdogPtr& watchdog, const std::string& dbName) :
                            m_dbName(dbName)
                            ,m_watchdog(watchdog)
{}

AraPersistentMemoryManager::~AraPersistentMemoryManager()
{
    if (true == IsEnabled())
    {
        Disable();
    }
}

bool AraPersistentMemoryManager::StoreEntry(common::types::string const& key, std::vector<uint8_t> const& buf)
{
    return StoreEntry(key, buf.data(), buf.size());
}

bool AraPersistentMemoryManager::StoreEntry(common::types::string const&& key, std::vector<uint8_t> const& buf)
{
    common::types::string const tempKey = std::move(key);
    return StoreEntry(tempKey, buf.data(), buf.size());
}

bool AraPersistentMemoryManager::StoreEntry(common::types::string const& key, uint8_t const* buf, uint32_t bufLen)
{
    if ((nullptr == buf) || key.empty())
    {
        return false;
    }

    return storeValue(key, buf, bufLen);
}

bool AraPersistentMemoryManager::StoreEntry(common::types::string const&& key, uint8_t const* buf, uint32_t bufLen)
{
    common::types::string const tempKey = std::move(key);
    return storeValue(tempKey, buf, bufLen);
}

bool AraPersistentMemoryManager::GetEntry(common::types::string const& key, uint8_t* buf, uint32_t bufLen)
{
    if ((false == IsEnabled()) || (nullptr == buf) || (true == key.empty()))
    {
        return false;
    }

    bool isSuccess = false;
    m_token->Start();
    ara::per::KvsType data = m_db->GetValue(key); // noexcept 
    m_token->Clear();

    if ((ara::per::KvsType::Status::kSuccess == data.GetStatus()) && (ara::per::KvsType::Type::kBinary == data.GetType()))
    {
        try
        {
            data.GetBinary(buf, bufLen); // throws logic_error
            isSuccess = true;
        }
        catch(ara::per::ExceptionLogicError const & e)
        {
            LOG_ERROR << "Error reading binary data: " << e.what() << LOG_NOOP;
        }
    }
    else
    {
        LOG_ERROR << "Error reading binary data" << LOG_NOOP;
    }

    return isSuccess;
}

void AraPersistentMemoryManager::GetAllKeys(std::vector<std::string>& keys)
{

    if (false == IsEnabled())
    {
        LOG_ERROR << "ara::per - GetAllKeys failed since storage is disabled for db: " << m_dbName << LOG_NOOP;

        keys = {};
        return;
    }

    bool isReconnectNeeded = false;

    try
    {
        m_token->Start();
        keys = m_db->GetAllKeys(); // throws physical_storage_error, logic_error 
        m_token->Clear();
    }
    catch (ara::per::ExceptionPhysicalStorageError const& e)
    {
        LOG_ERROR << "ara::per - out of memory while creating the return vector: " << e.what() << LOG_NOOP;
        isReconnectNeeded = true;
    }
    catch (ara::per::ExceptionLogicError const& e)
    {
        LOG_ERROR << "ara::per - invalid state used: " << e.what() << LOG_NOOP;
    }

    if(true == isReconnectNeeded)
    {
        /**
         * If we had internal memory allocation issue, 
         * we will try to reconnect to persistency database.
         */
        reconnectToDatabase();
    }
}

void AraPersistentMemoryManager::RemoveEntry(common::types::string const& key)
{
    removeEntry(key);
}

void AraPersistentMemoryManager::RemoveEntry(common::types::string const&& key)
{
    removeEntry(key);
}

void AraPersistentMemoryManager::RemoveAllKeys()
{
    if (true == IsEnabled())
    {
        m_token->Start();
        m_db->RemoveAllKeys(); // noexcept
        m_token->Clear();
    }    
}

bool AraPersistentMemoryManager::storeValue(std::string const& key, const uint8_t* buf, uint32_t bufLen)
{
    if (false == IsEnabled())
    {
        return false;
    }

    bool isSuccess = false;
    bool isReconnectNeeded = false;
    
    ara::per::KvsType dataToWrite(buf, bufLen);

    try
    {
        m_token->Start();
        m_db->SetValue(key, dataToWrite); // throws physical_storage_error, logic_error
        m_token->Clear();
        isSuccess = true;
    }
    catch (ara::per::ExceptionPhysicalStorageError const& e)
    {
        LOG_ERROR << "Can't write key: " << key << ", internal memory allocation failed: " << e.what() << LOG_NOOP;
        isReconnectNeeded = true;
    }
    catch (ara::per::ExceptionLogicError const& e)
    {
        LOG_ERROR << "Can't write key: " << key << ", invalid state used: " << e.what() << LOG_NOOP;
    }
    
    if(true == isReconnectNeeded)
    {
        /**
         * If we had internal memory allocation issue, 
         * we will try to reconnect to persistency database.
         */
        reconnectToDatabase();
    }

    return isSuccess;
}

void AraPersistentMemoryManager::removeEntry(std::string const& key)
{
    if (true == IsEnabled())
    {
        m_token->Start();
        m_db->RemoveKey(key); // noexcept
        m_token->Clear();
    }
}

bool AraPersistentMemoryManager::SaveToFile()
{
    if (false == IsEnabled())
    {
        return false;
    }

    bool isSuccess = false;
    
    try
    {
        m_token->Start();
        m_db->SyncToStorage(); // throws physical_storage_error, logic_error
        m_token->Clear();
        isSuccess = true;
    }
    catch (ara::per::ExceptionPhysicalStorageError const & e)
    {
        LOG_ERROR << "ara::per - internal memory allocation failed: " << e.what() << LOG_NOOP;
    }
    catch (ara::per::ExceptionLogicError const & e)
    {
        LOG_ERROR << "ara::per - invalid state used: " << e.what() << LOG_NOOP;
    }

    return isSuccess;   
}

void AraPersistentMemoryManager::Enable()
{
    if (true == IsEnabled())
    {
        return;
    }

    LOG_INFO << "AraPersistentMemoryManager::Enable - Opening connection for db: " << m_dbName << LOG_NOOP;

    try
    {
        m_token = m_watchdog->Register();
        m_db = std::make_unique<ara::per::KeyValueStorage>(m_dbName); // throws storage_location_not_found, physical_storage_error
    }
    catch (ara::per::ExceptionPhysicalStorageError const & e)
    {
        LOG_ERROR << "AraPersistentMemoryManager::Enable - ExceptionPhysicalStorageError thrown: " << e.what()
                  << LOG_NOOP;
        m_db = nullptr;
    }
    catch (ara::per::ExceptionStorageLocationNotFound const & e)
    {
        LOG_ERROR << "AraPersistentMemoryManager::Enable - ExceptionStorageLocationNotFound thrown: " << e.what()
                  << LOG_NOOP;
        m_db = nullptr;
    }
    
    if(nullptr == m_db)
    {
        LOG_ERROR << "AraPersistentMemoryManager::Enable - Failed to Enable database: " << m_dbName << LOG_NOOP;
    }
    
}
    
void AraPersistentMemoryManager::Disable()
{
    if (!IsEnabled())
    {
        return;
    }

    LOG_INFO << "Closing persistent memory storage connection for db: " << m_dbName << LOG_NOOP;

    auto isSaveToFileSucceed = SaveToFile();
    
    if(false == isSaveToFileSucceed)
    {
        LOG_ERROR << "AraPersistentMemoryManager::Disable - failed sync to file db: " << m_dbName
                  << ", crash is expected" << LOG_NOOP;
    }

    m_token->Start();
    m_db.reset(nullptr); 
    m_token->Clear();
    m_token->Deactivate();
    m_token.reset();
}

bool AraPersistentMemoryManager::IsEnabled()
{
    return nullptr != m_db.get();
}

void AraPersistentMemoryManager::reconnectToDatabase()
{
    Disable();
    Enable();
}

} // namespace memory
} // namespace brain
