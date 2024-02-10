/**
 * @file
 * @brief       This file describes  and implements the engine functionality
 */
#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "common/sensor_data/SensorData.hpp"
#include "common/utils/os/time/TimeWrapper.hpp"

namespace brain
{
namespace engines
{

enum class ReturnCode : uint8_t
{
    Success,
    TagError,
    CastError,
    InvalidError,
    LengthError,
    FailedError,
    MaxTableSizeError
};

using common::sensor_data::UPSensorData;

/**
 * @class   Engine
 * @brief   Base class for all engines
 */
class Engine
{
public:
    /**
     * @brief   Constructor
     */
    Engine() = default;

    /**
     * @brief   Destructor
     */
    virtual ~Engine() = default;

    /**
     * @brief    default copy constructor
     */
    Engine(const Engine& other) = delete;

    /**
     * @brief    default move constructor
     */
    Engine(Engine&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    Engine& operator=(Engine const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    Engine& operator=(Engine&&) = delete;

    /**
     * @fn      bool Process(UPSensorData sd)
     * @brief   Sets the current time and calls the internal processor on the input sensor data.
     *          The internal processor must be provided by each derived class.
     * @param   UPSensorData& sd - the notification dequeued from the WRR
     * @return  Success if the event can be send, otherwise an error code from returnCode enum
     */
    ReturnCode
    Process(UPSensorData sd)
    {
        m_currentTime = common::Time::GetCurrentTimeMilliSec();
        return processInternal(std::move(sd));
    }

protected:
    virtual ReturnCode processInternal(UPSensorData sd) = 0;
    uint64_t m_currentTime{};
};
}  // namespace engines
}  // namespace brain

#endif  // ENGINE_HPP
