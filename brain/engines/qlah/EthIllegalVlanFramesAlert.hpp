/**
 * @file
 * @brief    This file contains the definition of QLAH Illegal Vlang Dropped Frames Counter Alert.
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

class EthIllegalVlanFramesAlert
  : public EventAlertBase
{
public:
    using CounterManagerPtr            = common::counters::CounterManagerPtr;
    using ConfigurationPtr             = common::configuration::Pointer;
    using EventCounter                 = common::counters::EventCounter;
    using CriticalEventAlert           = brain::sender_events::CriticalEventAlert;
    using lllegalVlangTable            = common::types::BoundedUnorderedMap<std::string, uint64_t>;
    using EthIllegalVlanFramesAlertPtr = std::unique_ptr<EthIllegalVlanFramesAlert>;

    /**
     * @brief Create a unique ptr Illegal vlan frame object
     *
     * @param   CounterManagerPtr debugCounters
     * @param   messageRepository - for sending events.
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @param   SPEventNoiseFilter eventNoiseFilter
     * @param   EventPriority priority
     * @return  returns EthUnknownProtocolAlert unique ptr
     */
    static EthIllegalVlanFramesAlertPtr
    CreateAlert(CounterManagerPtr                                 debugCounters,
                MessageRepositoryPtr                              messageRepository,
                EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                EventNoiseFilterPtr                               eventNoiseFilter,
                events::EventPriority                             priority = events::EventPriority::Important)
    {
        return EthIllegalVlanFramesAlertPtr(
            new EthIllegalVlanFramesAlert{debugCounters, messageRepository, reportSerializer, eventNoiseFilter, priority});
    }

    /**
     * @brief checks if unknown id count is changed than send the alert to backend
     *
     * @param id - unknown constraint protocol frame id
     * @param count - event count
     */
    void Update(std::string const& id, uint64_t count);

    /**
     * @brief Get the Illegal vlan table
     *
     * @return qlah Illegal vlan frame table
     */
    inline const lllegalVlangTable&
    GetllegalVlangTable()
    {
        return m_illegalVlangTable;
    }

private:
    EthIllegalVlanFramesAlert(CounterManagerPtr                                 debugCounters,
                              MessageRepositoryPtr                              messageRepository,
                              EngineEventSender::IDSPeriodicReportSerializerPtr reportSerializer,
                              EventNoiseFilterPtr                               eventNoiseFilter,
                              events::EventPriority priority = events::EventPriority::Important);

    void sendAlert(std::string const& id, uint64_t count);

    lllegalVlangTable m_illegalVlangTable;
};

}  // namespace qlah
}  // namespace engines
}  // namespace brain
