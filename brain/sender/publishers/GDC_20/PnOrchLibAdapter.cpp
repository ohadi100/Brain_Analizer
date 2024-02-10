#include "PnOrchLibAdapter.hpp"
#include <chrono>
#include <cstring>
#include "IPnOrchControl.h"
#include "common/utils/logger/Logger.hpp"

using vwg::gdcpn_orch::api::IDownloadOrder;

namespace brain
{
namespace publishers
{
namespace ssp_publisher
{

PnOrchLibAdapter::PnOrchLibAdapter(uint16_t agentId, vwg::gdcpn_orch::api::IPnOrchControl& pnOrchControl)
  : mPnOrchControl(pnOrchControl)
  , mAgentId(agentId)
{
    memset(mOrderUUID.data(), 0xff, mOrderUUID.size());
}

void
PnOrchLibAdapter::connect()
{
    vwg::gdcpn_orch::api::DcpnConfig dcpnConfig{};
    dcpnConfig.agentId              = mAgentId;
    dcpnConfig.version              = {0U, 0U, 1U};
    dcpnConfig.maxConfigurationSize = 10000U;
    dcpnConfig.totalResources       = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    mPnOrchControl.initConstants(dcpnConfig);

    auto startResult = mPnOrchControl.start();

    LOG_INFO << "PnOrchLibAdapter started." << startResult << LOG_NOOP;
}

void
PnOrchLibAdapter::order_download()
{
    memset(mOrderUUID.data(), 0xff, mOrderUUID.size());
    auto& downloader = mPnOrchControl.getPnOrchOperation().getDownloadOrder();

    IDownloadOrder::Result downloadResponse{IDownloadOrder::Result::Status::ORDER_NOT_AVAILABLE, {}, {}};

    // Keep trying to download the order until it's available
    while (downloadResponse.status != IDownloadOrder::Result::Status::SUCCESS)
    {
        LOG_INFO << "Trying to download the order..." << LOG_NOOP;
        downloadResponse = downloader.download(mOrderUUID);
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    addOrder(mOrderUUID, downloadResponse.processingConfig);

    LOG_INFO << "PnOrchLibAdapter orderDownloaded." << LOG_NOOP;
}

void
PnOrchLibAdapter::data_upload(const std::vector<uint8_t>& msgPayload)
{
    static_cast<void>(msgPayload);
    // TODO:
}

void
PnOrchLibAdapter::addOrder(const std::array<uint8_t, 16>& key, const std::string& order)
{
    std::lock_guard<std::mutex> lock(mMutex);
    mOrder[key] = order;
}

std::string
PnOrchLibAdapter::findOrder(const std::array<uint8_t, 16>& key) const
{
    std::lock_guard<std::mutex> lock(mMutex);
    auto                        it = mOrder.find(key);
    if (it != mOrder.end())
    {
        return it->second;
    }
    else
    {
        return "Order not found";
    }
}

void
PnOrchLibAdapter::disconnect()
{
    mPnOrchControl.stop();
}

}  // namespace ssp_publisher
}  // namespace publishers
}  // namespace brain
