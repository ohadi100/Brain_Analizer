
/**
 * @file
 * @brief     code for the generic EngineDispatcher
 */

#include "EngineDispatcher.hpp"
#include "brain/events/Event.hpp"
#include "brain/events/EventPriority.hpp"
#include "PeriodicStatisticsEngine.hpp"
#include "common/sensor_data/SensorDataTags.hpp"

namespace brain
{
namespace engines
{

EngineDispatcher::EngineDispatcher(std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                                   SensorDataQueuesManager::SensorDataQueuesManagerPtr                   queuesManager,
                                   common::configuration::Pointer const                                  config)
  : EngineDispatcherBase(
      queuesManager, static_cast<uint32_t>(SensorDataTag::SD_NUMBER_OF_TAGS), events::EventPriorityMap)
{
    auto reportSerializer = std::make_shared<IDSPeriodicReportSerializer>(config);
    m_engines[static_cast<uint32_t>(SensorDataTag::SD_PERIODIC_STATISTICS)]
        = std::make_shared<PeriodicStatisticsEngine>(msgRepository, reportSerializer, events::EventPriority::Critical);
}

void
EngineDispatcher::Init()
{
}

}  // namespace engines
}  // namespace brain
