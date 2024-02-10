#pragma once
/**
 * @file
 * @brief Interface for a MessageRepository object.
 *
 * This interface class defines a message repository, to contain message data between modules. Defines initialization,
 * store, and load functionality.
 */
#include <memory>  // for std::unique_ptr
#include <vector>  // for std::vector

namespace brain
{
namespace messageRepository
{
class MessageRepositoryInterface
{
public:
    using Message    = std::vector<uint8_t>;
    using MessagePtr = std::unique_ptr<Message>;

    struct MessageRepositoryParameters
    {
        size_t weight{};       // Priority weight, high number gives higher priority
        size_t maxElements{};  // Maximum elements to store. When reaching the maximum elements, further elements will
                               // be dropped
    };

    /**
     * @brief Initialize the message repo class with maximun number of priorities.
     *
     * @param[in] MessageRepositoryParams Configure parameters for each priority level.
     * @note      Index 0 of the vector refers to the highest priority and the last index refers to the lowest priority.
     *
     * @return    true on success, else false.
     */
    virtual bool Init(const std::vector<MessageRepositoryParameters>& messageRepositoryParams) = 0;

    /**
     * @brief Pushes given message data into the repository.
     *
     * @note message should not be used after push.
     *
     * @param[in] message  Message to be inserted into the repository
     * @param[in] priority Priority of the message
     * @return    true on success, else false.
     */
    virtual bool Push(MessagePtr&& message, uint8_t priority) = 0;

    /**
     * @brief Pops a contained message and emplaces it into a given location.
     *
     * @note should use std::unique_ptr::swap to make sure emplacement is in O(1).
     *
     * @param[out] message The given location for a loaded message.
     * @return     true on success, else false.
     */
    virtual bool Pop(MessagePtr& message) = 0;

protected:
    MessageRepositoryInterface()          = default;
    virtual ~MessageRepositoryInterface() = default;
    
    /**
     * @brief    default copy constructor
     */
    MessageRepositoryInterface(const MessageRepositoryInterface& other) = delete;

    /**
     * @brief    default move constructor
     */
    MessageRepositoryInterface(MessageRepositoryInterface&& other) = delete;

    /**
    * @brief    default copy assignment operator
    */
    MessageRepositoryInterface& operator=(MessageRepositoryInterface const&) = delete;

    /**
    * @brief   default move assignment operator
    */
    MessageRepositoryInterface& operator=(MessageRepositoryInterface&&) = delete;
};
}  // namespace messageRepository
}  // namespace brain