#include "common/utils/logger/Logger.hpp"

#include "TLSErrorReportSensorData.hpp"  // implemented

using namespace brain::sensor_data;

TLSErrorReportSensorData::TLSErrorReportSensorData(bool&                   success,
                                                   rapidjson::Value const& parsedJson,
                                                   ConstraintId            constraintId)
  : SensorData()
  , SwpacSensorDataBase(constraintId)
{
    success = FillFromJson(parsedJson);
}

bool
TLSErrorReportSensorData::FillFromJson(rapidjson::Value const& dataItems)
{
    if (!dataItems.IsArray())
    {
        LOG_ERROR << "Input must be a JSON array" << LOG_NOOP;
        return false;
    }

    bool retVal = false;
    for (rapidjson::Value::ConstValueIterator dataItemItr = dataItems.Begin(); dataItemItr != dataItems.End();
         ++dataItemItr)
    {
        auto const& metaIdIt = dataItemItr->FindMember("reference");
        auto const& valueIt  = dataItemItr->FindMember("value");

        if ((metaIdIt == dataItemItr->MemberEnd()) || (valueIt == dataItemItr->MemberEnd())
            || !metaIdIt->value.IsString() || !valueIt->value.IsArray())
        {
            LOG_WARNING << "Missing 'reference' or 'value' members for TLSErrorReportSensorData" << LOG_NOOP;
            continue;
        }

        auto const&              reference{metaIdIt->value.GetString()};
        std::string              metaId{reference};
        static std::string const tLSErrorReportMetaId{"42399f48-4281-4069-8648-6045d7e6cd3d"};
        GetMetaId(metaId);

        if (tLSErrorReportMetaId != metaId)
        {
            LOG_DEBUG << "Unsupported type metaId for 'TLSErrorReportSensorData' - " << metaId << LOG_NOOP;
            continue;
        }

        rapidjson::Value const& valueJson = valueIt->value;
        for (rapidjson::Value::ConstValueIterator valueItr = valueJson.Begin(); valueItr != valueJson.End(); ++valueItr)
        {
            auto const& idIt = valueItr->FindMember("id");
            auto const& fieldValueIt = valueItr->FindMember("value");

            if ((idIt == valueItr->MemberEnd()) || (fieldValueIt == valueItr->MemberEnd()) || !idIt->value.IsUint())
            {
                LOG_WARNING << "Missing 'id' or 'value' members for TLSErrorReportSensorData" << LOG_NOOP;
                continue;
            }

            auto const id = idIt->value.GetUint();
            auto const& val = fieldValueIt->value;

            switch (static_cast<valueId>(id))
            {
            case valueId::COMPONENTID_ID:
                if (val.IsString())
                {
                    m_componentId = cm::optional<std::string>(truncateStringSize(val.GetString(), reference, cm::optional<uint32_t>(id)));
                    retVal        = true;
                }
                else
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::COMPONENTID_ID)
                                << " in TLSErrorReportSensorData, is not a string" << LOG_NOOP;
                }
                break;

            case valueId::TIME_STAMP_ID:
                if (val.IsUint64())
                {
                    auto const timestamp{val.GetUint64()};
                    m_timeStamp = cm::optional<uint64_t>(timestamp);
                    retVal      = true;
                    setAlertDataTimestamp(timestamp);
                }
                else
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::TIME_STAMP_ID)
                                << " in TLSErrorReportSensorData, is not uint64" << LOG_NOOP;
                }
                break;

            case valueId::CLIENT_IP_ID:
                if (val.IsString())
                {
                    m_clientIp = cm::optional<std::string>(truncateStringSize(val.GetString(), reference, cm::optional<uint32_t>(id)));
                    retVal     = true;
                }
                else
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::CLIENT_IP_ID)
                                << " in TLSErrorReportSensorData, is not a string" << LOG_NOOP;
                }
                break;

            case valueId::SERVER_IP_ID:
                if (val.IsString())
                {
                    m_serverIp = cm::optional<std::string>(truncateStringSize(val.GetString(), reference, cm::optional<uint32_t>(id)));
                    retVal     = true;
                }
                else
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::SERVER_IP_ID)
                                << " in TLSErrorReportSensorData, is not a string" << LOG_NOOP;
                }
                break;

            case valueId::CLIENT_PORT_ID:
                if (!val.IsUint())
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::CLIENT_PORT_ID)
                                << " in TLSErrorReportSensorData, is not uint" << LOG_NOOP;
                    break;
                }
                m_clientPort = cm::optional<uint16_t>(static_cast<uint16_t>(val.GetUint()));
                retVal       = true;
                break;

            case valueId::SERVER_PORT_ID:
                if (!val.IsUint())
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::SERVER_PORT_ID)
                                << " in TLSErrorReportSensorData, is not uint" << LOG_NOOP;
                    break;
                }
                m_serverPort = cm::optional<uint16_t>(static_cast<uint16_t>(val.GetUint()));
                retVal       = true;
                break;

            case valueId::PROTOCOL_ID:
                if (!val.IsUint())
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::PROTOCOL_ID)
                                << " in TLSErrorReportSensorData, is not uint" << LOG_NOOP;
                    break;
                }
                m_protocol = cm::optional<uint16_t>(static_cast<uint16_t>(val.GetUint()));
                if (m_protocol.has_value() && (static_cast<uint16_t>(protocolId::UDP_ID) != *m_protocol)
                    && (static_cast<uint16_t>(protocolId::TCP_ID) != *m_protocol))
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::PROTOCOL_ID)
                                << " in TLSErrorReportSensorData, doesn't match any valid value (tcp, udp). Dropping sd"
                                << LOG_NOOP;
                    return false;
                }
                retVal = true;
                break;

            case valueId::FAILURE_REASON_ID:
                if (!val.IsInt())
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::FAILURE_REASON_ID)
                                << " in TLSErrorReportSensorData, is not int" << LOG_NOOP;
                    break;
                }
                m_failureReason = cm::optional<int32_t>(val.GetInt());
                retVal          = true;
                break;

            case valueId::TLS_IDENTITY_ID:
                if (val.IsString())
                {
                    m_tlsIdentity = cm::optional<std::string>(truncateStringSize(val.GetString(), reference, cm::optional<uint32_t>(id)));
                    retVal        = true;
                }
                else
                {
                    LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::TLS_IDENTITY_ID)
                                << " in TLSErrorReportSensorData, is not a string" << LOG_NOOP;
                }
                break;

            default:
                LOG_WARNING << "The 'id' (" << (*valueItr)["id"].GetUint()
                            << ") in TLSErrorReportSensorData, exceeds its range" << LOG_NOOP;
                break;
            }
        }
    }
    return retVal;
}
