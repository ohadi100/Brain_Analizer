#include "CanPduParser.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "ext/can_algorithm/resources/generated_resources/UNECE/matrix_defs.h"
#include "ext/can_algorithm/src/include/mqb_can_types.h"

namespace brain
{
namespace can_pdu
{
CanPduParser::CanPduParser()
{
}

CanPduParser::~CanPduParser()
{
}

void
CanPduParser::ParserInit()
{

// m_canMsgsWhite.size() initilize m_canMsgsWhite with the areay index [{..0},{..1},{..2} ...]
#define CAN_MAP_FILL(CAN_NAME, CAN_ID, CAN_TYPE, CAN_IND, CRC_OFFSET, CYC_TIME)                                        \
    {                                                                                                                  \
                                                                                                                       \
        m_canMsgsIntermediate.insert(std::pair<uint32_t, brain::can_pdu::CanMsg>(                                                      \
            CAN_ID, {CAN_TYPE, CAN_IND, #CAN_NAME, CRC_OFFSET, static_cast<uint32_t>(m_canMsgsIntermediate.size())})); \
    }
#include "ext/can_algorithm/resources/generated_resources/UNECE/can_map_fill.h"
#undef CAN_MAP_FILL

    LOG_INFO << "CAN Matrix version: " << CAN_MATRIX_VERSION << LOG_NOOP;
    LOG_INFO << "CAN Count: " << m_canMsgsIntermediate.size() << LOG_NOOP;
}

bool
CanPduParser::ParseAndCreatePdu(brain::can_pdu::IdsFrame* frame, std::vector<brain::can_pdu::CanPDU*>& pduVec)
{
    // Check if the frame pointer is valid
    if (nullptr == frame)
    {
        LOG_ERROR << "Invalid IdsFrame pointer" << LOG_NOOP;
        return false;
    }

    // Get the size of the frame
    uint16_t frameSize = frame->ethtnlhdr.frameSz;
    uint16_t offset    = 0;

    // Iterate over the frame and extract the IdsCanFrame structures
    while (offset + sizeof(brain::can_pdu::IdsCanFrame) <= frameSize)
    {
        // Get a pointer to the current IdsCanFrame structure
        brain::can_pdu::IdsCanFrame* canFrame = reinterpret_cast<brain::can_pdu::IdsCanFrame*>(reinterpret_cast<uint8_t*>(frame->data) + offset);

        uint32_t canId = canFrame->canId & canIdMask;

        // Check if the size of the current IdsCanFrame plus the data size exceeds the frame size
        if (offset + sizeof(brain::can_pdu::IdsCanFrame) + canFrame->candataSz > frameSize)
        {
            LOG_ERROR << "mismatched sizes, IdsCanFrame exceeds the frame size" << LOG_NOOP;
            return false;
        }

        // Convert the IdsCanFrame to CanPDU and add it to the result vector
        auto iter = m_canMsgsIntermediate.find(canId);

        if (iter != m_canMsgsIntermediate.end())
        {
            auto const msgPtr = &(iter->second);

            // Due to the high amount of PDU created we avoid using smart pointers which has more overhad the regular
            // raw pointer. The responsibility for releaseing the PDU* value is on the canPduState when it is no longer
            // in use.
            brain::can_pdu::CanPDU* pdu = brain::can_pdu::CanPDU::Allocate(false);
            if (nullptr == pdu)
            {
                LOG_ERROR << "Failed to aloocate CanPDU object" << LOG_NOOP;
                continue;
            }

            pdu->SetMsgId(canId);
            pdu->SetMsgType(msgPtr->type);
            pdu->SetMsgIndex(msgPtr->index);
            pdu->SetCanIndex(msgPtr->canIndex);
            pdu->SetCanCrcOffset(msgPtr->crcOffset);
            pdu->SetBusId(canFrame->canbusId);
            pdu->SetTimestamp(canFrame->timestamp);
            pdu->SetPayload(canFrame->candata, canFrame->candataSz);
            pduVec.push_back(pdu);
        }
        else
        {
            // TODO: when can matrix is updated, the log level should be changed to kInfo
            LOG_ERROR << "CAN id: " << std::hex << canId << " was not found in CAN ID's map" << LOG_NOOP;
        }

        // Move the offset to the next IdsCanFrame
        offset += sizeof(brain::can_pdu::IdsCanFrame) + canFrame->candataSz;
    }

    LOG_DEBUG << "Done parsing IdsCanFrame, created: " << pduVec.size() << " CanPDU's" << LOG_NOOP;

    return true;
}
}  // namespace can_pdu
}  // namespace brain
