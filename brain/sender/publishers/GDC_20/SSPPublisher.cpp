/**
 * @file
 * @brief SSP Publisher implementation
 */

#include "SSPPublisher.hpp"
#include "IPnOrchControl.h"
#include "common/utils/logger/Logger.hpp"

namespace brain
{
namespace publishers
{
namespace ssp_publisher
{

SSPPublisher::SSPPublisher(std::shared_ptr<IPnOrchLibAdapter> adapter)
  : mPnOrchLibAdapter(adapter)
{
}

bool
SSPPublisher::Connect(std::function<void(EventType)> callback)
{
    mPnOrchLibAdapter->connect();

    // Download and store the order in map
    mPnOrchLibAdapter->order_download();

    if (nullptr != callback)
    {
        callback(EventType::CONNECTED);
    }

    LOG_DEBUG << "SSP Publisher connected." << LOG_NOOP;
    return true;
}

bool
SSPPublisher::Disconnect()
{
    mPnOrchLibAdapter->disconnect();
    LOG_DEBUG << "Publisher disconnected." << LOG_NOOP;
    return true;
}

std::size_t
SSPPublisher::SendMessage(const std::vector<uint8_t>& msgPayload)
{
    mPnOrchLibAdapter->data_upload(msgPayload);
    return msgPayload.size();
}

}  // namespace ssp_publisher
}  // namespace publishers
}  // namespace brain
