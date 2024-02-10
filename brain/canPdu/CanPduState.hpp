/**
 * @file      CanPduState.hpp
 * @brief     Definition of the CanPduState class
 */
#pragma once

#include <functional>
#include <list>
#include <map>
#include <memory>
#include <set>
#include <tuple>
#include <vector>

#include "CanPDU.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"

#include "brain/config/BrainConfigConstants.hpp"
#include "common/configuration/Configuration.hpp"

#include "autogen/nanopb/NanoPbInclude.hpp"

namespace brain
{
namespace can_pdu
{
using IdsState         = com_vwg_connect_ids_idsperiodicreport_v1_IdsState;
using ConfigurationPtr = common::configuration::Pointer;

// Classes that should be moved out of here
struct NSPduData
{
    uint32_t timestamp;
    uint8_t* payload;
    uint16_t size;
};

struct NSCanPduContext
{
    uint32_t                                     busId;
    uint32_t                                     canId;
    std::list<brain::can_pdu::CanPDU*>::iterator it;
    std::list<brain::can_pdu::CanPDU*>           pdus;
};

/**
 * @class State
 * @brief The State save backward and forward information about events.
          This class holds:
          - std::map<uint32_t, std::shared_ptr<NSCanPduContext>> m_fullStateCanPduContexMapping - This
            map manage all PDU's in this class.
 */

class CanPduState
{
public:
    /**
     * @fn      CanPduState() noexcept
     * @brief   constructor
     * @param   none
     * @return  none
     */
    CanPduState(ConfigurationPtr config) noexcept;

    /**
     * @fn      virtual ~CanPduState()
     * @brief   destructor
     * @param   none
     * @return  none
     */
    virtual ~CanPduState();

    /**
     * @fn      CanPDU* AddPdustream(CanPDU * const pdu)
     * @brief   Adding PDU stream to the vector and return it
     * @param   CanPDU * const pdu
     * @return  CanPDU*
     */
    brain::can_pdu::CanPDU* AddPdustream(brain::can_pdu::CanPDU* const pdu);

    /**
     * @fn      bool PrepareToShutdown() noexcept
     * @brief   Currently, do nothing.
     * @param   none
     * @return  Return always true
     */
    bool PrepareToShutdown() noexcept;

    /**
     * @fn      bool CancelPrepareToShutdown() noexcept;
     * @brief   Currently, do nothing.
     * @param   none
     * @return  Return always true
     */
    bool CancelPrepareToShutdown() noexcept;

    /**
     * @fn      size_t GetForwardPDUCount() noexcept
     * @brief   getter for the number of forwarded PDU
     * @param   none
     * @return  the number of forwarded PDU
     */
    size_t GetForwardPDUCount() noexcept;

    /**
     * @fn      IdsState GetAllStateData();
     * @brief   getter for the state data
     * @param   none
     * @return  IdsState - the state data
     */
    IdsState GetAllStateData();

    /**
     * @fn      void SetPeriodicStateDataFlag();
     * @brief   set the periodic flag
     * @param   const bool val
     * @return  none
     */
    void SetPeriodicStateDataFlag(const bool val);

    /**
     * @fn      void GetPeriodicStateDataFlag();
     * @brief   get the periodic flag value
     * @param   none
     * @return  bool val
     */
    bool GetPeriodicStateDataFlag();

    void CheckAndAddContext(uint32_t canId);

    void CheckAndRemoveContext(uint32_t canId);

private:
    static bool encodePduMapping(pb_ostream_t* const stream, const pb_field_t* const field, void* const* const arg);
    static bool encodePduContext(pb_ostream_t* const stream, const pb_field_t* const field, void* const* const arg);
    static bool encodePduPayload(pb_ostream_t* const stream, const pb_field_t* const field, void* const* const arg);

    static bool encodeStream(pb_ostream_t* const                                   stream,
                             pb_field_t const* const                               fields,
                             std::map<uint32_t, std::shared_ptr<NSCanPduContext>>& pduMap);

    std::map<uint32_t, std::shared_ptr<NSCanPduContext>> m_fullStateCanPduContexMapping;
    std::map<uint32_t, std::shared_ptr<NSCanPduContext>> m_filteredStateCanPduContexMapping;
    std::set<uint32_t>                                   m_statedCanIds;
    bool                                                 m_isPeriodic = false;
};
}  // namespace can_pdu
}  // namespace brain
