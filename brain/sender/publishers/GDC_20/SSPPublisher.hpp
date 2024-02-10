/**
 * @file
 * @brief SSP Publisher implementation
 */
#ifndef SSP_PUBLISHER_HPP
#define SSP_PUBLISHER_HPP

#include "IPnOrchLibAdapter.hpp"

#include "PublisherInterface.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "common/utils/logger/Logger.hpp"

#include <memory>

namespace brain
{
namespace publishers
{
namespace ssp_publisher
{

/**
 * @class   SSPPublisher
 * @brief   SSP Publisher implementation
 */

class SSPPublisher final : public PublisherInterface
{
public:
    SSPPublisher(std::shared_ptr<IPnOrchLibAdapter> adapter);
    ~SSPPublisher() = default;

private:
    virtual bool        Connect(std::function<void(EventType)> callback) override;
    virtual bool        Disconnect() override;
    virtual std::size_t SendMessage(const std::vector<uint8_t>& msgPayload) override;

    std::shared_ptr<IPnOrchLibAdapter> mPnOrchLibAdapter;
};

}  // namespace ssp_publisher
}  // namespace publishers
}  // namespace brain


#endif  // SSP_PUBLISHER_HPP
