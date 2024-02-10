#pragma once

/**
 * @file
 * @brief     The EngineDispatcher class that dequeues sensor data objects and sends them to the correct engine
 */

#include <memory>
#include <unordered_set>

#include "EngineDispatcherBase.hpp"
#include "MessageRepository.hpp"
#include "brain/diagnostics/interface/DiagnosticsManagerInterface.hpp"
#include "common/notification_handler/SensorDataQueuesManager.hpp"

namespace brain
{
namespace engines
{

/**
 * @class   EngineDispatcher
 * @brief   The EngineDispatcher class that dequeues sensor data objects and sends them to the correct engine
 */
class EngineDispatcher final : public EngineDispatcherBase
{
public:
    using DataArrivedEventPtr     = std::shared_ptr<common::notification_handler::DataArrivedEvent>;
    using SensorDataQueuesManager = common::notification_handler::SensorDataQueuesManager;

    EngineDispatcher(std::shared_ptr<brain::messageRepository::MessageRepositoryInterface> msgRepository,
                     SensorDataQueuesManager::SensorDataQueuesManagerPtr                   queuesManager,
                     common::configuration::Pointer                                        config);

    EngineDispatcher() = delete;

    void Init() override;
};
}  // namespace engines
}  // namespace brain
