#include "common/persistent_memory/interface/PersistentMemoryManagerBuilder.hpp"
#include "FsPersistentMemoryManager.hpp"
#include "common/utils/logger/Logger.hpp"

using common::memory::PersistentMemoryManagerBuilder;

namespace common
{
namespace memory
{
static constexpr char PM_DIRECTORY[] = DPM_DIRECTORY;
}  // namespace memory
}  // namespace common



PersistentMemoryManagerBuilder::PersistentMemoryManagerBuilder(PersistentMemoryWatchdogPtr watchdog,
                                                               CounterManagerPtr           debugCounters)
  : m_watchdog{watchdog}
  , m_debugCounters{debugCounters}
{
    common::memory::PersistentMemoryWatchdog::CreateThread(m_watchdog);
    static constexpr char IDS_DIRECTORY[] = DIDS_DIRECTORY;

    if (sizeof(IDS_DIRECTORY) > 0)
    {
        make_directory(IDS_DIRECTORY);
    }
    
    if (sizeof(PM_DIRECTORY) > 0)
    {
        make_directory(PM_DIRECTORY);
    }
}

PersistentMemoryManagerBuilder::PersistentMemoryManagerInterfacePtr
PersistentMemoryManagerBuilder::Create(std::string const& dbName)
{
    LOG_DEBUG << "creating FsPersistentMemoryManager for " << dbName << LOG_NOOP;
    return std::make_shared<common::memory::FsPersistentMemoryManager>(std::string(PM_DIRECTORY) + dbName);
}