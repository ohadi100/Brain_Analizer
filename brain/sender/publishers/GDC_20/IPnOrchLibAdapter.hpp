/**
 * @file
 * @brief SSP Publisher implementation
 */
#ifndef IPNORCHLIB_ADAPTER_H
#define IPNORCHLIB_ADAPTER_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

namespace brain
{
namespace publishers
{
namespace ssp_publisher
{

/**
 * \brief Adapter class that wraps the PnOrchLib instance and implements PublusherInterface.
 */
class IPnOrchLibAdapter
{
public:
    /**
     * \brief Destructor
     */
    virtual ~IPnOrchLibAdapter() = default;

    /**
     * \brief Establishes a connection to dc-vehicle-manager and makes oderdownload and data-upload
     * fucntionalities.
     *
     * \return none
     */
    virtual void connect() = 0;

    /**
     * \brief Downloads the order from dc-vehicle-manager provided UUID of the order
     *
     * \return
     */
    virtual void order_download() = 0;

    /**
     * \brief Uploads the data to backend provided upload path.
     *
     * \return none
     */
    virtual void data_upload(const std::vector<uint8_t>& msgPayload) = 0;

    /**
     * \brief Add downaloaded order to the map.
     *
     * \return none
     */
    virtual void addOrder(const std::array<uint8_t, 16>& key, const std::string& order) = 0;

    /**
     * \brief Find the order stored in map.
     *
     * \return none
     */
    virtual std::string findOrder(const std::array<uint8_t, 16>& key) const = 0;

    /**
     * \brief Disconnects the PnOrchLib instance
     *
     * \return none
     */
    virtual void disconnect() = 0;
};

}  // namespace ssp_publisher
}  // namespace publishers
}  // namespace brain

#endif  // IPNORCHLIB_ADAPTER_H
