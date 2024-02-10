/**
 * @file
 * @brief     This file contains the functionality of the SecurityEventSmall class
 */
#include "SecurityEventSmall.hpp"
#include "brain/sensor_data/security_events/SecurityEventSensorData.hpp"
#include "brain/engines/security_events/SecurityEventsEngine.hpp"

using brain::engines::security_events::SecurityEventsEngine;

using namespace brain::brain_communicator::someip::idssecurityeventsmall;
using SecurityEventSensorData = brain::sensor_data::SecurityEventSensorData;
using brain::engines::security_events::DropReason;

IDSSecurityEventSmallCommunicator::UPSensorData
IDSSecurityEventSmallCommunicator::FilterIncomeSD(UPSensorData sd, size_t const eventSize, bool& hasData)
{
    auto filteredSd = Communicator::FilterIncomeSD(std::move(sd), eventSize, hasData);
    auto droppedSd  = GetDroppedSensorData();
    if (droppedSd)
    {
        bool const isIntelligentEvent
            = common::sensor_data::SensorDataTag::SD_INTELLIGENT_SENSOR == droppedSd->GetTag();
        SecurityEventsEngine::HandleDroppedSecurityEventExt(
            std::move(droppedSd),
            isIntelligentEvent ? DropReason::IntelligentSensorNoiseFilter : DropReason::SecurityEventSmallNoiseFilter);
    }
    return filteredSd;
}

void
IDSSecurityEventSmallCommunicator::registerFactory(IDSSecurityEventSmallProxy& obj)
{
    LOG_INFO << "Registering to IDSSecurityEventSmall incidents" << LOG_NOOP;
    registerSomeIP(obj.securityEvent, registerSecurityEventSmallSD);
}

void
IDSSecurityEventSmallCommunicator::deregisterFactory(IDSSecurityEventSmallProxy& obj)
{
    LOG_INFO << "Deregistering to IDSSecurityEventSmall incidents" << LOG_NOOP;
    deregisterSomeIP(obj.securityEvent);
}

IDSSecurityEventSmallCommunicator::UPSensorDataVectorPtr
IDSSecurityEventSmallCommunicator::registerSecurityEventSmallSD(const SecurityEventSmallDataType& field)
{
    // Generate SD out of incoming SecurityEvent
    bool sdCreatedSuccessfully{};
    auto sd = std::make_unique<SecurityEventSensorData>(field, sdCreatedSuccessfully);

    if (sdCreatedSuccessfully)
    {
        LOG_DEBUG << "securityEventSmall SD created " << sd->GetEventId() << LOG_NOOP;
        // Process event
        UPSensorDataVectorPtr sdVector = std::make_shared<UPSensorDataVector>();
        sdVector->push_back(std::move(sd));
        return sdVector;
    }
    else if (sd)
    {
        bool const isIntelligentEvent = common::sensor_data::SensorDataTag::SD_INTELLIGENT_SENSOR == sd->GetTag();
        SecurityEventsEngine::HandleDroppedSecurityEventExt(
            std::move(sd),
            isIntelligentEvent ? DropReason::IntelligentSecurityEventCommunicator : DropReason::SecurityEventSmallCommunicator);
    }

    return nullptr;
}
