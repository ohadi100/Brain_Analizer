/**
 * @file
 * @brief     This file contains the functionality of the SecurityEventNormal class
 */
#include "SecurityEventNormal.hpp"
#include "sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/engines/security_events/SecurityEventsEngine.hpp"

using brain::engines::security_events::SecurityEventsEngine;

using namespace brain::brain_communicator::someip::idssecurityeventnormal;
using SecurityEventSensorData = brain::sensor_data::SecurityEventSensorData;
using brain::engines::security_events::DropReason;

IDSSecurityEventNormalCommunicator::UPSensorData
IDSSecurityEventNormalCommunicator::FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData)
{
    auto filteredSd = Communicator::FilterIncomeSD(std::move(sd), eventSize, hasData);
    auto droppedSd  = GetDroppedSensorData();
    if (droppedSd)
    {
        bool const isIntelligentEvent
            = common::sensor_data::SensorDataTag::SD_INTELLIGENT_SENSOR == droppedSd->GetTag();
        SecurityEventsEngine::HandleDroppedSecurityEventExt(
            std::move(droppedSd),
            isIntelligentEvent ? DropReason::IntelligentSensorNoiseFilter : DropReason::SecurityEventNormalNoiseFilter);
    }
    return filteredSd;
}

void
IDSSecurityEventNormalCommunicator::registerFactory(IDSSecurityEventNormalProxy& obj)
{
    LOG_INFO << "Registering to IDSSecurityEventNormal incidents" << LOG_NOOP;
    registerSomeIP(obj.securityEventEvent, generateSecurityEventNormalSD);
}

void
IDSSecurityEventNormalCommunicator::deregisterFactory(IDSSecurityEventNormalProxy& obj)
{
    LOG_INFO << "Deregistering to IDSSecurityEventNormal incidents" << LOG_NOOP;
    deregisterSomeIP(obj.securityEventEvent);
}

IDSSecurityEventNormalCommunicator::UPSensorDataVectorPtr
IDSSecurityEventNormalCommunicator::generateSecurityEventNormalSD(const SecurityEventNormalDataType& field)
{
    // Generate SD out of incoming SecurityEvent
    bool sdCreatedSuccessfully{};
    auto sd = std::make_unique<SecurityEventSensorData>(field, sdCreatedSuccessfully);

    if (sdCreatedSuccessfully)
    {
        LOG_DEBUG << "securityEventNormal SD created " << sd->GetEventId() << LOG_NOOP;
        // Process event
        UPSensorDataVectorPtr sdVector = std::make_shared<UPSensorDataVector>();
        sdVector->push_back(std::move(sd));
        return sdVector;
    }
    else if (sd)
    {
        bool const isIntelligentEvent = common::sensor_data::SensorDataTag::SD_INTELLIGENT_SENSOR == sd->GetTag();
        SecurityEventsEngine::HandleDroppedSecurityEventExt(std::move(sd),
                                                            isIntelligentEvent
                                                                ? DropReason::IntelligentSecurityEventCommunicator
                                                                : DropReason::SecurityEventNormalCommunicator);
    }

    return nullptr;
}