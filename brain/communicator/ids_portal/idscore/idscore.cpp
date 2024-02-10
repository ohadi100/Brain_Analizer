#include <folly/Try.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <yarpl/flowable/Subscriber.h>
#include <glog/logging.h>

#include <memory>
#include <string>
#include  <iomanip>

#include "portal/rsocket/RSocketPortalClient.hpp"
#include "proto/IdsPubSubPortal.hpp"

using namespace portal::ids::secevent;
using namespace yarpl::flowable;

static std::unique_ptr<yarpl::Disposable> subscribeStream(
        IdsAgentStub&                 service,
        folly::CPUThreadPoolExecutor& executor);

int main(int argc, char* argv[])
{
    int exitCode = 0;

    folly::Init initObj(&argc, &argv);
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;

    auto executor = std::make_shared<folly::CPUThreadPoolExecutor>(1);

    folly::Try<std::shared_ptr<portal::rpc::IPortalClient>> client =  //
            portal::rpc::RSocketPortalClient::create()
                    .clientId("cpp-example-client")
                    .tcp("127.0.0.1", 44444)
                    .connect()
                    .getTry();

    if (client.hasValue())
    {
        auto service = std::make_shared<IdsAgentStub>(client.value());

        std::unique_ptr<yarpl::Disposable> disposable = subscribeStream(*service, *executor);

        std::getchar();

        disposable->dispose();
    }
    else
    {
        LOG(ERROR) << "Failed to connect to 127.0.0.1:9001";
        exitCode = -1;
    }
    
    google::protobuf::ShutdownProtobufLibrary();
    return exitCode;
}

std::unique_ptr<yarpl::Disposable> subscribeStream(IdsAgentStub& service, folly::CPUThreadPoolExecutor& executor)
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