#pragma once
/**
 * @file
 * @brief This file contains the definition of the EthSensorData class and its functionality.
 */
#include <unordered_map>
#include "common/sensor_data/SensorData.hpp"
#include "common/utils/CPP/optional/Optional.hpp"
#include "rapidjson/document.h"

namespace brain
{
namespace sensor_data
{
/**
 * @class   EthSensorData
 * @brief   class which holds the data of Ethernet event
 */
class EthSensorData : public common::sensor_data::SensorData
{
public:
    enum class EthSensorProperties : uint8_t
    {
        TIMESTAMP = 0,
        ID,
        DOMAIN_TYPE,
        SENSOR_TYPE,
        DISCARDED,
        UNKNOWN_PROT,
        ILG_VLAN,
        ILG_IP,
        VLAN_INGRESS,
        VLAN_EGRESS,
        VLAN_LOOKUP,
        ACL_LOOKUP,
        IF_OUT_OCTETS,
        IF_IN_OCTETS,
        IF_OUT_MULTICAST_PKTS,
        IF_OUT_BROADCAST_PKTS,
        IF_OUT_DISCARDS,
        DIAG_FILTER,
        STATS_SIZE_UNDERSIZE,
        STATS_SIZE_64,
        STATS_SIZE_65_127,
        STATS_SIZE_128_255,
        STATS_SIZE_256_511,
        STATS_SIZE_512_1023,
        STATS_SIZE_1024_1518,
        STATS_SIZE_OVERSIZE
    };

    /**
     * @brief   Ctor
     * @param   rapidjson::Value const& parsedJson - json to build sd from
     * @param   bool& success - true for success, otherwise false.
     */
    EthSensorData(rapidjson::Value const& parsedJson, bool& success);

    /**
     * @brief   Ctor
     */
    EthSensorData() = default;

    /**
     * @brief   Fill SD data from json.
     * @param   rapidjson::Value const& parsedJson - json to fill sd from
     * @return  bool - true for success otherwise false.
     */
    bool FillFromJson(rapidjson::Value const& incidentJson);

    /**
    * @brief   Get the timestamp.
    * @return  const uint64_t& - The timestamp.
    */
    inline uint64_t const & GetTimestamp() const noexcept
    { 
        return m_timestamp;
    };

    /**
    * @brief   Set the timestamp.
    * @param   uint64_t inTimestamp - The time stamp to be set.
    */
    inline void SetTimestamp(uint64_t inTimestamp) noexcept
    { 
        m_timestamp = inTimestamp;
    };

    /**
    * @brief   Get the sensor ID.
    * @return  const std::string& - The sensor ID.
    */
    inline std::string const & GetID() const noexcept
    {
        return m_id;
    };

    /**
    * @brief   Set the sensor ID.
    * @param   std::string const& sensorID - the sensor ID to be set.
    */
    inline void SetID(std::string const& sensorID)
    {
        m_id = sensorID;
    };

    /**
    * @brief   Get the domain type.
    * @return  const cm::optional<std::string>& - The domain type.
    */
    inline cm::optional<std::string> const & GetDomainType() const noexcept
    {
        return m_domainType;
    };

    /**
    * @brief   Set the domain type.
    * @param   std::string const& domainType - the domain type to be set.
    */
    inline void SetDomainType(std::string const& domainType)
    {
        m_domainType = domainType;
    };

    /**
    * @brief   Get the sensor type.
    * @return  const cm::optional<std::string>& - The sensor type.
    */
    inline cm::optional<std::string> const & GetSensorType() const noexcept
    {
        return m_sensorType;
    };

    /**
    * @brief   Set the sensor type.
    * @param   std::string const& sensorType - the sensor type to be set.
    */
    inline void SetSensorType(std::string const& sensorType)
    {
        m_sensorType = sensorType;
    };

    /**
    * @brief   Get the discarded frames counter.
    * @return  const cm::optional<uint64_t>& - The discarded frames counter.
    */
    inline cm::optional<uint64_t> const & GetDiscardedFramesCounter() const noexcept
    {
        return m_discarded;
    };

    /**
    * @brief   Set the discarded frames counter.
    * @param   uint64_t discardedFrames - The discarded frames counter to be set.
    */
    inline void SetDiscardedFramesCounter(uint64_t discardedFrames) noexcept
    {
        m_discarded = discardedFrames;
    };

    /**
    * @brief   Get the unknown protocol dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The unknown protocol dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetUnknownProtocolDroppedFramesCounter() const noexcept
    {
        return m_unknownProt;
    };

    /**
    * @brief   Set the unknown protocol dropped frames counter.
    * @param   uint64_t unknownProt - The unknown protocol dropped frames counter to be set.
    */
    inline void SetUnknownProtocolDroppedFramesCounter(uint64_t unknownProt) noexcept
    {
        m_unknownProt = unknownProt;
    };

    /**
    * @brief   Get the illegal VLAN dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The illegal VLAN dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetIllegalVLANDroppedFramesCounter() const noexcept
    {
        return m_ilgVlan;
    };

    /**
    * @brief   Set the illegal VLAN dropped frames counter.
    * @param   uint64_t ilgVlan - The illegal VLAN dropped frames counter to be set.
    */
    inline void SetIllegalVLANDroppedFramesCounter(uint64_t ilgVlan) noexcept
    {
        m_ilgVlan = ilgVlan;
    };

    /**
    * @brief   Get the illegal IP dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The illegal IP dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetIllegalIPDroppedFramesCounter() const noexcept
    {
        return m_ilgIp;
    };

    /**
    * @brief   Set the illegal IP dropped frames counter.
    * @param   uint64_t ilgIp - The illegal IP dropped frames counter to be set.
    */
    inline void SetIllegalIPDroppedFramesCounter(uint64_t ilgIp) noexcept
    {
        m_ilgIp = ilgIp;
    };

    /**
    * @brief   Get the VLAN ingress dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The VLAN ingress dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetVLANIngressDroppedFramesCounter() const noexcept
    {
        return m_vlanIngress;
    };

    /**
    * @brief   Set the VLAN ingress dropped frames counter.
    * @param   uint64_t vlanIngress - The VLAN ingress dropped frames counter to be set.
    */
    inline void SetVLANIngressDroppedFramesCounter(uint64_t vlanIngress) noexcept
    {
        m_vlanIngress = vlanIngress;
    };

    /**
    * @brief   Get the VLAN egress dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The VLAN egress dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetVLANEgressDroppedFramesCounter() const noexcept
    {
        return m_vlanEgress;
    };

    /**
    * @brief   Set the VLAN egress dropped frames counter.
    * @param   uint64_t vlanEgress - The VLAN egress dropped frames counter to be set.
    */
    inline void SetVLANEgressDroppedFramesCounter(uint64_t vlanEgress) noexcept
    {
        m_vlanEgress = vlanEgress;
    };

    /**
    * @brief   Get the VLAN lookup dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The VLAN lookup dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetVLANLookupDroppedFramesCounter() const noexcept
    {
        return m_vlanLookup;
    };

    /**
    * @brief   Set the VLAN lookup dropped frames counter.
    * @param   uint64_t vlanLookup - The VLAN lookup dropped frames counter to be set.
    */
    inline void SetVLANLookupDroppedFramesCounter(uint64_t vlanLookup) noexcept
    {
        m_vlanLookup = vlanLookup;
    };

    /**
    * @brief   Get the ACL lookup dropped frames counter.
    * @return  const cm::optional<uint64_t>& - The ACL lookup dropped frames counter.
    */
    inline cm::optional<uint64_t> const & GetACLLookupDroppedFramesCounter() const noexcept
    {
        return m_aclLookup;
    };

    /**
    * @brief   Set the ACL lookup dropped frames counter.
    * @param   uint64_t aclLookup - The ACL lookup dropped frames counter to be set.
    */
    inline void SetACLLookupDroppedFramesCounter(uint64_t aclLookup) noexcept
    {
        m_aclLookup = aclLookup;
    };

    /**
    * @brief   Get the number of out octets.
    * @return  const cm::optional<uint64_t>& - The number of out octets.
    */
    inline cm::optional<uint64_t> const& GetIfOutOctetsCounter() const noexcept
    {
        return m_ifOutOctets;
    };

    /**
    * @brief   Set the number of out octets.
    * @param   uint64_t ifOutOctets - The number of out octets to be set.
    */
    inline void SetIfOutOctetsCounter(uint64_t ifOutOctets) noexcept
    {
        m_ifOutOctets = ifOutOctets;
    };

    /**
    * @brief   Get the number of in octets.
    * @return  const cm::optional<uint64_t>& - The number of in octets.
    */
    inline cm::optional<uint64_t> const& GetIfInOctetsCounter() const noexcept
    {
        return m_ifInOctets;
    };

    /**
    * @brief   Set the number of in octets.
    * @param   uint64_t ifOutOctets - The number of in octets to be set.
    */
    inline void SetIfInOctetsCounter(uint64_t ifInOctets) noexcept
    {
        m_ifInOctets = ifInOctets;
    };

    /**
    * @brief   Get the number of packets sized less than 64 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsUndersizePkts() const noexcept
    {
        return m_etherStatsUndersizePkts;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts64Octets - Number of packets to be set.
    */
    inline void SetEtherStatsUndersizePkts(uint64_t etherStatsUndersizePkts) noexcept
    {
        m_etherStatsUndersizePkts = etherStatsUndersizePkts;
    };

    /**
    * @brief   Get the number of packets sized 64 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsPkts64Octets() const noexcept
    {
        return m_etherStatsPkts64Octets;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts64Octets - Number of packets to be set.
    */
    inline void SetEtherStatsPkts64Octets(uint64_t etherStatsPkts64Octets) noexcept
    {
        m_etherStatsPkts64Octets = etherStatsPkts64Octets;
    };

    /**
    * @brief   Get the number of packets sized between 65 and 127 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsPkts65to127Octets() const noexcept
    {
        return m_etherStatsPkts65to127Octets;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts65to127Octets - Number of packets to be set.
    */
    inline void SetEtherStatsPkts65to127Octets(uint64_t etherStatsPkts65to127Octets) noexcept
    {
        m_etherStatsPkts65to127Octets = etherStatsPkts65to127Octets;
    };

    /**
    * @brief   Get the number of packets sized between 128 and 255 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsPkts128to255Octets() const noexcept
    {
        return m_etherStatsPkts128to255Octets;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts128to255Octets - Number of packets to be set.
    */
    inline void SetEtherStatsPkts128to255Octets(uint64_t etherStatsPkts128to255Octets) noexcept
    {
        m_etherStatsPkts128to255Octets = etherStatsPkts128to255Octets;
    };

    /**
    * @brief   Get the number of packets sized between 256 and 511 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsPkts256to511Octets() const noexcept
    {
        return m_etherStatsPkts256to511Octets;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts256to511Octets - Number of packets to be set.
    */
    inline void SetEtherStatsPkts256to511Octets(uint64_t etherStatsPkts256to511Octets) noexcept
    {
        m_etherStatsPkts256to511Octets = etherStatsPkts256to511Octets;
    };

    /**
    * @brief   Get the number of packets sized between 512 and 1023 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsPkts512to1023Octets() const noexcept
    {
        return m_etherStatsPkts512to1023Octets;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts512to1023Octets - Number of packets to be set.
    */
    inline void SetEtherStatsPkts512to1023Octets(uint64_t etherStatsPkts512to1023Octets) noexcept
    {
        m_etherStatsPkts512to1023Octets = etherStatsPkts512to1023Octets;
    };

    /**
    * @brief   Get the number of packets sized between 1024 and 1518 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsPkts1024to1518Octets() const noexcept
    {
        return m_etherStatsPkts1024to1518Octets;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsPkts1024to1518Octets - Number of packets to be set.
    */
    inline void SetEtherStatsPkts1024to1518Octets(uint64_t etherStatsPkts1024to1518Octets) noexcept
    {
        m_etherStatsPkts1024to1518Octets = etherStatsPkts1024to1518Octets;
    };

    /**
    * @brief   Get the number of packets bigger than 1518 octets.
    * @return  const cm::optional<uint64_t>& - Number of packets.
    */
    inline cm::optional<uint64_t> const& GetEtherStatsOversizePkts() const noexcept
    {
        return m_etherStatsOversizePkts;
    };

    /**
    * @brief   Set the number of packets.
    * @param   uint64_t etherStatsOversizePkts - Number of packets to be set.
    */
    inline void SetEtherStatsOversizePkts(uint64_t etherStatsOversizePkts) noexcept
    {
        m_etherStatsOversizePkts = etherStatsOversizePkts;
    };

     /**
    * @brief   Get the number of out multicast packets.
    * @return  const cm::optional<uint32_t>& - The number of out multicast packets.
    */
    inline cm::optional<uint32_t> const& GetIfOutMulticastPktsCounter() const noexcept
    {
        return m_ifOutMulticastPkts;
    };

    /**
    * @brief   Set the number of out multicast packets.
    * @param   uint32_t ifOutMulticastPkts - The number of out multicast packets to be set.
    */
    inline void SetIfOutMulticastPktsCounter(uint32_t ifOutMulticastPkts) noexcept
    {
        m_ifOutMulticastPkts = ifOutMulticastPkts;
    };

    /**
    * @brief   Get the number of out broadcast packets.
    * @return  const cm::optional<uint32_t>& - The number of out broadcast packets.
    */
    inline cm::optional<uint32_t> const& GetIfOutBroadcastPktsCounter() const noexcept
    {
        return m_ifOutBroadcastPkts;
    };

    /**
    * @brief   Set the number of out broadcast packets.
    * @param   uint32_t ifOutBroadcastPkts - The number of out broadcast packets to be set.
    */
    inline void SetIfOutBroadcastPktsCounter(uint32_t ifOutBroadcastPkts) noexcept
    {
        m_ifOutBroadcastPkts = ifOutBroadcastPkts;
    };

    /**
    * @brief   Get the count of frames drained out packet.
    * @return  const cm::optional<uint32_t>& - The count of frames drained out packet.
    */
    inline cm::optional<uint32_t> const& GetIfOutDiscardsCounter() const noexcept
    {
        return m_ifOutDiscards;
    };

    /**
    * @brief   Set the count of frames drained out packet.
    * @param   uint32_t ifOutDiscards - The count of frames drained out packet to be set.
    */
    inline void SetIfOutDiscardsCounter(uint32_t ifOutDiscards) noexcept
    {
        m_ifOutDiscards = ifOutDiscards;
    };

    /**
    * @brief   Get the diagFilter flag.
    * @return  const cm::optional<bool> const& - The diagFilter flag.
    */
    inline cm::optional<bool> const& GetDiagFilter() const noexcept
    {
        return m_diagFilter;
    };

    /**
    * @brief   Set the diagFilter flag.
    * @param   bool diagFilter - The new value.
    */
    inline void SetDiagFilter(bool diagFilter)
    {
        m_diagFilter = diagFilter;
    };

private:

    uint64_t                  m_timestamp;
    std::string               m_id;
    cm::optional<std::string> m_domainType;
    cm::optional<std::string> m_sensorType;
    cm::optional<uint64_t>    m_discarded;
    cm::optional<uint64_t>    m_unknownProt;
    cm::optional<uint64_t>    m_ilgVlan;
    cm::optional<uint64_t>    m_ilgIp;
    cm::optional<uint64_t>    m_vlanIngress;
    cm::optional<uint64_t>    m_vlanEgress;
    cm::optional<uint64_t>    m_vlanLookup;
    cm::optional<uint64_t>    m_aclLookup;
    cm::optional<uint64_t>    m_ifOutOctets;
    cm::optional<uint64_t>    m_ifInOctets;
    cm::optional<uint64_t>    m_etherStatsUndersizePkts;
    cm::optional<uint64_t>    m_etherStatsPkts64Octets;
    cm::optional<uint64_t>    m_etherStatsPkts65to127Octets;
    cm::optional<uint64_t>    m_etherStatsPkts128to255Octets;
    cm::optional<uint64_t>    m_etherStatsPkts256to511Octets;
    cm::optional<uint64_t>    m_etherStatsPkts512to1023Octets;
    cm::optional<uint64_t>    m_etherStatsPkts1024to1518Octets;
    cm::optional<uint64_t>    m_etherStatsOversizePkts;
    cm::optional<uint32_t>    m_ifOutMulticastPkts;
    cm::optional<uint32_t>    m_ifOutBroadcastPkts;
    cm::optional<uint32_t>    m_ifOutDiscards;
    cm::optional<bool>        m_diagFilter;
    static std::unordered_map<std::string, EthSensorProperties> const s_properties;
};
} // namespace sensor_data
} // namespace brain
