#include "DiagnosticsManager.hpp"
#include <persistent_map/PersistentMap.h>
#include <DBNames.hpp>
#include <factory/PersistentMemoryFactory.hpp>

using brain::diagnostics::DiagnosticsManager;

void
DiagnosticsManager::Init()
{
    LOG_INFO << "DIAG_INIT" << LOG_NOOP;
}

inline std::atomic<bool>&
DiagnosticsManager::GetFeatureFlag(uint8_t /*adaptationId*/)
{
    static std::atomic<bool> rc{true};
    return rc;
}
