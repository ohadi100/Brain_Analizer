#include "ProcessPerformanceSensorData.hpp"
#include "common/utils/logger/Logger.hpp"

using namespace brain::sensor_data;

namespace brain
{
namespace sensor_data
{
static bool
EndsWith(const std::string& fullString, const std::string& ending)
{
    if (fullString.length() < ending.length())
    {
        return false;
    }

    return (fullString.rfind(ending) == (fullString.length() - ending.length()));
}

}  // namespace sensor_data
}  // namespace brain

ProcessPerformanceSensorData::ProcessPerformanceSensorData(bool&                                   success,
                                                           rapidjson::Value const&                 parsedJson,
                                                           brain::sensor_data::swpac::ConstraintId constraintId)
  : SensorData()
  , SwpacSensorDataBase(constraintId)
{
    success = FillFromJson(parsedJson);
}

bool
ProcessPerformanceSensorData::FillFromJson(rapidjson::Value const& dataItems)
{
    if (!dataItems.IsArray())
    {
        LOG_DEBUG << "Error value is not an array" << LOG_NOOP;
        return false;
    }

    uint8_t parsedValuesCnt{};

    for (rapidjson::Value::ConstValueIterator valueItr = dataItems.Begin(); valueItr != dataItems.End(); ++valueItr)
    {
        auto const& referenceIt      = valueItr->FindMember("reference");
        auto const& referenceValueIt = valueItr->FindMember("value");

        if ((valueItr->MemberEnd() == referenceIt) || (valueItr->MemberEnd() == referenceValueIt)
            || !referenceIt->value.IsString())
        {
            LOG_WARNING << "Missing 'reference' or 'value' members for KernelLogSensorData" << LOG_NOOP;
            continue;
        }

        auto const& referenceId = referenceIt->value.GetString();
        auto const& val         = referenceValueIt->value;
        static constexpr char cpuKeyValue[]{"a7178255-99ff-4718-aa93-d933bd30023e"};
        static constexpr char ramKeyValue[]{"12f43252-5a9a-4836-a5fa-ed89a454e8ab"};

        if (val.IsString() && EndsWith(referenceId, "name"))
        {
            constexpr std::size_t maxProcessNameLength{24U};

            auto processName = truncateStringSize(val.GetString(), referenceId);
            if (processName.size() > maxProcessNameLength)
            {
                processName.resize(maxProcessNameLength);
            }
            m_processName    = processName;
            ++parsedValuesCnt;
        }
        else if (val.IsInt() && EndsWith(referenceId, "PID"))
        {
            m_pid = val.GetInt();
            ++parsedValuesCnt;
        }
        else if (val.IsUint() && EndsWith(referenceId, cpuKeyValue))
        {
            m_cpu = val.GetUint();
            ++parsedValuesCnt;
        }
        else if (val.IsUint() && EndsWith(referenceId, ramKeyValue))
        {
            m_ram = val.GetUint();
            ++parsedValuesCnt;
        }
    }

    return (parsedValuesCnt == 4U);
}
