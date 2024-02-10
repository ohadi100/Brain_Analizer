/**
 * @file
 * @brief     This file contains the functionality of the GSDPCommunicator class
 */
#include "GSDPCommunicator.hpp"
#include "brain/engines/security_events/SecurityEventsEngine.hpp"
#include "brain/sensor_data/swpac/IncidentHelper.hpp"
#include "brain/sensor_data/swpac/SwpacSensorDataBase.hpp"

using namespace brain::brain_communicator::someip::gsdp;
using brain::engines::security_events::SecurityEventsEngine;
using brain::sensor_data::swpac::ConstraintId;

GSDPCommunicator::UPSensorData
GSDPCommunicator::FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData)
{
    static const std::unordered_map<ConstraintId, DropReason> DhmNoiseFilterMap{
        {ConstraintId::KERNEL_LOG_KERNEL_PANIC, DropReason::DhmKernelLogNoiseFilter},
        {ConstraintId::TLS_ERROR_REPORT, DropReason::DhmTlsErrorNoiseFilter},
        {ConstraintId::PROCESS_PERFORMANCE, DropReason::DhmProcessPerformanceNoiseFilter}};

    auto filteredSd = Communicator::FilterIncomeSD(std::move(sd), eventSize, hasData);
    std::unique_ptr<common::sensor_data::SensorData> droppedSd = GetDroppedSensorData();
    if (droppedSd)
    {
        try
        {
            std::unique_ptr<brain::sensor_data::SwpacSensorDataBase> dhmSd(
                dynamic_cast<brain::sensor_data::SwpacSensorDataBase*>(droppedSd.release()));

            if (dhmSd)
            {
                auto const  constraintId = dhmSd->GetConstraintId();
                auto const& it           = DhmNoiseFilterMap.find(constraintId);
                if (DhmNoiseFilterMap.cend() != it)
                {
                    SecurityEventsEngine::HandleDhmDroppedSecurityEventExt(constraintId, it->second);
                }
                else
                {
                    LOG_WARNING << "could not find drop reson for constraint id " << static_cast<uint8_t>(constraintId)
                                << LOG_NOOP;
                }
            }
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (std::exception const& /*e*/)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "failed to convert the sd to SwpacSensorDataBase." << LOG_NOOP;
        }  // only for parasoft violations
    }

    return filteredSd;
}

#if (!defined(SSP_PLATFORM) && !defined(SSP_PLATFORM_TEST) && !defined(SSP_SIMULATION))
void
GSDPCommunicator::handleQueueAddFailed(UPSensorData sd, DropReason dropReason)
{
    if (sd)
    {
        try
        {
            std::unique_ptr<brain::sensor_data::SwpacSensorDataBase> dhmSd(
                dynamic_cast<brain::sensor_data::SwpacSensorDataBase*>(sd.release()));
            auto const constraintId = dhmSd->GetConstraintId();
            SecurityEventsEngine::HandleDhmDroppedSecurityEventExt(constraintId, dropReason);
        }
        // parasoft-begin-suppress AUTOSAR-A15_3_4-a "To prevent exception leak from IDS"
        catch (std::exception const& /*e*/)
        // parasoft-end-suppress AUTOSAR-A15_3_4-a
        {
            LOG_ERROR << "failed to convert the sd to SwpacSensorDataBase." << LOG_NOOP;
        }  // only for parasoft violations
    }
}
#endif

void
GSDPCommunicator::registerFactory(HealthIncidentProviderProxy& obj)
{
    LOG_INFO << "Registering to HealthIncidentProvider incidents" << LOG_NOOP;
    registerSomeIP(obj.incident, std::bind(&GSDPCommunicator::generateIncidentSD, this, std::placeholders::_1));

    auto uuid = std::array<unsigned char, 16>();
    uuid.fill(0);
    auto fut = obj.getLastIncidents(uuid);
    if (fut.wait_for(std::chrono::seconds(3)) == ara::core::future_status::timeout)
    {
        LOG_ERROR << "Timeout while getting results of getLastIncidents" << LOG_NOOP;
    }
    else
    {
        const auto result = fut.GetResult();
        if (!result)
        {
            LOG_ERROR << "Received error from getLastIncidents: " << result.Error().Message().data() << LOG_NOOP;
        }
        else
        {
            auto lastIncidents = result.Value();
            LOG_INFO << "Last Incidents = " << lastIncidents.incidents.data() << LOG_NOOP;
        }
    }
}

void
GSDPCommunicator::deregisterFactory(HealthIncidentProviderProxy& obj)
{
    LOG_INFO << "Deregistering from HealthIncidentProvider incidents" << LOG_NOOP;
    deregisterSomeIP(obj.incident);
}

GSDPCommunicator::UPSensorDataVectorPtr
GSDPCommunicator::generateIncidentSD(const IncidentSampleDatatype& field)
{
    LOG_DEBUG << "Got new incident: " << field << LOG_NOOP;

    ConstraintId constraintId{ConstraintId::UNDEFINED_CONSTRAINTID};
    auto         sd = brain::sensor_data::SWPACSensorDataFactory::CreateSD(constraintId, field.c_str(), m_diagManager);

    if ((!sd || sd->empty()) && (ConstraintId::UNDEFINED_CONSTRAINTID != constraintId))
    {
        SecurityEventsEngine::HandleDhmDroppedSecurityEventExt(constraintId, DropReason::GSDPCommunicator);
    }

    return sd;
}
