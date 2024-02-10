/**
 * @file
 * @brief    This file contains the definition of SimpleIdsmService.
 */

#ifndef IDSM_IDSM_SERVICE_HPP_
#define IDSM_IDSM_SERVICE_HPP_

#include <folly/Synchronized.h>
#include <yarpl/flowable/PublishProcessor.h>

#include <string>
#include <list>
#include <memory>

#include "proto/IdsPubSubPortal.hpp"

using namespace portal::ids::secevent;

namespace services
{

class SimpleIdsmService : public IIdsAgent
{
public:
    SimpleIdsmService();

    ~SimpleIdsmService() = default;

    folly::SemiFuture<folly::Unit> PublishIdsEvent(std::unique_ptr<IdsEvent> request) override;

    std::shared_ptr<yarpl::flowable::Flowable<std::unique_ptr<IdsEvent>>> SubscribeIdsEvent() override;

    bool IsSubscribed();

private:
    void put(IdsEvent& new_event);

    folly::Synchronized<std::list<IdsEvent>> mEntriesList;
    std::shared_ptr<yarpl::flowable::PublishProcessor<uint32_t>> mSecEvent;
    bool mSubscribed;
};

} // namespace services

#endif /* IDSM_IDSM_SERVICE_HPP_ */
