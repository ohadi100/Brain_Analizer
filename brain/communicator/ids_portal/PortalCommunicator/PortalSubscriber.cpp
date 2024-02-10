#include <folly/Try.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <yarpl/flowable/Subscriber.h>
#include <glog/logging.h>

#include <memory>
#include <string>
#include <iomanip>

#include "portal/rsocket/RSocketPortalClient.hpp"
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wc++17-extensions"
#include "proto/IdsPubSubPortal.hpp"
#pragma clang diagnostic pop
#else
#include "proto/IdsPubSubPortal.hpp"
#endif

#include "PortalSubscriber.hpp"

using namespace portal::ids::secevent;
using namespace yarpl::flowable;
using brain::brain_communicator::portal::PortalSubscriber;

static std::unique_ptr<yarpl::Disposable> subscribeStream(
        IdsAgentStub& service,
        folly::CPUThreadPoolExecutor& executor)
{
    return service.SubscribeIdsEvent()->observeOn(executor)->subscribe(
        // onNext
        [](std::unique_ptr<IdsEvent> response) {
            LOG(INFO) << "\n\nIDS PortalSubscriber: got new security event:";
            LOG(INFO) << "IDS payload: " << response->payload() << "\n\n";
        },
        // onError
        [](folly::exception_wrapper ex) {
            LOG(INFO) << "IDS PortalSubscriber <-- ERROR: " << ex.what();
        },
        // onComplete
        []() {
            LOG(INFO) << "IDS PortalSubscriber <-- CLOSED";
        }
    );
}

class PortalSubscriber::AuxPortalSubscriber
{
public:
    AuxPortalSubscriber() = default;
    virtual ~AuxPortalSubscriber() = default;

    std::unique_ptr<yarpl::Disposable> AuxSubscribe(std::string ipaddr, uint16_t port)
    {
        m_executor = std::make_shared<folly::CPUThreadPoolExecutor>(1);
        m_client = ::portal::rpc::RSocketPortalClient::create()
                   .clientId("idscore")
                   .tcp(ipaddr, port)
                   .connect()
                   .getTry();

        if (m_client.hasValue())
        {
            m_service = std::make_shared<IdsAgentStub>(m_client.value());
            return subscribeStream(*m_service, *m_executor);
        }

        return nullptr;
    };
    
private:
    std::shared_ptr<folly::CPUThreadPoolExecutor> m_executor;
    folly::Try<std::shared_ptr<::portal::rpc::IPortalClient>> m_client;
    std::shared_ptr<IdsAgentStub> m_service;
};

PortalSubscriber::PortalSubscriber(std::string ipaddr, uint16_t port)
    : m_subscribed(false)
    , m_ipaddr(ipaddr)
    , m_port(port)
{
    m_AuxPortalSubscriberPtr = new AuxPortalSubscriber();
    LOG(INFO) << "IDS Portal Publisher address: " << m_ipaddr << " port: " << m_port;
}

PortalSubscriber::~PortalSubscriber()
{
    UnSubscribe();
    delete m_AuxPortalSubscriberPtr;
}

bool PortalSubscriber::Subscribe()
{
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;

    LOG(INFO) << "IDS Subscribing ...";

    m_disposable = m_AuxPortalSubscriberPtr->AuxSubscribe(m_ipaddr, m_port);
    if (m_disposable == nullptr)
    {
        LOG(ERROR) << "IDS Failed to connect to " << m_ipaddr << ":" << m_port;
        google::protobuf::ShutdownProtobufLibrary();
        return false;
    }

    m_subscribed = true;
    LOG(INFO) << "IDS Subscribed to " << m_ipaddr << ":" << m_port;

    return true;
}

void PortalSubscriber::UnSubscribe()
{
    if (m_subscribed) {
        LOG(INFO) << "IDS UnSubscribing ...";
        m_disposable->dispose();
        google::protobuf::ShutdownProtobufLibrary();
        m_subscribed = false;
    }

    LOG(INFO) << "IDS UnSubscribed";
}
