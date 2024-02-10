#pragma once
/**
 * @file
 * @brief     Interface class of publisher.
 */
#include <functional>
#include <memory>
#include <vector>

class PublisherInterface
{
public:
    enum class EventType : uint8_t
    {
        CONNECTED,
        ACK_OK,
        ACK_OK_WITH_TIMEOUT,
        RETRY,
        RETRY_WITH_TIMEOUT
    };

    virtual ~PublisherInterface() = default;

    /**
     * @brief    default copy constructor
     */
    PublisherInterface(const PublisherInterface& other) = delete;

    /**
     * @brief    default move constructor
     */
    PublisherInterface(PublisherInterface&& other) = delete;

    /**
     * @brief    default copy assignment operator
     */
    PublisherInterface& operator=(PublisherInterface const&) = delete;

    /**
     * @brief   default move assignment operator
     */
    PublisherInterface& operator=(PublisherInterface&&) = delete;

    /**
     * @brief Initialize the publisher.
     * @param std::function callback function for sending notifications from the backend
     *
     * @return true on success, else false.
     */
    virtual bool Connect(std::function<void(EventType)> = nullptr) = 0;

    /**
     * @brief Close connection with publisher and stop initiating new connection.
     *
     * @return true on success, else false.
     */
    virtual bool Disconnect() = 0;

    /**
     * @brief send message by the publisher.
     *
     * @param msgPayload payload uint8_t vector to be send
     *
     * @return Amount bytes that were sent, in case of failure 0 value will be returned
     */
    virtual bool SendMessage(std::shared_ptr<std::vector<uint8_t>> msgPayload) = 0;

protected:
    /**
     * @brief   Ctor
     */
    PublisherInterface() = default;
};
