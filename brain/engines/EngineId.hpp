/**
 * @file
 * @brief     Tags enum for all supported sensor data types
*/
#ifndef ENGINE_ID_TAG_HPP
#define ENGINE_ID_TAG_HPP

namespace brain
{
namespace engines
{

/**
 * @class   EngineId
 * @brief   Engine ids
 */
enum class EngineId : uint8_t
{
    PERIODIC_STATISTICS = 0U,
    SWPAC_KERNEL_LOG,
    SWPAC_TLS_ERROR_REPORT,
    SWPAC_PROCESS_PERFORMANCE,
    SWPAC_UNKNOWN_CONSTRAINT_ID,
    QLAH_ETH,
    QLAH_HOST,
    SECURITY_EVENT,
    INTELLIGENT_SENSOR,
    SACID_EVENT,
    
    SD_NUMBER_OF_TAGS
};

} // namespace brain
} // namespace engines

#endif /* ENGINE_ID_TAG_HPP */
