/**
* @file
* @brief    This file contains the definition of SciSignalGroupHandler.
*/
#ifndef SCI_SIGNAL_GROUP_HANDLER_HPP
#define SCI_SIGNAL_GROUP_HANDLER_HPP

#include <map>

#include <sci/frontend/api/IEventHandlers.hpp>
#include <sci/frontend/common/ReceivedSignal.hpp>
#include <sci/frontend/common/ReceivedSignalGroup.hpp>

namespace brain
{
namespace brain_communicator
{
namespace sci_communicator
{

using namespace vwg::e3p::com;
using ExternalCallbackType = std::function<void(std::string const& signalName, std::vector<sci::ReceivedSignal const*> const& signals)>;

class SciSignalGroupHandler : public sci::api::ISignalGroupEventHandler
{
public:
    /**
     * @brief   Ctor
     * @param   std::string const& signalGroupName
     * @param   ExternalCallbackType callbackFunction
     */
    SciSignalGroupHandler(std::string const& signalGroupName, ExternalCallbackType const& callbackFunction);

    /**
     * @brief   This is the function designed to be registered to the sci signals, as defined in SCI's ISignalGroupEventHandler.
     *          Calles the callback function passed to it's constructor.
     * @param   sci::EventType const event
     * @param   sci::ReceivedSignal const& signal
     * @param   std::vector<sci::ReceivedSignal const*> const& signals
     * @return  None
     */
    void onEvent(sci::EventType const event, sci::ReceivedSignalGroup const& signalGroup, std::vector<sci::ReceivedSignal const*> const& signals) noexcept override;

private:
    std::string m_signalGroupName;
    ExternalCallbackType m_callback;

};

} /* namespace sci_communicator */
} /* namespace brain_communicator */
} /* namespace brain */

#endif /* SCI_SIGNAL_GROUP_HANDLER_HPP */
