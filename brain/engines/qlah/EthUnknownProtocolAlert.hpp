
/**
 * @file
 * @brief    This file contains the definition of QLAH Ethernet Unknown Protocol Dropped Frames Counter Alert.
 */
#pragma once

#include "EventAlertBase.hpp"
#include "common/utils/types/BoundedUnorderedMap.hpp"

namespace brain
{
namespace engines
{
namespace qlah
{

class EthUnknownProtocolAlert : public EventAlertBase
{
public:
    using CounterManagerPtr             = common::counters::CounterManagerPtr;
    using ConfigurationPtr              = common::configuration::Pointer;
    using EventCounter                  = common::counters::EventCounter;
    using UnknownProtocolTable          = common::types::BoundedUnorderedMap<std::string, uint64_t>;
    using EthUnknownProtocolAlertPtr    = std::unique_ptr<EthUnknownProtocolAlert>;

    /**
     * @brief Create a unique ptr Eth Unknown Protocol Alert object
     *
     * @param   CounterManagerPtr debugCounters
     * @param   messageRepository for sending events.
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   SPEventNoiseFilter eventNoiseFilter
     * @param   EventPriority priority
     * @return  returns EthUnknownProtocolAlert unique ptr
     */
    static EthUnknownProtocolAlertPtr
    CreateAlert(CounterManagerPtr                                 debugCounters,
                MessageRepositoryPtr                              messageRepository,
                EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                EventNoiseFilterPtr                               eventNoiseFilter,
                events::EventPriority                             priority = events::EventPriority::Important)
    {
        return EthUnknownProtocolAlertPtr(
            new EthUnknownProtocolAlert{debugCounters, messageRepository, reportSerializer, eventNoiseFilter, priority});
    }

    /**
     * @brief checks if unknown id count is changed than send the alert to backend
     *
     * @param id - unknown constraint protocol frame id
     * @param count - event count
     */
    void Update(std::string const& id, uint64_t count);

    /**
     * @brief Get the Uknown Protocol Table object
     *
     * @return qlah unknown protocol frame table
     */
    inline const UnknownProtocolTable&
    GetUnknownProtocolTable()
    {
        return m_unknownProtocolTable;
    }

private:
    EthUnknownProtocolAlert(CounterManagerPtr                                 debugCounters,
                            MessageRepositoryPtr                              messageRepository,
                            EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                            EventNoiseFilterPtr                               eventNoiseFilter,
                            events::EventPriority priority = events::EventPriority::Important);

    void sendAlert(std::string const& id, uint64_t count);

    UnknownProtocolTable m_unknownProtocolTable;
};

}  // namespace qlah
}  // namespace engines
}  // namespace brain
