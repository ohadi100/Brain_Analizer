/**
 * @file
 * @brief     This file contains the definition of the Event class and its functionality
 */
#ifndef EVENT_HPP
#define EVENT_HPP

#include <vector>
#include <memory>

#include "common/utils/types/string.hpp"
#include "EventPriority.hpp"

#include "autogen/nanopb/NanoPbInclude.hpp"

namespace brain
{
namespace events
{
constexpr int UUID_VER_4 = 4;

class Event final
{

public:
    using RuleEvaluation = com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation;

    using BufferType = std::vector<uint8_t>;
    using UuidStringType = common::types::string;

    /**
     * @brief   Default Constructor
     */
    Event();

    /**
     * @brief   Constructor
     * @param   BufferType buffer
     * @param   EventPriority priority
     */
    Event(BufferType const& buffer, EventPriority const priority);

    /**
     * @brief   Constructor
     * @param   std::string buffer
     * @param   EventPriority priority
     */
    Event(std::string const& buffer, EventPriority const priority);

    /**
     * @brief   Sets an internal data to the given data by the input. The old buffer is deleted,
     *          and a new one is allocate and copied
     * @param   BufferType const& buffer - the buffer to copy and store. Size is derived from the string object
     *          EventPriority const priority - the priority of the buffer stored
     */
    void Set(BufferType const& buffer, EventPriority const priority);

    /**
     * @brief   Sets an internal data to the given data by the input. The old buffer is deleted,
     *          and a new one is allocate and copied
     * @param   std::string const& buffer - the buffer to copy and store. Size is derived from the string object
     *          EventPriority const priority - the priority of the buffer stored
     */
    void Set(std::string const& buffer, EventPriority const priority);

    /**
     * @brief   Buffer getter
     * @return  Event::BufferType const& - The internally saved buffer
     */
    inline BufferType const& GetBuffer() const noexcept
    {
        return m_buffer;
    }

    /**
     * @brief   Size getter
     * @return  size_t - The size of the internally saved buffer
     */
    inline size_t GetSize() const noexcept
    {
        return m_buffer.size();
    }

    /**
     * @brief   Priority getter
     * @return  EventPriority - The priority of the internally saved buffer
     */
    inline EventPriority GetPriority() const noexcept
    {
        return m_priority;
    }

    /**
     * @brief   Check if the event is empty, or has valid data
     * @return  bool - true iff event is valid and has content
     */
    inline bool IsEventEmpty() const noexcept
    {
        return m_buffer.empty();
    }

private:
    BufferType m_buffer;
    brain::events::EventPriority m_priority;
};

} // namespace events
} // namespace brain

#endif // EVENT_HPP
