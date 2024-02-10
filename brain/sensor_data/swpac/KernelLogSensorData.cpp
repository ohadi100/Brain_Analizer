#include "KernelLogSensorData.hpp"
#include "common/utils/logger/Logger.hpp"

using namespace brain::sensor_data;


KernelLogSensorData::KernelLogSensorData(bool& success, rapidjson::Value const& parsedJson, ConstraintId constraintId)
  : SensorData()
  , SwpacSensorDataBase(constraintId)
{
    success = FillFromJson(parsedJson);
}

bool
KernelLogSensorData::FillFromJson(rapidjson::Value const& dataItems)
{
    bool retVal = false;
    for (rapidjson::Value::ConstValueIterator valueItr = dataItems.Begin(); valueItr != dataItems.End(); ++valueItr)
    {
        auto const& metaIdIt = valueItr->FindMember("reference");
        auto const& valueIt  = valueItr->FindMember("value");

        if ((metaIdIt == valueItr->MemberEnd()) || (valueIt == valueItr->MemberEnd()) || !metaIdIt->value.IsString()
            || !valueIt->value.IsArray())
        {
            LOG_WARNING << "Missing 'reference' or 'value' members for KernelLog" << LOG_NOOP;
            continue;
        }

        auto const& reference{metaIdIt->value.GetString()};
        std::string metaId{reference};
        GetMetaId(metaId);
        static std::string const logMessageMetaId{"57c9b247-cae6-48e4-9a4e-cf56846ad1e9"};

        if (logMessageMetaId == metaId)
        {
            retVal = fillLogMessageFromJson(valueIt->value, reference);
            break;
        }
    }

    return retVal;
}

  bool
  KernelLogSensorData::fillLogMessageFromJson(rapidjson::Value const& incidentJson, std::string const& reference)
  {
      if (!incidentJson.IsArray())
      {
          LOG_DEBUG << "Error value is not an array" << LOG_NOOP;
          return false;
      }

      bool retVal = false;

      for (rapidjson::Value::ConstValueIterator valueItr = incidentJson.Begin(); valueItr != incidentJson.End();
           ++valueItr)
      {
          auto const& idIt         = valueItr->FindMember("id");
          auto const& fieldValueIt = valueItr->FindMember("value");

          if ((idIt == valueItr->MemberEnd()) || (fieldValueIt == valueItr->MemberEnd()) || !idIt->value.IsUint())
          {
              LOG_WARNING << "Missing 'id' or 'value' members for KernelLogSensorData" << LOG_NOOP;
              continue;
          }

          auto const  id  = idIt->value.GetUint();
          auto const& val = fieldValueIt->value;

          switch (static_cast<valueId>(id))
          {
          case valueId::TIMESTAMP_ID:
              if (val.IsUint64())
              {
                  auto const timestamp{val.GetUint64()};
                  m_logMessageTimestamp = cm::optional<uint64_t>(timestamp);
                  retVal                = true;
                  setAlertDataTimestamp(timestamp);
              }
              else
              {
                  LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::TIMESTAMP_ID)
                              << " in KernelLogSensorData, is not uint64" << LOG_NOOP;
              }
              break;

          case valueId::MESSAGE_ID:
              if (val.IsString())
              {
                  m_logMessageMessage = cm::optional<std::string>(
                      truncateStringSize(val.GetString(), reference, cm::optional<uint32_t>(id)));
                  retVal = true;
              }
              else
              {
                  LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::MESSAGE_ID)
                              << " in KernelLogSensorData, is not a string" << LOG_NOOP;
              }
              break;

          case valueId::LOG_LEVEL_ID:
              if (!val.IsUint())
              {
                  LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::LOG_LEVEL_ID)
                              << " in KernelLogSensorData, is not a uint" << LOG_NOOP;
                  break;
              }
              m_logMessageLoglevel = cm::optional<uint32_t>(val.GetUint());
              retVal               = true;
              break;

          case valueId::FACILITY_ID:
              if (!val.IsUint())
              {
                  LOG_WARNING << "The 'value' for " << static_cast<uint8_t>(valueId::FACILITY_ID)
                              << " in KernelLogSensorData, is not a uint" << LOG_NOOP;
                  break;
              }
              m_logMessageFacility = cm::optional<uint32_t>(val.GetUint());
              retVal               = true;
              break;

          default:
              LOG_WARNING << "The 'id' (" << id << ") in KernelLogSensorData, exceeds its range" << LOG_NOOP;
              break;
          }
      }

      return retVal;
  }
