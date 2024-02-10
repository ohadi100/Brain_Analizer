/**
 * @file      CanPDU.hpp
 * @brief     Define CanPDU struct, detach it from sensor data | NOT THREAD SAFE, 1 allocator, 1 deallocator

 */
#pragma once

#include <string>

#include "common/utils/singleQueue/SingleQueueAllocator.hpp"
#include "ext/can_algorithm/resources/generated_resources/UNECE/matrix_defs.h"

#define NUM_OF_FORWARD_PDUS   (10)
#define NUM_OF_BACKWARDS_PDUS (15)
#define MAX_NUM_PDUS_TO_SAVE  (1 + NUM_OF_FORWARD_PDUS + NUM_OF_BACKWARDS_PDUS)

#define UNALIGNED_MAX_CAN_PDU                  (NUM_OF_CRITICAL_MESSAGES * MAX_NUM_PDUS_TO_SAVE * 3)
#define ROUND_NEAREST_STEP(STEP_SIZE, MAX_PDU) (((UNALIGNED_MAX_CAN_PDU / STEP_SIZE) + 1) * STEP_SIZE)

namespace brain
{
namespace can_pdu
{

/**
 * @class       CanPDU
 * @brief       This class holds all the information about the CanPDU message.
 *              This class holds a queue that holds the all CanPDU messages.
 *              This class holds SingleQueueAllocator<CanPDU>, and manage the allocation and the releases
 *              of any CanPDU message.
 *              The fields of this class is about the message details, like msgID, msgBusID and etc.
 *
 *              Static variable: m_allocator.
 *              The m_allocator variable is SingleQueueAllocator<CanPDU> static variable.
 *              This variable manages all the allocated CanPDU.
 *              The initial value is an empty SingleQueueAllocator<CanPDU> with capacity of MAX_CAN_PDU_COUNT.
 *              This variable is accessible for any module that import the CanPDU header via the following methods:
 *              Allocate() - To allocate new CanPDU.
 *              Release(CanPDU*) - To release a given CanPDU.
 *              HasAllocatedPDUs() - To check if CanPDU's allocated.
 */
class CanPDU
{

public:
    /**
     * @fn       CanPDU()
     * @brief    Constructor
     * @param    none
     * @return   none
     */
    CanPDU() = default;

    /**
     * @fn       CanPDU(const CanPDU&)
     * @brief    Copy constructor - disable this function
     * @param    CanPDU&
     * @return   none
     */
    CanPDU(const CanPDU&) = delete;

    /**
     * @fn       CanPDU(const CanPDU&&)
     * @brief    Copy constructor with rvalue reference - default
     * @param    CanPDU&&
     * @return   none
     */
    CanPDU(CanPDU&&) = default;

    /**
     * @fn       CanPDU& operator=(CanPDU)
     * @brief    operator=.
     * @param    CanPDU
     * @return   CanPDU&
     */
    CanPDU& operator=(CanPDU);

    /**
     * @fn       ~CanPDU()
     * @brief    Destructor
     * @param    none
     * @return   none
     */
    ~CanPDU() = default;

    /**
     * @fn       static CanPDU* Allocate()
     * @brief    allocates a new canPDU instance with isGap == false
     * @param    none
     * @return   CanPDU*
     */
    static CanPDU* Allocate();

    /**
     * @fn       static CanPDU* Allocate(bool isGap)
     * @brief    allocates a new canPDU struct with isGap == true
     * @param    bool isGap
     * @return   CanPDU*
     */
    static CanPDU* Allocate(bool const isGap);

    /**
     * @fn       static CanPDU* Allocate()
     * @brief    deletes the given instance
     * @param    CanPDU* instance
     * @return   none
     */
    static void Release(CanPDU* const element);

    /**
     * @fn       bool SetPayload(uint8_t* buffer, uint16_t size)
     * @brief    aggregate the Payloads of the CAN messages into a single buffer
     * @param    uint8_8* buffer - pointer to buffer to be aggregated
     * @param    uint16_t size - the size of the buffer
     * @return   true iff the value has been set
     */
    bool SetPayload(uint8_t* const buffer, uint16_t size);

    /**
     * @fn       inline void SetTimestamp(uint32_t timestamp)
     * @brief    sets the Timestamp of the CAN pdu
     * @param    uint32_t timestamp - The PDU's timestamp
     * @return   none
     */
    inline void
    SetTimestamp(uint32_t timestamp)
    {
        m_timestamp = timestamp;
    }

    /**
     * @fn       inline void SetCanIndex(uint32_t canIndex)
     * @brief    sets the canIndex
     * @param    uint32_t canIndex
     * @return   none
     */
    inline void
    SetCanIndex(uint32_t canIndex)
    {
        m_canIndex = canIndex;
    }

    /**
     * @fn       inline void SetCanCrcOffset(uint32_t crcOffset)
     * @brief    set the crc signal offset
     * @param    uint32_t crcOffset
     * @return   none
     */
    inline void
    SetCanCrcOffset(uint32_t crcOffset)
    {
        m_crcOffset = crcOffset;
    }

    /**
     * @fn       inline uint32_t GetCanIndex()
     * @brief    get the can index
     * @param    none
     * @return   uint32_t
     */
    inline uint32_t
    GetCanIndex()
    {
        return m_canIndex;
    }


    /**
     * @fn       inline uint32_t GetCanIndex()
     * @brief    get the crc offset
     * @param    none
     * @return   uint32_t
     */
    inline int32_t
    GetCanCrcOffset()
    {
        return m_crcOffset;
    }


    /**
     * @fn       inline void SetMsgType(uint32_t msgType)
     * @brief    sets the MsgType of the CAN pdu
     * @param    uint32_t msgType - The PDU's msgType
     * @return   none
     */
    inline void
    SetMsgType(uint32_t msgType)
    {
        m_msgType = msgType;
    }

    /**
     * @fn       inline void SetBusId(uint32_t msgBusId)
     * @brief    sets the BusId of the CAN pdu
     * @param    uint32_t msgBusId - The PDU's msgBusId
     * @return   none
     */
    inline void
    SetBusId(uint32_t msgBusId)
    {
        m_msgBusId = msgBusId;
    }

    /**
     * @fn       inline void SetMsgId(uint32_t msgId)
     * @brief    sets the MsgId of the CAN pdu
     * @param    uint32_t msgId - The PDU's MsgId
     * @return   none
     */
    inline void
    SetMsgId(uint32_t msgId)
    {
        m_msgId = msgId;
    }

    /**
     * @fn       void SetMsgIndex(uint32_t msgIndex)
     * @brief    sets the MsgIndex of the CAN pdu
     * @param    uint32_t msgIndex - The PDU's msgIndex
     * @return   none
     */
    inline void
    SetMsgIndex(uint32_t msgIndex)
    {
        m_msgIndex = msgIndex;
    }

    /**
     * @fn       inline const uint8_t* GetPayload() const
     * @brief    getter for the payload
     * @param    none
     * @return   uint8_t* - the payload
     */
    inline const uint8_t*
    GetPayload() const
    {
        return m_payload;
    }

    /**
     * @fn       inline size_t GetSize() const
     * @brief    getter for the size
     * @param    none
     * @return   uint8_t* - the payload size
     */
    inline size_t
    GetSize() const
    {
        return m_size;
    }

    /**
     * @fn       inline uint32_t GetTimestamp() const
     * @brief    getter for the timestamp
     * @param    none
     * @return   uint32_t - the timestamp
     */
    inline uint32_t
    GetTimestamp() const
    {
        return m_timestamp;
    }

    /**
     * @fn       inline uint32_t GetMsgType() const
     * @brief    getter for the type of the msg
     * @param    none
     * @return   uint32_t - the msg type
     */
    inline uint32_t
    GetMsgType() const
    {
        return m_msgType;
    }

    /**
     * @fn       inline uint32_t GetBusId() const
     * @brief    getter for the bus ID
     * @param    none
     * @return   uint32_t - the bus ID
     */
    inline uint32_t
    GetBusId() const
    {
        return m_msgBusId;
    }

    /**
     * @fn       inline uint32_t GetMsgId() const
     * @brief    getter for the msg ID
     * @param    none
     * @return   uint32_t - the msg ID
     */
    inline uint32_t
    GetMsgId() const
    {
        return m_msgId;
    }

    /**
     * @fn       inline uint32_t GetMsgIndex() const
     * @brief    getter for the msg index
     * @param    none
     * @return   uint32_t - the msg index
     */
    inline uint32_t
    GetMsgIndex() const
    {
        return m_msgIndex;
    }

    /**
     * @fn       inline bool IsGapFound() const
     * @brief    checks if there was a gap in the frames
     * @param    none
     * @return   bool - true if gap was found, false otherwise
     */
    inline bool
    IsGapFound() const
    {
        return m_isGapFound;
    }

    /**
     * @fn       static bool HasAllocatedPDUs()
     * @brief    checks if there are PDUs allocated and not released
     * @param    none
     * @return   bool - true if there are PDUs allocated and not released, false otherwise
     */
    static bool HasAllocatedPDUs();

    // /**
    //  * @fn       void ParseCsvLine(std::string csvLine)
    //  * @brief    parses a single csv line
    //  * @param    char* csvLine
    //  * @return   none
    //  */
    // void ParseCsvLine(std::string csvLine);

protected:
    //    /**
    //      * @fn       std::string RemoveCsvComments(std::string line)
    //      * @brief    remove comments from csv line .. the string after # or ;
    //      * @param    std::string line
    //      * @return   std::string
    //      */
    //     std::string removeCsvComments(std::string line);

private:
    inline void
    setIsGapFound(bool state)
    {
        m_isGapFound = state;
    }

    static SingleQueueAllocator<CanPDU> m_allocator;

    // min amount of allocated pdus
    static uint32_t const MIN_PDU_ALLOC_COUNT = 1000;

    // how many to allocate each time we increase the amount
    static uint32_t const PDU_ALLOC_STEP = 1000;

    static uint32_t const PDU_PAYLOAD_MAX_SIZE = 64;

    // max amount of allocated pdus, IM-5921 set size 2 times extra to avoid allocator memory starvation
    static uint32_t const MAX_CAN_PDU_COUNT = ROUND_NEAREST_STEP(PDU_ALLOC_STEP, UNALIGNED_MAX_CAN_PDU);

    bool m_isGapFound{0};

    uint16_t m_size;
    uint8_t  m_payload[PDU_PAYLOAD_MAX_SIZE];
    uint32_t m_timestamp;
    uint32_t m_canIndex;
    int32_t  m_crcOffset;  // if <0 , the can message without CRC
    uint32_t m_msgType;
    uint16_t m_msgBusId;
    uint32_t m_msgId;
    uint32_t m_msgIndex;
};

}  // namespace can_pdu
}  // namespace brain
