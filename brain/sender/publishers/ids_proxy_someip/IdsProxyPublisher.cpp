#include "IdsProxyPublisher.hpp"
#include <ac/com/runtime.hpp>
#include "Logger.hpp"
#include "PublisherInterface.hpp"

namespace brain
{
namespace publishers
{
namespace ids_proxy_someip
{

enum class MessageCategory: uint32_t
{
    CONTROL_MESSAGE         = 0,
    IDS_REPORT_MESSAGE      = 1,
    IDS_UPDATE_VEHICLE_DATA = 2
};

bool
IdsProxyPublisher::Connect(std::function<void(EventType)> callback)
{
    LOG_INFO << "IDS Proxy Publisher connecting to Proxy " << LOG_NOOP;

    // Declare IDS Is running for the service
    static ac::com::Runtime runtime;

    m_server.InitSceleton();
    m_server.OfferService();

    /*
        Open for extention with implementation of BrainToProxyClient and then:

        m_client.Connent(callback);

        Temporary working only in CONNECTED state
    */
    m_callBack = callback;
    m_callBack(EventType::CONNECTED);

    return true;
}

bool
IdsProxyPublisher::Disconnect()
{
    LOG_INFO << "IDS Proxy Publisher disconnecting from Proxy " << LOG_NOOP;
    m_server.StopOfferService();

    return true;
}

bool
IdsProxyPublisher::SendMessage(std::shared_ptr<std::vector<uint8_t>> msgPayload)
{
    if (nullptr == m_callBack)
    {
        LOG_ERROR << "IDS Proxy Connection uninitialized, SendMessage failed" << LOG_NOOP;
        return false;
    }

    ++m_sequenceNumber;
    LOG_DEBUG << "IDS Proxy Publisher Sending message, sequence number: " << m_sequenceNumber << " payload size: " << msgPayload->size() << LOG_NOOP;
    m_server.Send(msgPayload, m_sequenceNumber, (uint32_t)MessageCategory::IDS_REPORT_MESSAGE);

    // A way to Signal the Sender to keep sending, before Proxy feedback (client) interface was developed
    m_callBack(EventType::ACK_OK);
    return true;
}

}  // namespace ids_proxy_someip
}  // namespace publishers
}  // namespace brain
