#pragma once
/**
 * @file
 * @brief     HTTPS Publisher implementation
 */

#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/un.h>

#include <factory/PersistentMemoryFactory.hpp>
#include "common/utils/logger/Logger.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
#include "sender/publishers/interface/PublisherInterface.hpp"
#include "sender/publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"

using namespace brain::publishers::utils;
namespace brain
{
namespace publishers
{
namespace https
{

/**
 * @class   Publisher
 * @brief   HTTPS Publisher implementation
 */
class Publisher : public PublisherInterface
{
public:
    using ChangeModeCallback = std::function<void(PublisherInterface::EventType)>;

    /**
     * @brief   Constructor
     */
    Publisher(std::shared_ptr<common::memory::PersistentMemoryFactory>,
              std::shared_ptr<common::counters::CounterManager>,
              common::configuration::Pointer)
    {
    }

    /**
     * @brief   Destructor
     */
    ~Publisher();

    /**
     * @brief   Inits the publisher
     */
    void Init();
    /**
     * @brief   Get the reactor callback and start offering agent service
     * @param   std::function<void>EventType)
     * @return  true
     */
    bool Connect(ChangeModeCallback callback) override;

    /**
     * @brief   stop offering agent service
     * @return  true
     */
    bool Disconnect() override;
    /**
     * @brief   sends forward message from brain to HTTPS server
     * @param   std::vector<uint8_t> const& msgPayload
     * @return  true
     */
    bool SendMessage(std::shared_ptr<std::vector<uint8_t>> msgPayload) override;

    inline const SPExceededMessageSizeCheck
    GetExceededMessageSizeCheck() const
    {
        return {};
    }

private:
    int                m_outSocket = -1;
    ChangeModeCallback m_callback;
};


}  // namespace https
}  // namespace publishers
}  // namespace brain