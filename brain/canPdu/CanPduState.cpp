/**
 * @file      CanPduState.cpp
 * @brief     This file contains the functionality of the State class

 */
#include "CanPduState.hpp"
#include "brain/utils/nanopb/Encoders.hpp"

using brain::can_pdu::CanPDU;
using brain::can_pdu::CanPduState;
using brain::can_pdu::IdsState;

namespace nanopb
{
    using CanPduContext = com_vwg_connect_ids_idsperiodicreport_v1_CanPduContext;
    using PduData = com_vwg_connect_ids_idsperiodicreport_v1_PduData;
    using Bucket = com_vwg_connect_ids_idsperiodicreport_v1_Bucket;
}

CanPduState::CanPduState(ConfigurationPtr config) noexcept : m_fullStateCanPduContexMapping()
{
    m_statedCanIds.clear();
    std::vector<uint32_t> m_statedCanIdsVec;
    static_cast<void>(config->GetValue(brain::config_keys::CAN_ALGORITHM_STATED_CAN_IDS, m_statedCanIdsVec));

    for (auto &element : m_statedCanIdsVec)
    {
        m_statedCanIds.insert(element);
    }
}

CanPduState::~CanPduState()
{
    for (auto &pair : m_fullStateCanPduContexMapping)
    {
        for (CanPDU *const pduPtr : pair.second->pdus)
        {
            CanPDU::Release(pduPtr);
        }
        pair.second->pdus.clear();
    }
    m_fullStateCanPduContexMapping.clear();

    for (auto &pair : m_filteredStateCanPduContexMapping)
    {
        for (CanPDU *const pduPtr : pair.second->pdus)
        {
            CanPDU::Release(pduPtr);
        }
        pair.second->pdus.clear();
    }
    m_filteredStateCanPduContexMapping.clear();
}

CanPDU *CanPduState::AddPdustream(CanPDU *const pdu)
{
    auto const mapIter = m_fullStateCanPduContexMapping.find(pdu->GetMsgId());
    std::shared_ptr<NSCanPduContext> context;

    if (m_fullStateCanPduContexMapping.end() == mapIter)
    {
        // Insert to mapping
        context = std::make_shared<NSCanPduContext>();

        context->canId = pdu->GetMsgId();
        context->busId = pdu->GetBusId();
        context->it = std::list<CanPDU *>::iterator{};
        m_fullStateCanPduContexMapping[pdu->GetMsgId()] = context;
    }
    else
    {
        context = mapIter->second;
        // Remove oldest pdu if needed
        if (MAX_NUM_PDUS_TO_SAVE <= context->pdus.size())
        {
            CanPDU::Release(context->pdus.front());
            context->pdus.pop_front();
        }
    }

    // Add pdu
    context->pdus.push_back(pdu);

    if ((NUM_OF_FORWARD_PDUS + 1) == context->pdus.size())
    {
        context->it = context->pdus.begin();
    }

    if ((NUM_OF_FORWARD_PDUS + 1) < context->pdus.size())
    {
        // ASF -Advance the iterator to achieve O(1) access when needed
        ++context->it;
    }

    if ((NUM_OF_FORWARD_PDUS + 1U) > context->pdus.size())
    {
        return nullptr;
    }

    // Check if the CAN ID is in the filtered list and add the context to the filtered map
    if (m_statedCanIds.find(context->canId) != m_statedCanIds.end())
    {
        m_filteredStateCanPduContexMapping[context->canId] = context;
    }

    return *(context->it);
}

void CanPduState::CheckAndAddContext(uint32_t canId)
{
    // Check if the anomaly CAN ID is in the stated set if it not found, add match context
    if (m_statedCanIds.find(canId) != m_statedCanIds.end())
    {
        return;
    }

    auto const mapIter = m_fullStateCanPduContexMapping.find(canId);

    if (m_fullStateCanPduContexMapping.end() != mapIter)
    {
        m_filteredStateCanPduContexMapping[canId] = mapIter->second;
    }
}

void CanPduState::CheckAndRemoveContext(uint32_t canId)
{
    // Check if the anomaly CAN ID is in the stated set if it not found, remove match context
    if (m_statedCanIds.find(canId) != m_statedCanIds.end())
    {
        return;
    }

    auto const mapIter = m_filteredStateCanPduContexMapping.find(canId);

    if (m_filteredStateCanPduContexMapping.end() != mapIter)
    {
        m_filteredStateCanPduContexMapping.erase(canId);
    }
}

size_t CanPduState::GetForwardPDUCount() noexcept
{
    return NUM_OF_FORWARD_PDUS;
}

IdsState CanPduState::GetAllStateData()
{
    LOG_DEBUG << "Called GetAllStateData" << LOG_NOOP;

    IdsState state = com_vwg_connect_ids_idsperiodicreport_v1_IdsState_init_default;
    state.pduStream.funcs.encode = encodePduMapping;
    state.pduStream.arg = this;

    return state;
}

bool CanPduState::encodePduMapping(pb_ostream_t *const stream, pb_field_t const *const fields, void *const *const arg)
{
    auto const &self = *reinterpret_cast<CanPduState *const *>(arg);
    if (!self)
    {
        return false;
    }

    if (true == self->GetPeriodicStateDataFlag())
    {
        return encodeStream(stream, fields, self->m_filteredStateCanPduContexMapping);
    }
    else
    {
        return encodeStream(stream, fields, self->m_fullStateCanPduContexMapping);
    }

    return true;
}

bool CanPduState::encodeStream(pb_ostream_t *const stream, pb_field_t const *const fields, std::map<uint32_t, std::shared_ptr<NSCanPduContext>> &pduMap)
{
    for (auto const &context : pduMap)
    {
        auto nsCanPduCtx = context.second;
        nanopb::CanPduContext pduCtx = {nsCanPduCtx->canId, nsCanPduCtx->busId, nullptr, nullptr};
        pduCtx.pduContexts.funcs.encode = encodePduContext;
        pduCtx.pduContexts.arg = static_cast<void *>(&nsCanPduCtx->pdus);

        if ((!pb_encode_tag_for_field(stream, fields)) ||
            (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_CanPduContext_fields, &pduCtx)))
        {
            return false;
        }
    }
    return true;
}

bool CanPduState::encodePduContext(pb_ostream_t *const stream, pb_field_t const *const fields, void *const *const arg)
{
    auto const &nsPdu_p = reinterpret_cast<decltype(NSCanPduContext::pdus) *const *>(arg);
    if ((!nsPdu_p) || (!(*nsPdu_p)))
    {
        return false;
    }

    auto const &nsPdus = **nsPdu_p;
    for (auto const &nsPdu : nsPdus)
    {
        nanopb::PduData pdu = {nsPdu->GetTimestamp(), nullptr, nullptr};
        pdu.payload.funcs.encode = encodePduPayload;
        pdu.payload.arg = (void *)&nsPdu;

        if ((!pb_encode_tag_for_field(stream, fields)) ||
            (!pb_encode_submessage(stream, com_vwg_connect_ids_idsperiodicreport_v1_PduData_fields, &pdu)))
        {
            return false;
        }
    }
    return true;
}

bool CanPduState::encodePduPayload(pb_ostream_t *const stream, pb_field_t const *const fields, void *const *const arg)
{
    auto const &nsPdu_p = reinterpret_cast<CanPDU **const *>(arg);
    if ((!nsPdu_p) || (!(*nsPdu_p)))
    {
        return false;
    }

    auto const &nsPdu = ***nsPdu_p;
    if ((!pb_encode_tag_for_field(stream, fields)) ||
        (!pb_encode_string(stream, nsPdu.GetPayload(), nsPdu.GetSize())))
    {
        return false;
    }
    return true;
}

bool CanPduState::PrepareToShutdown() noexcept
{
    return true;
}

bool CanPduState::CancelPrepareToShutdown() noexcept
{
    return true;
}

void CanPduState::SetPeriodicStateDataFlag(const bool val)
{
    m_isPeriodic = val;
}

bool CanPduState::GetPeriodicStateDataFlag()
{
    return m_isPeriodic;
}