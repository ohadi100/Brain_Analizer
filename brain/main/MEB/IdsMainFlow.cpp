#include "IdsMainFlow.hpp"
#include <string>
#include "Configuration.hpp"
#include "IdsProxyPublisher.hpp"
#include "Logger.hpp"

namespace brain
{
namespace main_flow
{

static constexpr char                             ICAS1_STATE_ON[]{"kOn"};
static constexpr char                             ICAS1_STATE_OFF[]{"kPrep"};
static constexpr char                             IDS_NAME_ICAS1[] = "brain";
static constexpr uint32_t                         IDS_ID_ICAS1{6004U};
static const IdsMainFlowBase::ConfigFilePaths     CONFIG_FILE_PATHS{{"/usr/local/brain_meb_config.json"}};
static const IdsMainFlowBase::MessageQueuesConfig MSG_QUEUES_CONFIG{{4U, 100U}, {4U, 100U}, {2U, 10U}, {1U, 40U}};

IdsMainFlow::IdsMainFlow()
  : IdsMainFlowBase()
{
    buildDomainObjects(IDS_NAME_ICAS1, IDS_ID_ICAS1, CONFIG_FILE_PATHS, [this](const std::string& state) {
        if (state == ICAS1_STATE_ON)
        {
            suspendIds();
            return true;
        }

        if (state == ICAS1_STATE_OFF)
        {
            resumeIds();
            return false;
        }

        LOG_ERROR << "Power Switch call back called with unknown State: " << state << LOG_NOOP;
        return false;
    });

    // Building chani from end to start 
    auto proxy_publisher = std::make_unique<publishers::ids_proxy_someip::IdsProxyPublisher>();
    buildCommunicatorChain(buildEngineChain(buildSendChain(std::move(proxy_publisher), MSG_QUEUES_CONFIG)));
}

}  // namespace main_flow
}  // namespace brain
