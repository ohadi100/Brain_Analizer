#pragma once

#include <list>
#include "autogen/nanopb/NanoPbInclude.hpp"
#include "common/utils/types/ConfigurationTypes.hpp"
namespace brain
{
namespace publishers
{
namespace utils
{

class ExceededMessageSizeCheck
{
public:
    using ConfigurationPtr = common::configuration::Pointer;

    struct ExceededMaxSizeEntry
    {
        uint64_t    droppedTimestamp{};
        std::size_t droppedMessageSize{};
    };

    explicit ExceededMessageSizeCheck(ConfigurationPtr configuration);

    /**
     * @brief verify if message size is valid can be sent to gdc
     * @param msgSize - gdc message size
     * @return true - message successfully sent
     * @return false - message can't be sent
     */
    bool IsValid(std::size_t msgSize);

    /**
     * @brief serialize the exceeded message size list
     * @param entry - list of exceeded message size entries
     * @return true - serialization was successfully
     * @return false - serialization failed
     * ToDo - Place Pb struct to compile on MEB (Protobuf common) IDSPPE-3176
     */

#ifndef MEB_PLATFORM
    bool Serialize(com_vwg_connect_ids_idsperiodicreport_v1_ExceededMaxMessageSizeToIepDropEntryList& entry);
#endif

    /**
     * @brief clear the exceeded entries values
     */
    inline void
    clear()
    {
        m_exeededSizeCnt = 0U;
        m_exceededEntries.clear();
    }

private:
// ToDo - Place Pb struct to compile on MEB (Protobuf common) IDSPPE-3176
#ifndef MEB_PLATFORM
    static bool encodeExceededMessageSizeEntries(pb_ostream_t* stream, pb_field_t const* fields, void* const* arg);
#endif

    uint32_t                        m_maxListSize{};
    uint32_t                        m_messageSize{};
    uint32_t                        m_exeededSizeCnt{};
    std::list<ExceededMaxSizeEntry> m_exceededEntries;
};

using SPExceededMessageSizeCheck = std::shared_ptr<brain::publishers::utils::ExceededMessageSizeCheck>;

}  // namespace utils
}  // namespace publishers
}  // namespace brain