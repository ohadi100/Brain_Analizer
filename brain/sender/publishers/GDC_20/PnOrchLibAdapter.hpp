#include <mutex>
#include <unordered_map>
#include "IPnOrchControl.h"
#include "IPnOrchLibAdapter.hpp"

namespace std
{
template <>
class hash<std::array<unsigned char, 16>>
{
public:
    size_t
    operator()(const std::array<unsigned char, 16>& arr) const
    {
        size_t           hash_val     = 0;
        constexpr size_t MAGIC_NUMBER = 0x9e3779b9;
        for (const auto& val : arr)
        {
            hash_val ^= std::hash<unsigned char>{}(val) + MAGIC_NUMBER + (hash_val << 6) + (hash_val >> 2);
        }
        return hash_val;
    }
};
}  // namespace std

namespace brain
{
namespace publishers
{
namespace ssp_publisher
{

/**
 * \brief Adapter class forwarding calls to the proprietary VIConnector class.
 */
class PnOrchLibAdapter final : public IPnOrchLibAdapter
{
public:
    /**
     * \brief Creates PnOrchLibAdapter
     *
     * \param[in] x
     */
    PnOrchLibAdapter(uint16_t agentId, vwg::gdcpn_orch::api::IPnOrchControl& pnOrchControl);
    virtual ~PnOrchLibAdapter() = default;

private:
    virtual void        connect() override;
    virtual void        order_download() override;
    virtual void        data_upload(const std::vector<uint8_t>& msgPayload) override;
    virtual void        disconnect() override;
    virtual void        addOrder(const std::array<uint8_t, 16>& key, const std::string& order) override;
    virtual std::string findOrder(const std::array<uint8_t, 16>& key) const override;

    //! Real PnOrchLib instance to which all incoming calls are forwarded.
    vwg::gdcpn_orch::api::IPnOrchControl& mPnOrchControl;

    std::array<uint8_t, 16>                                  mOrderUUID;
    std::unordered_map<std::array<uint8_t, 16>, std::string> mOrder;
    mutable std::mutex                                       mMutex;
    uint16_t                                                 mAgentId;
};


}  // namespace ssp_publisher
}  // namespace publishers
}  // namespace brain
