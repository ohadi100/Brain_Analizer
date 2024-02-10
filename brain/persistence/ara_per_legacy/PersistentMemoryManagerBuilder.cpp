#include "PersistentMemoryManagerBuilder.hpp"
#include "AraPersistentMemoryManager.hpp"
#include "Logger.hpp"

namespace common
{
    namespace memory
{

PersistentMemoryManagerBuilder::PersistentMemoryManagerBuilder(PersistentMemoryWatchdogPtr watchdog, CounterManagerPtr debugCounters)
  : m_watchdog{watchdog}
  , m_debugCounters{debugCounters}
{
    common::memory::PersistentMemoryWatchdog::CreateThread(m_watchdog);
}

PersistentMemoryManagerBuilder::PersistentMemoryManagerInterfacePtr PersistentMemoryManagerBuilder::Create(std::string const& dbName)
{
    LOG_INFO << "Creating AraPersistentMemoryManager with legacy library - for " << dbName << LOG_NOOP;
    return std::make_shared<brain::memory::AraPersistentMemoryManager>(m_watchdog, dbName);
}

} // namespace memory   
} // namespace common
