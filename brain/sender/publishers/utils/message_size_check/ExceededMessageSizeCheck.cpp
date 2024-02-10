#include "ExceededMessageSizeCheck.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "brain/utils/nanopb/Encoders.hpp"
#include "common/utils/os/time/Time.hpp"
#include "common/configuration/Configuration.hpp"

using brain::publishers::utils::ExceededMessageSizeCheck;

ExceededMessageSizeCheck::ExceededMessageSizeCheck(ConfigurationPtr configuration)
{
    static constexpr uint32_t DEFAULT_GDC_MAXIMUM_MESSAGE_SIZE{256U * 1024U};
    static constexpr uint16_t GDC_MAXIMUM_DROP_ENTRIES_SIZE{100U};

    m_maxListSize = DEFAULT_GDC_MAXIMUM_MESSAGE_SIZE;
    m_messageSize = GDC_MAXIMUM_DROP_ENTRIES_SIZE;

    if (configuration)
    {
        std::ignore = configuration->GetValue(config_keys::GDC_MAXIMUM_MESSAGE_SIZE, m_maxListSize);
        std::ignore = configuration->GetValue(config_keys::GDC_MAXIMUM_DROP_ENTRIES_SIZE, m_messageSize);
    }
}

bool
ExceededMessageSizeCheck::IsValid(std::size_t msgSize)
{
    if (msgSize <= m_maxListSize)
    {
        return true;
    }
    else
    {
        if (m_exceededEntries.size() > m_messageSize)
        {
            ++m_exeededSizeCnt;
        }
        else
        {
            const ExceededMaxSizeEntry entry{common::Time::GetCurrentTimeMilliSec(), msgSize};
            m_exceededEntries.emplace_back(entry);
        }

        return false;
    }
}

#ifndef MEB_PLATFORM
bool
ExceededMessageSizeCheck::Serialize(
    com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntryList& entry)
{
    if (!m_exceededEntries.empty())
    {
        entry.ExceededAllowedListSize                            = m_exeededSizeCnt;
        entry.exceededMaxMessageSizeToIepDropEntrys.funcs.encode = &encodeExceededMessageSizeEntries;
        entry.exceededMaxMessageSizeToIepDropEntrys.arg          = static_cast<void*>(&m_exceededEntries);

        return true;
    }

    return false;
}

bool
ExceededMessageSizeCheck::encodeExceededMessageSizeEntries(pb_ostream_t*     stream,
                                                           pb_field_t const* fields,
                                                           void* const*      arg)
{
    if ((nullptr != arg) && (nullptr != *arg))
    {
        auto const& entries = **reinterpret_cast<std::list<ExceededMaxSizeEntry>* const*>(arg);

        for (auto const& entry : entries)
        {
            com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntry message
                = com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntry_init_default;

            message.droppedTimestamp   = entry.droppedTimestamp;
            message.droppedMessageSize = entry.droppedMessageSize;

            if (!pb_encode_tag_for_field(stream, fields)
                || (!pb_encode_submessage(
                    stream,
                    com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntry_fields,
                    &message)))
            {
                return false;
            }
        }

        return true;
    }

    return false;
}
#endif
