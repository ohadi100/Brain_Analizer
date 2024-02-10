#include "EventUtils.hpp"
#include "common/utils/logger/Logger.hpp"

#include <stdexcept>
#ifdef _WIN32
#include <Iterator>
#endif

using brain::events::EventsUtils;
using brain::events::Event;

std::string EventsUtils::IntegerToZeroPaddedString(uint32_t const number, uint32_t const stringLength)
{
    try
    {
        std::string const numberAsString = std::to_string(number);

        if (numberAsString.length() > stringLength)
        {
            return "Invalid input";
        }

        size_t const numberOfCharsToPad = stringLength - numberAsString.length();
        static constexpr size_t MAX_PADDING_SIZE = 100U;
        if (numberOfCharsToPad > MAX_PADDING_SIZE)
        {
            LOG_ERROR << "padding size is too big" << LOG_NOOP;
            return std::string("");
        }

        std::string const paddedString = std::string(numberOfCharsToPad, '0').append(numberAsString);
        return paddedString;
    }
    catch (std::bad_alloc const& e)
    {
        LOG_ERROR << "failed allocate string and got exception: " << e.what() << LOG_NOOP;
        return std::string("");
    }   
}

uint32_t EventsUtils::BufferToNumber(Event::BufferType const & buffer)
{
    std::string const fieldString(buffer.begin(), buffer.end());

    uint32_t num = 0U;
    try
    {
        num = static_cast<uint32_t>(std::stoi(fieldString));
    }
    catch (std::invalid_argument const& ex)
    {
        LOG_ERROR << "error while trying to cast string to int - " << ex.what() << LOG_NOOP;
    }

    return num;
}

Event::BufferType EventsUtils::NumberToBuffer(
    uint32_t fieldValue,
    uint32_t fieldBufferLength)
{
    auto paddedString = IntegerToZeroPaddedString(fieldValue, fieldBufferLength);
    Event::BufferType bufferForFieldValue;

    std::ignore = std::copy(paddedString.begin(), paddedString.end(), std::back_inserter(bufferForFieldValue));

    return bufferForFieldValue;
}

Event::BufferType EventsUtils::GetSubBuffer(
    Event::BufferType& buffer,
    Event::BufferType::size_type const startIndex,
    Event::BufferType::size_type const endIndex)
{
    Event::BufferType::const_iterator sizeFieldStartIter =
        buffer.begin() + static_cast<long int>(startIndex);

    Event::BufferType::const_iterator sizeFieldStartEndIter =
        buffer.begin() + static_cast<long int>(startIndex + endIndex);

    Event::BufferType subBuffer(sizeFieldStartIter, sizeFieldStartEndIter);

    return subBuffer;
}