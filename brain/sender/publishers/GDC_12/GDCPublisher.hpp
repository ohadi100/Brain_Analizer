/**
 * @file
 * @brief GDC Publisher implementation
 */
#ifndef GDC_PUBLISHER_HPP
#define GDC_PUBLISHER_HPP

#include <mutex>

#include <factory/PersistentMemoryFactory.hpp>
#include "GDC/GDCAgent.hpp"
#include "common/counter_manager/CounterManager.hpp"
#include "sender/publishers/interface/PublisherInterface.hpp"
#include "common/utils/logger/Logger.hpp"
#include "sender/publishers/utils/message_size_check/ExceededMessageSizeCheck.hpp"
using namespace brain::publishers::utils;

namespace brain
{
namespace publishers
{
namespace gdc_publisher
{

static constexpr size_t   kMaxChunkSizeInBytes             = 1024U * 1024U;
static constexpr uint8_t  kResponseTimeoutSeconds          = 10U;

/**
 * @class   GDCPublisher
 * @brief   GDC Publisher implementation
 */
class GDCPublisher final : public PublisherInterface
{
public:
    using GdcAgentGenericHuge_data_eventData = vwg::services::connect::datacollector::odcagentgenerichuge::Data;
    using ChunkInfo                          = vwg::services::connect::datacollector::odcagentgenerichuge::ChunkInfo;
    using GDCAgent                           = brain::publishers::agents::GDCAgent;
    using ChangeModeCallback                 = std::function<void(PublisherInterface::EventType)>;
    using ConfigurationPtr                   = common::configuration::Pointer;

    /**
     * @brief   Constructor
     * @param   std::shared_ptr<common::memory::PersistentMemoryFactory> persistentMemoryFactory
     * @param   std::shared_ptr<common::counters::CounterManager> debugCounters
     */
    explicit GDCPublisher(std::shared_ptr<common::memory::PersistentMemoryFactory> persistentMemoryFactory,
                          std::shared_ptr<common::counters::CounterManager>        debugCounters,
                          ConfigurationPtr                                         configuration);

    /**
     * @brief   sends forward message from brain to GDC Master
     *
     *  GDCMaster will respond for each data send with an acknowledgement and transmission flags.
     *  Agent should modify next chunk sending according to the following table:
     *
     *      | Ack | Trans |               Result                   |
     *      |  0  |   0   | Stop for some time and resend OLD data |
     *      |  0  |   1   | Resend the old data      			   |
     *      |  1  |   0   | Stop for some time and send NEW data   |
     *      |  1  |   1   | Send new data      					   |
     *
     *  When no control message arrives, message is dropped.
     *
     * @param   std::vector<uint8_t> const & msgPayload
     * @return  size of bytes that sent. On failure -1 is returned
     */
    bool SendMessage(std::shared_ptr<std::vector<uint8_t>> msgPayload) override;

    /**
     * @brief   Get the reactor callback and start offering agent service
     * @param   std::function<void>EventType)
     * @return  true 
     */
    bool Connect(ChangeModeCallback callback) override;

    /**
     * @brief   stop offering agent service
     * @return  true 
     */
    bool Disconnect() override;

    inline const  SPExceededMessageSizeCheck GetExceededMessageSizeCheck() const
    {
        return m_exceededMessageSizeCheck;
    }

#ifdef TESTS
    inline void
    SetAllowedToSendData(bool const state) noexcept
    {
        m_gdcAgent.SetGDCMasterPermitsSend(state);
    }
    void AddCampaign(gdccommonlargedatatypes::AddCampaignRequest const& request)
    {
        m_gdcAgent.addCampaign(request);
    }
    void RemoveCampaign(::ara::stdtypes::String const& uuid)
    {
        m_gdcAgent.removeCampaign(uuid);
    }
#endif

private:
    /**
     * @brief   Send the output 'output' using the Field 'event'.
     * @param   Event & event
     * @param[in] fieldName Name of the Field, in string format.
     * @param   typename Event::SampleType const & output - the notification to send.
     * @return  none.
     */
    template <class Event>
    static void
    SendEvent(Event& event, typename Event::SampleType const& output)
    {
        // TODO change to LOG_VERBOSE level
        LOG_INFO << "Event is sent by GDCPublisher" << LOG_NOOP;
        event.Send(output);
    }

    GDCAgent                                                 m_gdcAgent;
    std::shared_ptr<common::memory::PersistentMemoryFactory> m_persistentMemoryFactory;
    std::shared_ptr<common::counters::EventCounter>          m_sendMessageCounter;
    ChangeModeCallback                                       m_callback;
    SPExceededMessageSizeCheck                               m_exceededMessageSizeCheck;

};

}  // namespace gdc_publisher
}  // namespace publishers
}  // namespace brain

#endif  // PROXY_PUBLISHER_HPP
