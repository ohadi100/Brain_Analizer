#pragma once

#include "brain/engines/CriticalAlertFilter.hpp"
#include "brain/engines/serializer/IDSPeriodicReportSerializer.hpp"
#include "brain/noise_filter/event_noise_filter/EventNoiseFilter.hpp"
#include "common/utils/types/MessageRepositoryTypes.hpp"

namespace brain
{

namespace brain_noise_filter
{
class EventNoiseFilter;
}

namespace sender_events
{
enum class CriticalEventAlert : uint16_t;
}

namespace engines
{

/**
 * @class   EngineCreateEvent
 * @brief   Base class for engines that send events to the backend
 */
class EngineEventSender
{
public:
    static constexpr uint32_t EVENT_MAX_SIZE = 120U * 1024U;

    enum class SendStatus : uint8_t
    {
        Success,
        NoiseFilterError,
        EmptyRuleEval,
        Failed
    };

    using EventNoiseFilterPtr            = std::shared_ptr<brain::brain_noise_filter::EventNoiseFilter>;
    using SensorDataTag                  = common::sensor_data::SensorDataTag;
    using SecurityEventFrame             = brain::engines::security_events::SecurityEventFrame;
    using MessageRepositoryPtr           = brain::messageRepository::MessageRepositoryPtr;
    using IDSPeriodicReportSerializerPtr = brain::engines::IDSPeriodicReportSerializerPtr;

    /**
     * @brief Constructs an Engine Event Sender object from given priority, sender, and noise filter.
     *
     * that is used to send events to backend.
     *
     * @note if not given noise filter, will use no noise filter
     *
     * @param   EventPriority priority - sender priority
     * @param   MessageRepositoryPtr  msgRepository - message sender object
     * @param   EventNoiseFilter eventNoiseFilter - events noise filter object
     * @param   reportSerializer - class to serialize idsperiodicreport proto object
     * @return  none
     */
    EngineEventSender(events::EventPriority          priority,
                      MessageRepositoryPtr           msgRepository,
                      IDSPeriodicReportSerializerPtr reportSerializer,
                      EventNoiseFilterPtr            eventNoiseFilter = nullptr);

    /**
     * @brief   Destructor
     */
    virtual ~EngineEventSender() = default;

    /**
     * @brief    default copy constructor
     */
    EngineEventSender(const EngineEventSender& other) = delete;

    /**
     * @brief    default move constructor
     */
    EngineEventSender(EngineEventSender&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    EngineEventSender& operator=(EngineEventSender const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    EngineEventSender& operator=(EngineEventSender&&) = delete;

    /**
     * @brief send event to backend
     *
     * @param ruleEval - ids periodic report rule evaluation proto
     * @param sdTag - sensor data tag enum
     * @param event - critical event alert enum
     * @param frame - security events frame struct
     * @param eventSize - serialized rule data size
     * @return SendStatus - sent status
     */
    SendStatus SendEvent(com_vwg_connect_ids_idsperiodicreport_v1_RuleEvaluation const& ruleEval,
                         SensorDataTag                                                  sdTag,
                         brain::sender_events::CriticalEventAlert                       event,
                         SecurityEventFrame                                             frame = {},
                         size_t const eventSize = EngineEventSender::EVENT_MAX_SIZE);

protected:
    /**
     * @brief send event to backend
     *
     * @param serializedRuleEval - serialized rule data
     * @param sdTag - sensor data tag enum
     * @param eventSize - serialized rule data size
     * @return SendStatus - sent status
     */
    SendStatus SendUnfilteredEvent(cm::optional<std::vector<uint8_t>> const& serializedRuleEval,
                                   SensorDataTag                             sdTag,
                                   size_t                                    eventSize);

    IDSPeriodicReportSerializerPtr m_reportSerializer;

private:
    SendStatus CanSendNoiseFilter(SensorDataTag       sdTag,
                                  size_t              eventSize = EngineEventSender::EVENT_MAX_SIZE) const;

    events::EventPriority          m_priority{};
    MessageRepositoryPtr           m_messageRepository;
    EventNoiseFilterPtr            m_eventNoiseFilter;
};
}  // namespace engines
}  // namespace brain
