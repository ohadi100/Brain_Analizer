/**
 * @file      CanSensor.hpp
 * @brief     Definition of the CanSensor class
 */
#pragma once

#include "CanPduData.hpp"

namespace brain
{
namespace can_pdu
{
/**
 * @class CanPduParser
 * @brief A class for parsing CAN Protocol Data Units (PDUs).
 *
 * The CanPduParser class provides functionality for parsing CAN PDUs and creating PDU objects from ETH Tunnel frames.
 */
class CanPduParser
{
public:
    /**
     * @brief Constructor for CanPduParser.
     * @param isCandisabled Whether CAN is disabled or not.
     * @param disabledCanIdsList A list of disabled CAN IDs.
     */
    CanPduParser();

    /**
     * @brief Destructor for CanPduParser.
     */
    ~CanPduParser();

    /**
     * @brief Parses a given IdsFrame and creates a vector of CanPDU objects.
     * @param frame The IdsFrame to parse.
     * @param pduVec The vector to store the created CanPDU objects.
     * @return True if parsing and creation were successful, false otherwise.
     */
    bool ParseAndCreatePdu(IdsFrame* frame, std::vector<brain::can_pdu::CanPDU*>& pduVec);

    /**
     * @brief Initializes the parser.
     */
    void ParserInit();

private:
    static constexpr uint32_t canIdMask = 0x1FFFFFFFU;

    std::vector<brain::can_pdu::CanMsgWhiteList> m_canMsgsWhite{}; /**< A list of CAN message white-list. */
    std::unordered_map<uint32_t, brain::can_pdu::CanMsg>
        m_canMsgsIntermediate{}; /**< A map of intermediate CAN messages. */
};

}  // namespace can_pdu
}  // namespace brain
