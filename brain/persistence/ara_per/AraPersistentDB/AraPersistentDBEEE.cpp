#include <CounterNames.hpp>
#include <CounterManager.hpp>
#include <Logger.hpp>

#include "AraPersistentDBEEE.hpp" // implemennted

using common::memory::AraPersistentDBEEE;
using EventCounterLevelType = common::counters::EventCounter::EventCounterLevelType;

AraPersistentDBEEE::AraPersistentDBEEE(std::string const& dbName, CounterManagerPtr debugCounters) : AraPersistentDB()
,m_db(std::shared_ptr<ara::per::KeyValueStorage>())
,m_debugCounters(debugCounters)
{
    if(debugCounters)
    {
        m_errorSetPM = m_debugCounters->CreateCounter(common::counters::errors::ERROR_WHILE_SET_PM_VALUE(dbName), EventCounterLevelType::COUNTER_ERROR);
        m_errorSyncPM = m_debugCounters->CreateCounter(common::counters::errors::ERROR_WHILE_SYNC_TO_PM_STORAGE(dbName), EventCounterLevelType::COUNTER_ERROR);
    }

    if (InitializeDB(dbName))
    {
        return;
    }

    ara::core::StringView dbNameSV(dbName.c_str(), dbName.size());
    const auto resetStat = ara::per::ResetKeyValueStorage(ara::core::InstanceSpecifier(dbNameSV));
    if (!resetStat) 
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_ERROR << "Failed resetting DB '" << dbName << "' [" << errTranslate->Message(resetStat.Error().Value())
                  << "]" << LOG_NOOP;
        return;
    }

    if (InitializeDB(dbName))
    {
        return;
    }

    LOG_ERROR << "DB '" << dbName << "' failed to initialize" << LOG_NOOP;
}

AraPersistentDBEEE::~AraPersistentDBEEE()
{}

bool AraPersistentDBEEE::InitializeDB(std::string const& dbName)
{
    ara::core::StringView dbNameSV(dbName.c_str(), dbName.size());

    auto db = ara::per::OpenKeyValueStorage(ara::core::InstanceSpecifier(dbNameSV));
    if (!db) 
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_ERROR << "Error encountered during OpenKeyValueStorage = [" << errTranslate->Message(db.Error().Value())
                  << "]" << LOG_NOOP;
        return false;
    }

    m_db = *db;
    return true;
}

bool AraPersistentDBEEE::SetValue(common::types::string const& key, std::vector<uint8_t> const& data)
{
    if (!m_db)
    {
        LOG_ERROR << "Setting value with empty m_db!" << LOG_NOOP;
        return false;
    }

    ara::core::StringView keySV(key.c_str(), key.size());
    
    KvsType kvs(data.data(), data.size());
    ara::core::Result<void> res = m_db->SetValue(keySV, kvs);
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_DEBUG << "Error encountered during SetValue = [" << errTranslate->Message(res.Error().Value()) << "]"
                  << LOG_NOOP;
        common::counters::IncreaseCounter(m_errorSetPM);
        
        return false;
    }

    // Successful SetValue
    return true;
}

bool AraPersistentDBEEE::SetValue(common::types::string const& key, uint8_t const* buf, uint32_t bufLen)
{
    if (!m_db)
    {
        LOG_ERROR << "Setting value with empty m_db!" << LOG_NOOP;
        return false;
    }

    ara::core::StringView keySV(key.c_str(), key.size());
    
    KvsType kvs(buf, bufLen);
    ara::core::Result<void> res = m_db->SetValue(keySV, kvs);
    
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_DEBUG << "Error encountered during SetValue = [" << errTranslate->Message(res.Error().Value()) << "]"
                  << LOG_NOOP;
        common::counters::IncreaseCounter(m_errorSetPM);

        return false;
    }

    // Successful SetValue
    return true;
}

bool AraPersistentDBEEE::GetValue(common::types::string const& key, uint8_t* buf, uint32_t bufLen)
{
    if (!m_db)
    {
        LOG_ERROR << "GetValue called with empty m_db!" << LOG_NOOP;
        return false;
    }
    
    KvsType data;

    ara::core::StringView keySV(key.c_str(), key.size());
    ara::core::Result<void> res = m_db->GetValue(keySV, data);
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_ERROR << "Error encountered during GetValue = [" << errTranslate->Message(res.Error().Value())
                  << "], for key = [" << key << "]" << LOG_NOOP;
        return false;
    }

    if ((KvsType::Status::kSuccess != data.GetStatus()) || (KvsType::Type::kBinary != data.GetType()))
    {
        LOG_ERROR << "Error reading binary data" << LOG_NOOP;
        return false;
    }

    try
    {
        data.GetBinary(buf, bufLen);
    }
    catch(std::runtime_error const & e)
    {
        LOG_ERROR << "Error reading binary data: " << e.what() << LOG_NOOP;
        return false;
    }  

    // Successful GetValue
    return true;
}

cm::optional<std::vector<common::types::string>> AraPersistentDBEEE::GetAllKeys()
{
    if (!m_db)
    {
        LOG_WARNING << "GetAllKeys called with empty m_db!" << LOG_NOOP;
        return cm::optional<std::vector<common::types::string>>{};
    }
    
    auto res = m_db->GetAllKeys();
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_WARNING << "Error encountered during GetAllKeys = [" << errTranslate->Message(res.Error().Value()) << "]"
                    << LOG_NOOP;

        return cm::optional<std::vector<common::types::string>>{};
    }

    // Successful GetAllKeys

    std::vector<common::types::string> keys;

    const auto resKeys = res.Value();
    keys.reserve(resKeys.size());
    for (const auto& resKey : resKeys)
	{
        keys.emplace_back(resKey.c_str());
    }

    return cm::optional<std::vector<common::types::string>>{keys};
}

bool AraPersistentDBEEE::RemoveKey(common::types::string const& key)
{
    if (!m_db)
    {
        LOG_WARNING << "RemoveKey called with empty m_db!" << LOG_NOOP;
        return false;
    }
    
    ara::core::StringView keySV(key.c_str(), key.size());
    ara::core::Result<void> res = m_db->RemoveKey(keySV);
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_WARNING << "Error encountered during RemoveKey = [" << errTranslate->Message(res.Error().Value()) << "]"
                    << LOG_NOOP;
        return false;
    }

    // Successful RemoveKey
    return true;
}

bool AraPersistentDBEEE::RemoveAllKeys()
{
    if (!m_db)
    {
        LOG_WARNING << "RemoveAllKeys called with empty m_db!" << LOG_NOOP;
        return false;
    }
    
    ara::core::Result<void> res = m_db->RemoveAllKeys();
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_WARNING << "Error encountered during RemoveAllKeys = [" << errTranslate->Message(res.Error().Value()) << "]"
                    << LOG_NOOP;

        return false;
    }

    // Successful RemoveAllKeys
    return true;
}

bool AraPersistentDBEEE::SyncToStorage()
{
    if (!m_db)
    {
        LOG_WARNING << "SyncToStorage called with empty m_db!" << LOG_NOOP;
        return false;
    }
    
    ara::core::Result<void> res = m_db->SyncToStorage();
    if (!res.HasValue())
    {
        auto errTranslate = std::make_unique<ara::per::PerErrorDomain>();
        LOG_DEBUG << "Error encountered during SyncToStorage =  [" << errTranslate->Message(res.Error().Value()) << "]"
                  << LOG_NOOP;
        common::counters::IncreaseCounter(m_errorSyncPM);

        return false;
    }

    // Successful SyncToStorage
    return true;
}

bool AraPersistentDBEEE::HasKey(const std::string& key)
{
	if (!m_db)
    {
        LOG_ERROR << "HasKey called with empty m_db!" << LOG_NOOP;
        return false;
    }

	ara::core::StringView keySV(key.c_str(), key.size());
	ara::core::Result<bool> res = m_db->HasKey(keySV);
	bool const isKeyInDB = res.Value();
        LOG_DEBUG << "HasKey finished successfully with key '" << key << "'" << (isKeyInDB ? "" : " not") << " in DB"
                  << LOG_NOOP;
        return isKeyInDB;
}