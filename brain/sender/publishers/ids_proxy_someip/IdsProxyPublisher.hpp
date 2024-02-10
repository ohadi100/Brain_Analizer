#pragma once

/**
 * @file 
 * @brief contains the IDS Proxy Publisher implementation of the Publisher Interface
 * Using BrainToProxyServer class (send message), and is open for extention with implementation of BrainToProxyClient (recieve feedback)
 */

#include "PublisherInterface.hpp"
#include "brain_to_proxy_server/BrainToProxyServer.hpp"

namespace brain
{
namespace publishers
{
namespace ids_proxy_someip
{

class IdsProxyPublisher : public PublisherInterface
{
public:
    /**
     * @brief Construct a new Ids Proxy Publisher object
     * 
     */
    IdsProxyPublisher() = default;

    /**
     * @brief Eslablish connectino to Proxy - server side for send and (ToDo) client side for recieve feedback
     * 
     * @param callback Call back for state change upon feedback
     * @return true - Connent sussesfull
     * @return false - Connect failed
     */
    bool Connect(std::function<void(EventType)> callback) override;

    /**
     * @brief Close Connection to IDS Proxy
     * 
     * @return true - Close sussesfull 
     * @return false - Close failed
     */
    bool Disconnect() override;

    /**
     * @brief Send Message to IDS Proxy. Send Should follow a feedback for the client
     * 
     * @param msgPayload - message serialized as bytes 
     * @return true - Send was succesfull
     * @return false - Send failed
     */
    bool SendMessage(std::shared_ptr<std::vector<uint8_t>> msgPayload) override;

private:
    uint32_t m_sequenceNumber{0U};
    std::function<void(EventType)> m_callBack{nullptr};
    BrainToProxyServer m_server; // Open for extention with implementing a client class (m_client)
};

}  // namespace ids_proxy_someip
}  // namespace publishers
}  // namespace brain
