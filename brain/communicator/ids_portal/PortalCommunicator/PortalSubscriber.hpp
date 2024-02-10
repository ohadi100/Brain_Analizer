/**
 * @file
 * @brief    This file contains the definition of PortalCommunicator.
 */

#ifndef PORTALSUBSCRIBER_HPP
#define PORTALSUBSCRIBER_HPP

#include <string>
#include "yarpl/Disposable.h"

namespace brain
{
namespace brain_communicator
{
namespace portal
{
class PortalSubscriber
{
private:
    class AuxPortalSubscriber;

public:
    PortalSubscriber(std::string ipaddr, uint16_t port);
    ~PortalSubscriber();

    bool Subscribe();
    void UnSubscribe();

private:
    AuxPortalSubscriber* m_AuxPortalSubscriberPtr{nullptr};
    std::unique_ptr<yarpl::Disposable> m_disposable;
    bool m_subscribed;
    std::string m_ipaddr;
    uint16_t m_port;

};
} /* namespace portal */
} /* namespace brain_communicator */
} /* namespace brain */

#endif /* PORTALSUBSCRIBER_HPP */