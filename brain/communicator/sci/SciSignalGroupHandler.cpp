/**
 * @file
 * @brief     This file contains the functionality of the SciSignalGroupHandler class
 */
#include "SciSignalGroupHandler.hpp"

#include "brain/config/BrainConfigConstants.hpp"
#include "common/utils/logger/Logger.hpp"

using brain::brain_communicator::sci_communicator::SciSignalGroupHandler;

SciSignalGroupHandler::SciSignalGroupHandler(std::string const& signalGroupName, ExternalCallbackType const& callbackFunction) :
    m_signalGroupName(signalGroupName),
    m_callback(callbackFunction)
    {
    }

void SciSignalGroupHandler::onEvent(sci::EventType const event, sci::ReceivedSignalGroup const& signalGroup, std::vector<sci::ReceivedSignal const*> const& signals) noexcept
{
    if (sci::EventType::kOnChange == event)
    {
        LOG_VERBOSE << "[OnChange event] for signal group, updating signal group " << m_signalGroupName << LOG_NOOP;
        signalGroup.updateGroupSignals();
        m_callback(m_signalGroupName, signals);
    }
}
