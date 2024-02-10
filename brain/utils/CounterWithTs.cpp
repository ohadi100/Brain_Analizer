#include "common/utils/logger/Logger.hpp"

#include "CounterWithTs.hpp"  // implemented

using brain::utils::CounterWithTs;

CounterWithTs::CounterWithTs(std::string const& name)
  : m_name(name)
  , m_counter(0U)
  , m_lastSeenTimeStamp(0U)
  , m_firstSeenTimeStamp(0U)
{
}

void
CounterWithTs::logIncrementWarning(const std::string& name)
{
    LOG_WARNING << "counter overflow, thus counter gets max value of uint64_t: " << name << LOG_NOOP;
}
