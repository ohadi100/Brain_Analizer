#include "common/utils/logger/Logger.hpp"
#include "common/counter_manager/CounterManager.hpp"

#include "AraPersistentMemoryManager.hpp"

using common::memory::AraPersistentMemoryManager;

AraPersistentMemoryManager::AraPersistentMemoryManager(PersistentMemoryWatchdogPtr watchdog,
                                                       std::string const&          dbName,
                                                       CounterManagerPtr           debugCounters)
  : m_dbName(dbName)
  , m_accessLock()
  , m_watchdog(watchdog)
  , m_debugCounters(debugCounters)
{
    Enable();
}

AraPersistentMemoryManager::~AraPersistentMemoryManager()
{
    try
    {
        std::lock_guard<std::recursive_mutex> guard{m_accessLock};

        if (!IsEnabled())
        {
            return;
        }
        Disable();
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the persistent memory manager failed and got exception." << LOG_NOOP;
    } //only for parasoft violations
}

bool AraPersistentMemoryManager::StoreEntry(common::types::string const& key, std::vector<uint8_t> const& buf)
{
    if (key.empty())
    {
        return false;
    }

    return storeValue(key, buf);
}

bool AraPersistentMemoryManager::StoreEntry(common::types::string const&& key, std::vector<uint8_t> const& buf)
{
    common::types::string const tempKey = std::move(key);
    return StoreEntry(tempKey, buf);
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
    return StoreEntry(tempKey, buf, bufLen);
}

bool AraPersistentMemoryManager::GetEntry(common::types::string const& key, uint8_t* buf, uint32_t bufLen)
{    
    if ((nullptr == buf) || key.empty())
    {
        return false;
    }

    std::lock_guard<std::recursive_mutex> guard{m_accessLock};

    if (!IsEnabled())
    {
        return false;
    }

    m_token->Start();
    bool result = m_db->GetValue(key, buf, bufLen);
    m_token->Clear();

    if (!result)
    {
        LOG_WARNING << "Error Getting Value from DB, reconnecting" << LOG_NOOP;
        reconnectToDatabase();
        return false;
    }

    return true;
}

void AraPersistentMemoryManager::GetAllKeys(std::vector<common::types::string>& keys)
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};
    
    if (!IsEnabled())
    {
        LOG_WARNING << "GetAllKeys failed for db [" << m_dbName
                    << "] since storage is disabled for Ara Persistent Memory manager" << LOG_NOOP;

        keys = {};
        return;
    }

    m_token->Start();
    cm::optional<std::vector<common::types::string>> res = m_db->GetAllKeys();
    m_token->Clear();

    if(!res)
    {
        /**
         * If we had internal memory allocation issue, 
         * we will try to reconnect to persistency database.
         */
        reconnectToDatabase();
        keys = {};
        return;
    }

    keys = *res;
}

void AraPersistentMemoryManager::RemoveEntry(common::types::string const& key)
{
    removeValue(key);
}

void AraPersistentMemoryManager::RemoveEntry(common::types::string const&& key)
{
    removeValue(key);
}

void AraPersistentMemoryManager::RemoveAllKeys()
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};
    if (!IsEnabled())
    {
        return;
    }

    m_token->Start();
    std::ignore = m_db->RemoveAllKeys();
    m_token->Clear(); 
}

bool AraPersistentMemoryManager::storeValue(common::types::string const& key, std::vector<uint8_t> const& buf)
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};

    if (!IsEnabled())
    {
        return false;
    }

    m_token->Start();
    bool const isSuccess = m_db->SetValue(key, buf);
    m_token->Clear();
    
    if (!isSuccess)
    {
        /**
         * If we had internal memory allocation issue, 
         * we will try to reconnect to persistency database.
         */
        reconnectToDatabase();
    }

    return isSuccess;
}

bool AraPersistentMemoryManager::storeValue(common::types::string const& key, uint8_t const* buf, uint32_t bufLen)
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};

    if (!IsEnabled())
    {
        return false;
    }

    m_token->Start();
    bool isSuccess = false;
    isSuccess = m_db->SetValue(key, buf, bufLen);
    m_token->Clear();
    
    if (!isSuccess)
    {
        /**
         * If we had internal memory allocation issue, 
         * we will try to reconnect to persistency database.
         */
        reconnectToDatabase();
    }

    return isSuccess;
}

void AraPersistentMemoryManager::removeValue(common::types::string const& key)
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};
    if (!IsEnabled())
    {
        return;
    }

    m_token->Start();
    std::ignore = m_db->RemoveKey(key);
    m_token->Clear();
}

bool AraPersistentMemoryManager::SaveToFile()
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};

    if (!IsEnabled())
    {
        return false;
    }
    
    bool isSuccess = false;
    m_token->Start();
    isSuccess = m_db->SyncToStorage();
    m_token->Clear();

    return isSuccess;   
}

void AraPersistentMemoryManager::Enable()
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};

    if (IsEnabled())
    {
        LOG_WARNING << "Enabled called on an already enabled Ara Persistent Memory manager!" << LOG_NOOP;
        return;
    }

    LOG_DEBUG << "Opening persistent memory storage connection for db " << m_dbName << LOG_NOOP;
    m_token = m_watchdog->Register();
#ifdef EEE_PLATFORM
    m_db = std::make_unique<AraPersistentDBEEE>(m_dbName, m_debugCounters);
#endif

    if(nullptr == m_db)
    {
        LOG_WARNING << "Failed to Enable database " << m_dbName << LOG_NOOP;
    }
}
    
void AraPersistentMemoryManager::Disable()
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};

    if (!IsEnabled())
    {
        LOG_WARNING << "Not Disabling Ara Persistent Memory manager because the connection is already closed for db "
                    << m_dbName << LOG_NOOP;
        return;
    }

    LOG_DEBUG << "Closing persistent memory storage connection for db [" << m_dbName << "]" << LOG_NOOP;
    if (!SaveToFile())
    {
        LOG_WARNING << "Not Disabling Ara Persistent Memory manager because failed sync to file db " << m_dbName
                    << LOG_NOOP;
    }

    m_token->Start();
    m_db.reset(nullptr);
    m_token->Clear();

    m_token->Deactivate();
    m_token.reset();
}

bool AraPersistentMemoryManager::IsEnabled()
{
    return (nullptr != m_db.get());
}

void AraPersistentMemoryManager::reconnectToDatabase()
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};
    LOG_INFO << "Reconnecting to database [" << m_dbName << "] for Ara Persistent Memory manager" << LOG_NOOP;
    Disable();
    Enable();
}

#if defined(EEE_PLATFORM) || defined(SIMULATION)
bool AraPersistentMemoryManager::HasKey(std::string const& key)
{
    std::lock_guard<std::recursive_mutex> guard{m_accessLock};
    return m_db->HasKey(key);
}
#endif
