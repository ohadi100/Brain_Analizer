/**
 * @file
 * @brief       implementation of the Event
*/
#include "Event.hpp"
#include "EventUtils.hpp"

#include "common/utils/logger/Logger.hpp"
#include "common/utils/GUID/GUID.hpp"

using brain::events::EventPriority;
using brain::events::Event;
using brain::events::EventsUtils;

using common::GUID;

Event::Event()
{
    BufferType const buffer;
    Set(buffer, EventPriority::Low);
}

Event::Event(BufferType const& buffer, EventPriority const priority)
{
    Set(std::move(buffer), priority);
}

Event::Event(std::string const& buffer, EventPriority const priority)
{
    Set(std::move(buffer), priority);
}

void Event::Set(BufferType const& buffer, EventPriority const priority)
{
    m_buffer = std::move(buffer);
    m_priority = priority;
}

void Event::Set(std::string const& buffer, EventPriority const priority)
{
    m_buffer.reserve(buffer.size());
    static_cast<void>(std::copy(buffer.begin(), buffer.end(), m_buffer.data()));

    m_priority = priority;
}
