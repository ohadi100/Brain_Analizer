#include "ids_service.hpp"

#include <yarpl/single/Singles.h>
#include <glog/logging.h>

#include <functional>
#include <utility>

using folly::SemiFuture;
using folly::Unit;
using namespace portal::ids::secevent;

namespace services
{
SimpleIdsmService::SimpleIdsmService()

    : IIdsAgent()
    , mEntriesList()
    , mSecEvent(yarpl::flowable::PublishProcessor<uint32_t>::create())
    , mSubscribed(false)
{
}

folly::SemiFuture<folly::Unit> SimpleIdsmService::PublishIdsEvent(std::unique_ptr<IdsEvent> request)
{
    (void) put(*request);

    return folly::Unit{};
}

std::shared_ptr<yarpl::flowable::Flowable<std::unique_ptr<IdsEvent>>> SimpleIdsmService::SubscribeIdsEvent()
{
    LOG(INFO) << "Subscribe on IdsEvent";

    mSubscribed = true;

    return mSecEvent
            ->map([this](const uint32_t& dummy) {
                IdsEvent event;
                mEntriesList.withWLock([&](auto& locked_list) {
                    event = locked_list.front();
                    locked_list.pop_front();
                });

                return std::make_unique<IdsEvent>(event);
            })
            ->toFlowable(yarpl::BackpressureStrategy::LATEST);
}

void SimpleIdsmService::put(IdsEvent& new_event)
{
    mEntriesList.withWLock([&](auto& locked_list) {
        locked_list.push_back(new_event);
    });
    
    mSecEvent->onNext(0);
}

bool SimpleIdsmService::IsSubscribed()
{
    return mSubscribed;
}

} // namespace services
