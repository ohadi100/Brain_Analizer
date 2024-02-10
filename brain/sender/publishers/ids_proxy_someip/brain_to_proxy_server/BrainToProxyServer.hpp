#pragma once

/**
 * @file
 * @brief Brain to Proxy Server of SOME/IP - sending the data to the IDS Proxy
 */


#include <vector>

#include "vwg/services/idsbrainproxyrelay/idsbrainproxyrelay_common.h"
#include "vwg/services/idsbrainproxyrelay/idsbrainproxyrelay_skeleton.h"

namespace brain
{
namespace publishers
{
namespace ids_proxy_someip
{


/**
 * @brief Template function for working with SOME/IP Skeleton relay types 
 *
 * @param relay - relay to send the message upon - it's type is easily detected by template function  
 * @param message - message to send on relay
 */
template <typename Relay, typename Data>
static void
SendMessage(Relay& relay, Data& message)
{
    std::vector<typename Relay::FieldType::value_type> messageVec;
    messageVec.push_back(message);
    relay.Update(messageVec);
}

/**
 * @brief Send empty message on the relay
 *
 * @param relay - relay to send the message upon - it's type is easily detected by template function  
 */
template <typename Relay>
static void
SendEmpty(Relay& relay)
{
    typename Relay::FieldType::value_type empty;
    SendMessage(relay, empty);
}

using vwg::services::idsbrainproxyrelay::skeleton::IDSBrainProxyRelaySkeleton;
using BrainToProxyData = vwg::services::idsbrainproxyrelay::datatypes::DT_relayForwardPDU_struct;

class BrainToProxyServer
{
public:
    /**
     * @brief Construct a new Brain To Proxy Server object. No domain interaction should happen at this stage.
     * 
     */
    BrainToProxyServer();

    /**
     * @brief Initialize the skeletons of the server
     * 
     */
    void InitSceleton();

    /**
     * @brief Offer service for IDS Proxy to start listening
     * 
     */
    void OfferService();

    /**
     * @brief Send message to IDS Proxy
     * 
     * @param msgPayload message in bytes
     * @param sequenceNumber number of sent messages in current session
     * @param msgType message type 
     */
    void Send(std::shared_ptr<std::vector<uint8_t>> msgPayload, uint32_t sequenceNumber, uint32_t msgType);

    /**
     * @brief Stop connection to IDS Proxy
     * 
     */
    void StopOfferService();

private:
    std::unique_ptr<IDSBrainProxyRelaySkeleton> m_skeleton;
};


}  // namespace ids_proxy_someip
}  // namespace publishers
}  // namespace brain