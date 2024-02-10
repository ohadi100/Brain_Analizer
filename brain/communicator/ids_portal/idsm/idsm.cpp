#include <folly/Try.h>
#include <folly/executors/CPUThreadPoolExecutor.h>
#include <folly/init/Init.h>
#include <glog/logging.h>

#include <memory>
#include <string>
#include <chrono>
#include <thread>
#include <time.h>

#include "portal/rsocket/RSocketPortalServer.hpp"
#include "ids-service/ids_service.hpp"
#include "proto/IdsPubSubPortal.hpp"

using namespace portal::ids::secevent;

int main(int argc, char* argv[])
{
    folly::Init initObj(&argc, &argv);
    FLAGS_logtostderr = true;
    FLAGS_minloglevel = 0;

    LOG(INFO) << "Serving Portal RSocket server on 127.0.0.1:44444";

    auto idsmImpl = std::make_shared<services::SimpleIdsmService>();
    auto server = portal::rpc::RSocketPortalServer::create("idsm");
    server.tcp("127.0.0.1", 44444);
    server.executor(std::make_shared<folly::CPUThreadPoolExecutor>(1));
    server.addService(std::make_shared<IdsAgentAdapter>(idsmImpl));
    server.start();

    while (true) {
        using namespace std::chrono_literals;

        std::this_thread::sleep_for(500ms);

        if (!idsmImpl->IsSubscribed())
            continue;

        LOG(INFO) << "generating event ...";
        auto data = new std::string("hello from IDSM");
        auto event = std::make_unique<portal::ids::secevent::IdsEvent>();
        event->set_allocated_payload(data);
        idsmImpl->PublishIdsEvent(std::move(event));
    }

    server.stop();
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}