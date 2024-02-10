/**
 * @file      CanPDU.cpp
 * @brief     Define CanPDU struct, detach it from sensor data | THREAD SAFETY - 1 allocator and multiple de-allocators
  
 */
#include "CanPDU.hpp"

#include <cstring>
#include <sstream>
#include <string>
#include <stdexcept>

#include "Logger.hpp"

using namespace brain::can_pdu;

SingleQueueAllocator<CanPDU> CanPDU::m_allocator(MIN_PDU_ALLOC_COUNT, MAX_CAN_PDU_COUNT, PDU_ALLOC_STEP);

CanPDU* CanPDU::Allocate()
{
    return Allocate(false);
}

CanPDU* CanPDU::Allocate(bool const isGap)
{
    CanPDU* const tmp = m_allocator.Allocate();
    if (nullptr == tmp)
    {
        return tmp;
    }

    /*
    new(tmp) CanPDU();
    This syntax calls the tmp's CanPDU() Ctor, without allocating a new memory.

    It's like doing:
    tmp = CanPDU()
    but tmp is a const pointer so we can't assign it directly, therefor we use this syntax.
    */

    new(tmp) CanPDU();
    tmp->setIsGapFound(isGap);
    return tmp;
}

void CanPDU::Release(CanPDU* const element)
{
    element->~CanPDU();
    static_cast<void>(m_allocator.Release(element));
}

CanPDU& CanPDU::operator=(CanPDU rhs)
{
    m_isGapFound = rhs.m_isGapFound;
    m_size = rhs.m_isGapFound;
    static_cast<void>(std::move(std::begin(rhs.m_payload), std::end(rhs.m_payload), std::begin(m_payload)));
    m_timestamp = rhs.m_timestamp;
    m_msgType = rhs.m_msgType;
    m_msgBusId = rhs.m_msgBusId;
    m_msgId = rhs.m_msgId;
    m_msgIndex = rhs.m_msgIndex;


    return *this;
}

bool CanPDU::SetPayload(uint8_t* const buffer, uint16_t size)
{
    uint16_t copy_size = PDU_PAYLOAD_MAX_SIZE;

    if (size <= copy_size)
    {
        copy_size = size;
    }
    else
    {
        LOG_ERROR << "SetPayload received unexpected buffer size: " << size << LOG_NOOP;
        return false;
    }

    m_size = copy_size;
    if(0U != copy_size)
    {
        static_cast<void>(memcpy(m_payload, buffer, copy_size));
    }

    return true;
}

bool CanPDU::HasAllocatedPDUs()
{
    return m_allocator.HasElementsOutside();
}

///////////////////////////////////////////////////////////
//TODO: unmask the function once we have CAN PDU csv parser
///////////////////////////////////////////////////////////

// std::string CanPDU::removeCsvComments(std::string line)
// {
//     std::string csvLine = line;
//     auto const find_comment = csvLine.find_first_of(";#");
//     if (find_comment != std::string::npos)
//     {
//         csvLine.erase(find_comment, csvLine.length());
//     }
//     return Trim(csvLine);
// }

// void CanPDU::ParseCsvLine(std::string csvLine)
// {
//     csvLine = removeCsvComments(csvLine);
//     if(csvLine.length() == 0U)
//     {
//         return;
//     }

//     std::string element;
//     std::stringstream parsed(csvLine);

//     m_msgBusId = 0U;

//     static_cast<void>(getline(parsed, element, ','));
//     if (element.size() == 0U)
//     {
//         return;
//     }

//     try
//     {
//         m_timestamp = stoi(element);
//     }
//     catch (const std::invalid_argument& ia)
//     {
//         LOG(CommonLogerLevel::kError) << "ParseCsvLine - failed to parse timestamp with exception: " << ia.what();
//         m_timestamp = 0U;
//     }


//     static_cast<void>(getline(parsed, element, ','));
//     if (element.size() == 0U)
//     {
//         return;
//     }

//     try
//     {
//         m_msgId = stoi(element, 0, 16);
//     }
//     catch (const std::invalid_argument& ia)
//     {
//         LOG(CommonLogerLevel::kError) << "ParseCsvLine - failed to parse message id with exception: " << ia.what();
//         m_msgId = 0U;
//     }

//     static_cast<void>(getline(parsed, element));
//     m_size = element.size() / 2U;
//     for (uint32_t i = 0U; i < element.size(); i += 2)
//     {
//         try
//         {
//             m_payload[i / 2U] = static_cast<uint8_t>(stoi(element.substr(i, 2U), 0, 16));
//         }
//         catch (const std::invalid_argument& ia)
//         {
//             LOG(CommonLogerLevel::kError) << "ParseCsvLine - failed to parse payload with exception: " << ia.what();
//             m_payload[i / 2U] = 0U;
//         }
//     }
// }