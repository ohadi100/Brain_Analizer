#include "state_notification_lib/component_client.hpp"

#include "PowerStateAdapter.hpp"
#include "Logger.hpp"

using brain::power_state::PowerStateAdapter;

static const ara::stm::ComponentState compClientkPrepSD{"kPrepSD"};
static const ara::stm::ComponentState compClientkOn{"kOn"};

PowerStateAdapter::PowerStateAdapter(SwitchStateCallBack switchStateCb,
                                     std::string const& idsComponentName):
                                     m_switchStateCb(switchStateCb),
                                     m_idsComponentName(idsComponentName)
{}

void PowerStateAdapter::Register()
{
    ara::stm::ComponentClient::Callback_t callback =
        [this](ara::stm::ComponentClient const& componentClient,
               uint32_t sequenceNumber,
               ara::stm::ComponentState const& state)
    {
        if (state != compClientkPrepSD && state != compClientkOn)            
        {
            LOG_ERROR << "ara::stm::ComponentClient::Callback_t - sequence: " << sequenceNumber << ", Wrong state received: " << state << LOG_NOOP;
            componentClient.ConfirmComponentState(sequenceNumber, state, ara::stm::ComponentClientReturnType::kInvalid);
            return;
        }

        m_switchStateCb(state);
        LOG_INFO << "ara::stm::ComponentClient::Callback_t - sequence: " << sequenceNumber << ", Updating to state: " << state << LOG_NOOP;
        componentClient.ConfirmComponentState(sequenceNumber, state, ara::stm::ComponentClientReturnType::kSuccess);
    };

    std::ignore = ara::stm::createComponentClient(m_idsComponentName, callback);
    LOG_INFO << "Componennt Client interface initialized, IDS Component name: " << m_idsComponentName << LOG_NOOP;
}
