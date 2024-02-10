/**
 * @file
 * @brief     This file contains the functionality of the DiagMeasurementValuesManager class
*/
#include "DiagMeasurementValuesManager.hpp"


using brain::diagnostics::measurement_values::DiagMeasurementValuesManager;


DiagMeasurementValuesManager::DiagMeasurementValuesManager(CounterManagerPtr countersManager) : 
    m_countersManager(countersManager)
{}

void DiagMeasurementValuesManager::SetUpCounterPublishers(PersistentMapPtr persistentMemory)
{
    // Diag - 0x32c
    m_diagIntrusionDetectionSystemWarningCounterPublisher = 
        std::make_shared<IntrusionDetectionSystemWarningCounterPublisher>(m_countersManager, persistentMemory);

    // Diag - 0x32d
    m_diagIntrusionDetectionSystemErrorCounterPublisher = 
        std::make_shared<IntrusionDetectionSystemErrorCounterPublisher>(m_countersManager, persistentMemory);
}

bool DiagMeasurementValuesManager::ResetMeasurementValues()
{
    bool result = true;

    // Diag - 0x32c
    if (nullptr != m_diagIntrusionDetectionSystemWarningCounterPublisher)
    {
        result = m_diagIntrusionDetectionSystemWarningCounterPublisher->ResetCounters();
    }

    // Diag - 0x32d
    if (nullptr != m_diagIntrusionDetectionSystemErrorCounterPublisher)
    {
        result = result && m_diagIntrusionDetectionSystemErrorCounterPublisher->ResetCounters();
    }

    return result;
}