/**
 * @file
 * @brief     This file contains the definition of the EventUtils class and its functionality
*/
#ifndef EVENT_UTILS_HPP
#define EVENT_UTILS_HPP

#include <vector>
#include <string>
#include <memory>

#include "Event.hpp"

namespace brain
{

namespace events
{

/**
 * @class   EventsUtils
 * @brief   EventsUtils implementation
 */
class EventsUtils
{
public:

    /**
     * @brief   Convert number to data buffer
     * @param   fieldValue
     * @param   fieldBufferLength
     * @return  Event::BufferType
     */
    static Event::BufferType NumberToBuffer(uint32_t fieldValue, uint32_t fieldBufferLength);

    /**
     * @brief   Convert buffer to number
     * @param   buffer
     * @return  uint32_t
     */
    static uint32_t BufferToNumber(Event::BufferType const & buffer);

    /**
     * @brief   Convert number to string and pad the string with zeros.
     * @param   number
     * @param   stringLength
     * @return  std::string
     */
    static std::string IntegerToZeroPaddedString(uint32_t const number, uint32_t const stringLength);

    /**
     * @brief   Get range of buffer between start and end indices
     * @param   number
     * @param   stringLength
     * @return  std::string
     */
    static Event::BufferType GetSubBuffer(
        Event::BufferType& buffer,
        Event::BufferType::size_type const startIndex,
        Event::BufferType::size_type const endIndex);

};

} //namespace events
} //namespace brain

#endif // EVENT_UTILS_HPP