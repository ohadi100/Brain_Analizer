#include "common/utils/logger/Logger.hpp"

#include "EthSensorData.hpp" // implemented

using brain::sensor_data::EthSensorData;

static std::unordered_map<std::string, EthSensorData::EthSensorProperties>&&
initEthSensorDataProperties() noexcept
{
    static std::unordered_map<std::string, EthSensorData::EthSensorProperties> newMap{
        {"timestamp", EthSensorData::EthSensorProperties::TIMESTAMP},
        {"id", EthSensorData::EthSensorProperties::ID},
        {"domainType", EthSensorData::EthSensorProperties::DOMAIN_TYPE},
        {"sensorType", EthSensorData::EthSensorProperties::SENSOR_TYPE},
        {"discarded", EthSensorData::EthSensorProperties::DISCARDED},
        {"unknownProt", EthSensorData::EthSensorProperties::UNKNOWN_PROT},
        {"ilgVlan", EthSensorData::EthSensorProperties::ILG_VLAN},
        {"ilgIp", EthSensorData::EthSensorProperties::ILG_IP},
        {"vlanIngress", EthSensorData::EthSensorProperties::VLAN_INGRESS},
        {"vlanEgress", EthSensorData::EthSensorProperties::VLAN_EGRESS},
        {"vlanLookup", EthSensorData::EthSensorProperties::VLAN_LOOKUP},
        {"aclLookup", EthSensorData::EthSensorProperties::ACL_LOOKUP},
        {"ifOutOctets", EthSensorData::EthSensorProperties::IF_OUT_OCTETS},
        {"ifInOctets", EthSensorData::EthSensorProperties::IF_IN_OCTETS},
        {"ifOutMulticastPkts", EthSensorData::EthSensorProperties::IF_OUT_MULTICAST_PKTS},
        {"ifOutBroadcastPkts", EthSensorData::EthSensorProperties::IF_OUT_BROADCAST_PKTS},
        {"ifOutDiscards", EthSensorData::EthSensorProperties::IF_OUT_DISCARDS},
        {"diagFilter", EthSensorData::EthSensorProperties::DIAG_FILTER},
        {"etherStatsUndersizePkts", EthSensorData::EthSensorProperties::STATS_SIZE_UNDERSIZE},
        {"etherStatsPkts64Octets", EthSensorData::EthSensorProperties::STATS_SIZE_64},
        {"etherStatsPkts65To127Octets", EthSensorData::EthSensorProperties::STATS_SIZE_65_127},
        {"etherStatsPkts128To255Octets", EthSensorData::EthSensorProperties::STATS_SIZE_128_255},
        {"etherStatsPkts256To511Octets", EthSensorData::EthSensorProperties::STATS_SIZE_256_511},
        {"etherStatsPkts512To1023Octets", EthSensorData::EthSensorProperties::STATS_SIZE_512_1023},
        {"etherStatsPkts1024To1518Octets", EthSensorData::EthSensorProperties::STATS_SIZE_1024_1518},
        {"etherStatsOversizePkts", EthSensorData::EthSensorProperties::STATS_SIZE_OVERSIZE},
    };
    return std::move(newMap);
}
std::unordered_map<std::string, EthSensorData::EthSensorProperties> const EthSensorData::s_properties
    = initEthSensorDataProperties();


EthSensorData::EthSensorData(rapidjson::Value const& parsedJson, bool& success) :
    SensorData()
{
    success = FillFromJson(parsedJson);
}

bool EthSensorData::FillFromJson(rapidjson::Value const& incidentJson)
{
    if ((!(incidentJson.IsObject())) || (!(incidentJson.HasMember("timestamp"))) || (!(incidentJson.HasMember("id"))))
    {
        LOG_ERROR << "Missing 'timestamp' or 'id' members for EthSensorData" << LOG_NOOP;
        return false;
    }

    rapidjson::Value::ConstMemberIterator memberItr = incidentJson.MemberBegin();
    for (; memberItr != incidentJson.MemberEnd(); ++memberItr)
    {
        std::string const & property = memberItr->name.GetString();
        // TODO: define hash function in order to verify O(1)
        auto const & propertyItr = s_properties.find(property);
        if (propertyItr == s_properties.end())
        {
            LOG_WARNING << "Property '" << property << "' in EthSensorData, is unknown" << LOG_NOOP;
            continue;
        }

        switch (propertyItr->second)
        {
            case EthSensorProperties::TIMESTAMP:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'timestamp' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    return false;
                }
                m_timestamp = memberItr->value.GetUint64();
                break;

            case EthSensorProperties::ID:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'id' in EthSensorData, is not a string" << LOG_NOOP;
                    return false;
                }
                m_id = memberItr->value.GetString();
                break;

            case EthSensorProperties::DOMAIN_TYPE:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'domainType' in EthSensorData, is not a string" << LOG_NOOP;
                    break;
                }
                m_domainType = cm::optional<std::string>(memberItr->value.GetString());
                break;

            case EthSensorProperties::SENSOR_TYPE:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'sensorType' in EthSensorData, is not a string" << LOG_NOOP;
                    break;
                }
                m_sensorType = cm::optional<std::string>(memberItr->value.GetString());
                break;

            case EthSensorProperties::DISCARDED:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'discarded' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_discarded = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::UNKNOWN_PROT:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'unknownProt' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_unknownProt = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::ILG_VLAN:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'ilgVlan' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_ilgVlan = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::ILG_IP:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'ilgIp' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_ilgIp = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::VLAN_INGRESS:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'vlanIngress' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_vlanIngress = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::VLAN_EGRESS:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'vlanEgress' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_vlanEgress = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::VLAN_LOOKUP:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'vlanLookup' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_vlanLookup = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::ACL_LOOKUP:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'aclLookup' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_aclLookup = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::IF_OUT_OCTETS:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'ifOutOctets' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_ifOutOctets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::IF_IN_OCTETS:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'ifInOctets' in EthSensorData, is not a uint64 type" << LOG_NOOP;
                    break;
                }
                m_ifInOctets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_UNDERSIZE:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'etherStatsUndersizePkts' in EthSensorData, is not a uint64 type"
                                << LOG_NOOP;
                    break;
                }
                m_etherStatsUndersizePkts = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_64:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'etherStatsPkts64Octets' in EthSensorData, is not a uint64 type"
                                << LOG_NOOP;
                    break;
                }
                m_etherStatsPkts64Octets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_65_127:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'etherStatsPkts65to127Octets' in EthSensorData, is not a uint64 type"
                                << LOG_NOOP;
                    break;
                }
                m_etherStatsPkts65to127Octets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_128_255:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'etherStatsPkts128to255Octets' in EthSensorData, is not a uint64 type"
                                << LOG_NOOP;
                    break;
                }
                m_etherStatsPkts128to255Octets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_256_511:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'etherStatsPkts256to511Octets' in EthSensorData, is not a uint64 type"
                                << LOG_NOOP;
                    break;
                }
                m_etherStatsPkts256to511Octets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_512_1023:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING
                        << "The value for 'etherStatsPkts512to1023Octets' in EthSensorData, is not a uint64 type"
                        << LOG_NOOP;
                    break;
                }
                m_etherStatsPkts512to1023Octets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_1024_1518:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING
                        << "The value for 'etherStatsPkts1024to1518Octets' in EthSensorData, is not a uint64 type"
                        << LOG_NOOP;
                    break;
                }
                m_etherStatsPkts1024to1518Octets = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::STATS_SIZE_OVERSIZE:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'etherStatsOversizePkts' in EthSensorData, is not a uint64 type"
                                << LOG_NOOP;
                    break;
                }
                m_etherStatsOversizePkts = cm::optional<uint64_t>(memberItr->value.GetUint64());
                break;

            case EthSensorProperties::IF_OUT_MULTICAST_PKTS:
                if (!memberItr->value.IsUint())
                {
                    LOG_WARNING << "The value for 'ifOutMulticastPkts' in EthSensorData, is not a Uint type"
                                << LOG_NOOP;
                    break;
                }
                m_ifOutMulticastPkts = cm::optional<uint32_t>(memberItr->value.GetUint());
                break;

            case EthSensorProperties::IF_OUT_BROADCAST_PKTS:
                if (!memberItr->value.IsUint())
                {
                    LOG_WARNING << "The value for 'ifOutBroadcastPkts' in EthSensorData, is not a Uint type"
                                << LOG_NOOP;
                    break;
                }
                m_ifOutBroadcastPkts = cm::optional<uint32_t>(memberItr->value.GetUint());
                break;

            case EthSensorProperties::IF_OUT_DISCARDS:
                if (!memberItr->value.IsUint())
                {
                    LOG_WARNING << "The value for 'ifOutDiscards' in EthSensorData, is not a Uint type" << LOG_NOOP;
                    break;
                }
                m_ifOutDiscards = cm::optional<uint32_t>(memberItr->value.GetUint());
                break;


            case EthSensorProperties::DIAG_FILTER:
                if (!memberItr->value.IsBool())
                {
                    LOG_WARNING << "The value for 'diagFilter' in EthSensorData, is not a boolean type" << LOG_NOOP;
                    break;
                }
                m_diagFilter = cm::optional<bool>(memberItr->value.GetBool());
                break;

            default:
                LOG_WARNING << "Property '" << property << "' is unknown for EthSensorData" << LOG_NOOP;
                return false;
                break; // Only for parasoft, to ignore switch-case without break at the end.
        }
    }

    return true;
}
