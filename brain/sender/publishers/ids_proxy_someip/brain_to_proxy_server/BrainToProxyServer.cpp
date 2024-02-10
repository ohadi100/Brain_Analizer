#include "BrainToProxyServer.hpp"

namespace brain
{
namespace publishers
{
namespace ids_proxy_someip
{

static constexpr char ServerIdInDomain[] = "IDSBrainProxyRelay_ProvidedSomeipServiceInstance";
static constexpr std::array<unsigned char, 16> SentNotificationId{
    'd', '5', '1', '3', 'c', 'b', '8', '2', 'a', '9', '1', '5', '4', 'd', '2', '7'};

BrainToProxyServer::BrainToProxyServer()
  : m_skeleton(nullptr)
{
}

void BrainToProxyServer::InitSceleton()
{
    m_skeleton = std::make_unique<IDSBrainProxyRelaySkeleton>(ara::com::InstanceIdentifier{ServerIdInDomain});
    SendEmpty(m_skeleton->relayForwardPDU);
    SendEmpty(m_skeleton->relayFeedbackPDU);
}

void BrainToProxyServer::OfferService()
{
    m_skeleton->OfferService();
}

void BrainToProxyServer::Send(std::shared_ptr<std::vector<uint8_t>> msgPayload, uint32_t sequenceNumber, uint32_t msgType)
{
    BrainToProxyData message;

    message.seqNum = sequenceNumber;
    message.id.emplace(SentNotificationId);
    message.protocolCntrl = msgType;
    message.framePayload  = std::vector<uint8_t>{};
    message.framePayload.value().assign(msgPayload->begin(), msgPayload->end());

    SendMessage(m_skeleton->relayForwardPDU, message);
    
}

void BrainToProxyServer::StopOfferService()
{
    m_skeleton->StopOfferService();
}

}  // namespace ids_proxy_someip
}  // namespace publishers
}  // namespace brain
