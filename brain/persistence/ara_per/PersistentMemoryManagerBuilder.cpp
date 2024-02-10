#include "common/persistent_memory/interface/PersistentMemoryManagerBuilder.hpp"
#include "AraPersistentMemoryManager.hpp"
#include "common/utils/logger/Logger.hpp"

using common::memory::PersistentMemoryManagerBuilder;

PersistentMemoryManagerBuilder::PersistentMemoryManagerBuilder(PersistentMemoryWatchdogPtr watchdog,
                                                               CounterManagerPtr           debugCounters)
  : m_watchdog{watchdog}
  , m_debugCounters{debugCounters}
{
    common::memory::PersistentMemoryWatchdog::CreateThread(m_watchdog);
}

PersistentMemoryManagerBuilder::PersistentMemoryManagerInterfacePtr
PersistentMemoryManagerBuilder::Create(std::string const& dbName)
{
    LOG_DEBUG << "creating AraPersistentMemoryManager for " << dbName << LOG_NOOP;
    return std::make_shared<AraPersistentMemoryManager>(m_watchdog, dbName, m_debugCounters);
}