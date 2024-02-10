#include "common/utils/logger/Logger.hpp"

#include "HostSensorData.hpp" // implemented

using brain::sensor_data::HostSensorData;

static std::unordered_map<std::string, HostSensorData::HostSensorProperties>&&
initHostSensorDataProperties() noexcept
{
    static std::unordered_map<std::string, HostSensorData::HostSensorProperties> newMap{
        {"timestamp", HostSensorData::HostSensorProperties::TIMESTAMP},
        {"id", HostSensorData::HostSensorProperties::ID},
        {"domainType", HostSensorData::HostSensorProperties::DOMAIN_TYPE},
        {"sensorType", HostSensorData::HostSensorProperties::SENSOR_TYPE},
        {"missingAliveSig", HostSensorData::HostSensorProperties::MISSING_ALIVE_SIG},
        {"appUnexp", HostSensorData::HostSensorProperties::APP_UNEXP},
        {"authError", HostSensorData::HostSensorProperties::AUTH_ERROR},
        {"failedSgn1", HostSensorData::HostSensorProperties::FAILED_SGN1},
        {"cpuErrors", HostSensorData::HostSensorProperties::CPU_ERRORS},
        {"failedSgn2", HostSensorData::HostSensorProperties::FAILED_SGN2}};
    return std::move(newMap);
}
std::unordered_map<std::string, HostSensorData::HostSensorProperties> const HostSensorData::s_properties
    = initHostSensorDataProperties();

HostSensorData::HostSensorData(rapidjson::Value const& parsedJson, bool& success) :
    SensorData()
{
    success = FillFromJson(parsedJson);
}

bool HostSensorData::FillFromJson(rapidjson::Value const& incidentJson)
{
    if ((!(incidentJson.IsObject())) || (!(incidentJson.HasMember("timestamp"))) || (!(incidentJson.HasMember("id"))))
    {
        LOG_ERROR << "Missing 'timestamp' or 'id' members for HostSensorData" << LOG_NOOP;
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
            LOG_WARNING << "Property '" << property << "' is unknown for HostSensorData" << LOG_NOOP;
            return false;
        }

        switch (propertyItr->second)
        {
        case HostSensorProperties::TIMESTAMP:
                if (!memberItr->value.IsUint64())
                {
                    LOG_WARNING << "The value for 'timestamp' in HostSensorData, is not a uint64 type" << LOG_NOOP;
                    return false;
                }
                m_timestamp = memberItr->value.GetUint64();
                break;

            case HostSensorProperties::ID:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'id' in HostSensorData, is not a string" << LOG_NOOP;
                    return false;
                }
                m_id = memberItr->value.GetString();
                break;

            case HostSensorProperties::DOMAIN_TYPE:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'domainType' in HostSensorData, is not a string" << LOG_NOOP;
                    break;
                }
                m_domainType = cm::optional<std::string>(memberItr->value.GetString());
                break;

            case HostSensorProperties::SENSOR_TYPE:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'sensorType' in HostSensorData, is not a string" << LOG_NOOP;
                    break;
                }
                m_sensorType = cm::optional<std::string>(memberItr->value.GetString());
                break;

            case HostSensorProperties::MISSING_ALIVE_SIG:
                if (!memberItr->value.IsBool())
                {
                    LOG_WARNING << "The value for 'missingAliveSig' in HostSensorData, is not bool" << LOG_NOOP;
                    break;
                }
                m_missingAliveSig = cm::optional<bool>(memberItr->value.GetBool());
                break;

            case HostSensorProperties::APP_UNEXP:
                if (!memberItr->value.IsString())
                {
                    LOG_WARNING << "The value for 'appUnexp' in HostSensorData, is not a string" << LOG_NOOP;
                    break;
                }
                m_appUnexp = cm::optional<std::string>(memberItr->value.GetString());
                break;

            case HostSensorProperties::AUTH_ERROR:
                if (!memberItr->value.IsBool())
                {
                    LOG_WARNING << "The value for 'authError' in HostSensorData, is not bool" << LOG_NOOP;
                    break;
                }
                m_authError = cm::optional<bool>(memberItr->value.GetBool());
                break;

            case HostSensorProperties::FAILED_SGN1:
                if (!memberItr->value.IsUint())
                {
                    LOG_WARNING << "The value for 'failedSgn1' in HostSensorData, is not a uint type" << LOG_NOOP;
                    break;
                }
                m_failedSgn1 = cm::optional<uint16_t>(static_cast<uint16_t>(memberItr->value.GetUint()));
                break;

            case HostSensorProperties::CPU_ERRORS:
                if (!memberItr->value.IsUint())
                {
                    LOG_WARNING << "The value for 'cpuErrors' in HostSensorData, is not a uint type" << LOG_NOOP;
                    break;
                }
                m_cpuErrors = cm::optional<uint16_t>(static_cast<uint16_t>(memberItr->value.GetUint()));
                break;

            case HostSensorProperties::FAILED_SGN2:
                if (!memberItr->value.IsUint())
                {
                    LOG_WARNING << "The value for 'failedSgn2' in HostSensorData, is not a uint type" << LOG_NOOP;
                    break;
                }
                m_failedSgn2 = cm::optional<uint16_t>(static_cast<uint16_t>(memberItr->value.GetUint()));
                break;

            default:
                LOG_WARNING << "Property '" << property << "' is unknown for HostSensorData" << LOG_NOOP;
                return false;
                break; // Only for parasoft, to ignore switch-case without break at the end.
        }
    }

    return true;
}
