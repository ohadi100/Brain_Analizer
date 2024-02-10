#include <fstream>
#include <errno.h>

#include <cstdint>
#include <filesystem.hpp>
#include <Logger.hpp>

#include "FsPersistentMemoryManager.hpp" // implemented

using common::memory::FsPersistentMemoryManager;

constexpr char common::memory::FsPersistentMemoryManager::m_extension[];

FsPersistentMemoryManager::FsPersistentMemoryManager(std::string const& dbName) : m_directory(dbName +'/'), m_isEnabled(true)
{
    if (!make_directory(m_directory.c_str()))
    {
        LOG_FATAL << "unable to create a directory with the name: [" << m_directory << "]" << LOG_NOOP;
        throw std::exception();//TODO check if it's good approach
    }
}

FsPersistentMemoryManager::~FsPersistentMemoryManager()
{
    try
    {
        if (IsEnabled())
        {
            Disable();
        }
    }
    // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
    catch (std::exception const& /*e*/)
    // parasoft-end-suppress AUTOSAR-A15_3_4-a
    {
        LOG_ERROR << "destruction of the FsPersistentMemoryManager failed and got exception." << LOG_NOOP;
    }  // only for parasoft violations
}

bool FsPersistentMemoryManager::StoreEntry(std::string const& key, std::vector<uint8_t> const& buf)
{
    return storeValue(key, buf.data(), static_cast<uint32_t>(buf.size()));
}

bool FsPersistentMemoryManager::StoreEntry(std::string const&& key, std::vector<uint8_t> const& buf)
{
    return storeValue(key, buf.data(), static_cast<uint32_t>(buf.size()));
}

bool FsPersistentMemoryManager::StoreEntry(std::string const& key, uint8_t const* buf, uint32_t bufLen)
{
    return storeValue(key, buf, bufLen);
}

bool FsPersistentMemoryManager::StoreEntry(std::string const&& key, uint8_t const* buf, uint32_t bufLen)
{
    return storeValue(key, buf, bufLen);
}

bool FsPersistentMemoryManager::GetEntry(std::string const& key, uint8_t* buf, uint32_t bufLen)
{
    if (!IsEnabled() || (nullptr == buf) || key.empty())  
    {
        return false;
    }

    auto filePath = buildFilePath(key);

    std::lock_guard<std::mutex> lock(m_lock);
    std::ifstream rf(filePath, std::ios::in | std::ios::binary);

    if(!rf) 
    {
        LOG_ERROR << "Cannot open file!: " << filePath << " for reading" << LOG_NOOP;
        return false;
    }

    std::ignore = rf.read(reinterpret_cast<char*>(buf), bufLen);

    rf.close();

    if(!rf.good()) 
    {
        LOG_ERROR << "Cannot read from file: " << filePath << LOG_NOOP;
        return false;
    }

    return true;
}

void FsPersistentMemoryManager::GetAllKeys(std::vector<std::string> & keys)
{
    static_cast<void>(get_files_in_dir(m_directory, keys));

    auto it = keys.begin();
    while (it != keys.end())
    {
        std::size_t found = it->find(m_extension, (it->size()-sizeof(m_extension)));
        if (found==std::string::npos)
        {   // If element isn't key type, remove it
            it = keys.erase(it);
        }
        else 
        {   // Remove the internal identifier of key
            std::ignore = it->erase(it->end() - (sizeof(m_extension) - 1), it->end());
            ++it;
        }
    }
}

void FsPersistentMemoryManager::RemoveEntry(std::string const& key)
{
    std::lock_guard<std::mutex> lock(m_lock);
    std::ignore = std::remove(buildFilePath(key.c_str()).c_str());
}

void FsPersistentMemoryManager::RemoveEntry(std::string const&& key)
{
    std::lock_guard<std::mutex> lock(m_lock);
    std::ignore = std::remove(buildFilePath(key.c_str()).c_str());
}

void FsPersistentMemoryManager::RemoveAllKeys()
{
    if (IsEnabled())
    {
        std::vector<std::string> keysVec;
        GetAllKeys(keysVec);

        for (std::string & key : keysVec)
        {
            RemoveEntry(key);
        }
    }
}

bool FsPersistentMemoryManager::storeValue(std::string const& key, uint8_t const* buf, uint32_t bufLen)
{
    if (!IsEnabled())
    {
        return false;
    }
    //m_directory = "";
    auto filePath = buildFilePath(key);

    std::lock_guard<std::mutex> lock(m_lock);
    std::ofstream wf(filePath, std::ios::out | std::ios::binary);

    if(!wf) 
    {
        LOG_ERROR << "Cannot open file!: " << filePath << " for writing" << LOG_NOOP;
        return false;
    }

    std::ignore = wf.write(reinterpret_cast<const char*>(buf), bufLen);

    wf.close();

    if(!wf.good()) 
    {
        LOG_ERROR << "Error occurred at writing time to file!: " << filePath << LOG_NOOP;
        return false;
    }

    return true;
}

bool FsPersistentMemoryManager::SaveToFile()
{
    return true;
}

void FsPersistentMemoryManager::Disable()
{
    m_isEnabled = false;
}

void FsPersistentMemoryManager::Enable()
{
    m_isEnabled = true;
}

bool FsPersistentMemoryManager::IsEnabled()
{
    return m_isEnabled;
}

#if defined(EEE_PLATFORM) || defined(SIMULATION)
bool FsPersistentMemoryManager::HasKey(std::string const& key)
{
    std::ifstream rf(buildFilePath(key));
    return rf.good();
}
#endif
