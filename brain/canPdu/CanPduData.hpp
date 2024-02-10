/**
 * @file      CanPduData.hpp
 * @brief     A class for the can Data struct.
 */

#pragma once


#pragma GCC diagnostic ignored "-Wpedantic"

#include <linux/if_ether.h>
#include <stdint.h>

#include "common/sensor_data/SensorData.hpp"
#include "CanPDU.hpp"
#include "CanPduState.hpp"

#include "ext/can_algorithm/src/include/ids_results.h"

namespace brain
{
namespace can_pdu
{
using SPCanPduState = std::shared_ptr<brain::can_pdu::CanPduState>;

constexpr uint32_t ETH_TNL_PROTO           = 0xFF08U;
constexpr uint32_t ETH_TYPE                = 0x08FFU;
constexpr uint32_t ETH_TNL_IDS_FRAME_ID_R7 = 0x0082U;
constexpr uint32_t ETH_TNL_IDS_FRAME_ID_CR = 0x0081U;

class EthTnlHeader
{
public:
    uint16_t seqNr;
    uint16_t frameId;
    uint16_t frameSz;
} __attribute__((packed));

class IdsCanFrame
{
public:
    uint32_t canId;
    uint32_t timestamp;
    int16_t  canbusId;
    uint16_t candataSz;
    uint8_t  candata[];
} __attribute__((packed));

class IdsFrame
{
public:
    struct ethhdr       ethhdr;
    struct EthTnlHeader ethtnlhdr;
    struct IdsCanFrame  data[];
} __attribute__((packed));

class CanMsg
{
public:
    // the members should be const , should generated  in compile time
    uint32_t const type;
    uint32_t const index;
    const char*    name;
    const int32_t  crcOffset;
    uint32_t const canIndex;

    // the members are const as table generated in compile time ,we need this cast operator = for example for sort
    // operation
    void
    operator=(const CanMsg& canMsg)
    {
        const_cast<uint32_t&>(type)     = canMsg.type;
        const_cast<uint32_t&>(index)    = canMsg.index;
        const_cast<const char*&>(name)  = canMsg.name;
        const_cast<uint32_t&>(canIndex) = canMsg.canIndex;
        const_cast<int32_t&>(crcOffset) = canMsg.crcOffset;
    }
};

class CanMsgWhiteList
{
public:
    CanMsg   canMsgsConst;
    uint32_t canId;
    uint16_t payloadsOffset;
    uint16_t timeStampsOffset;
    uint16_t bitOnOffset;
    uint16_t bitOnLocation;
    uint16_t comChannel;
    uint16_t size;
};

class CanPduData : public common::sensor_data::SensorData
{
public:
    static constexpr uint32_t ETH_TNL_MAX_IDS_FRAME_DATA_SIZE = 1476U;

    // since IdsFrame has empty array CanFrameData data[] the sizeof operator dose not count this member.
    // more over CanFrameData has empty array of uint8_t data so I had to add this sizes
    static constexpr uint32_t ETH_TNL_MAX_BUFFER_LENGTH
        = sizeof(IdsFrame) + ETH_TNL_MAX_IDS_FRAME_DATA_SIZE + 2 * sizeof(void*);

    char     m_buffer[ETH_TNL_MAX_BUFFER_LENGTH];
    uint32_t m_bufferSize;
};

struct CanEventEngineData : public common::sensor_data::SensorData
{
    brain::can_pdu::CanPDU*       m_pdu;
    SPCanPduState m_state;
    IDS_Result    m_result;
    uint32_t      m_timeStamp;
    uint32_t      m_canId;
};

}  // namespace can_pdu

}  // namespace brain
