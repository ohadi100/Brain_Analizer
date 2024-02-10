#pragma once
/**
 * @file
 * @brief A counter with timestamps for first and last seen
 */
#include <memory>
#include <string>
#include <limits>

namespace brain
{
namespace utils
{
/**
 * @class   CounterWithTs
 * @brief   The CounterWithTs provides counter with timestamps for first and last seen.
 */
class CounterWithTs
{
public:
    /**
     * @brief   Constructor
     * @param   const std::string & name - name of counter
     */
    CounterWithTs(std::string const & name = std::string());

    /**
     * @brief   Update timestamps and increment counter
     * @param   uint64_t const timestamp - input timestamp
     * @param   uint64_t const addToCounter - value to add to counter
     */
    inline void Increment(uint64_t const timeStamp, uint64_t const addToCounter = 1U)
    {
        m_lastSeenTimeStamp = timeStamp;
       
        if (0 == m_firstSeenTimeStamp)
        {
            m_firstSeenTimeStamp = timeStamp;
        }

        if (m_counter > (std::numeric_limits<uint64_t>::max() - addToCounter))
        {
            m_counter = std::numeric_limits<uint64_t>::max();
            if (!m_name.empty())
            {
                logIncrementWarning(m_name);
            }
        }
        else
        {
            m_counter += addToCounter;
        }
    }

    /**
     * @brief   Get the first seen timestamp.
     * @return  uint64_t const& - the timestamp's value.
     */
    inline uint64_t const& GetFirstSeenTimeStamp() const noexcept
    {
        return m_firstSeenTimeStamp;
    }

    /**
     * @brief   Get the last seen timestamp.
     * @return  uint64_t const& - the timestamp's value.
     */
    inline uint64_t const& GetLastSeenTimeStamp() const noexcept
    {
        return m_lastSeenTimeStamp;
    }

    /**
     * @brief   Get the counter's value.
     * @return  uint64_t const& - the counter's value.
     */
    inline uint64_t const& GetCounter() const noexcept
    {
        return m_counter;
    }

    /**
     * @brief   Clears the counter and timestamps contents.
     */
    inline void ClearContents() noexcept
    {
        m_counter = 0U;
        m_lastSeenTimeStamp = 0U;
        m_firstSeenTimeStamp = 0U;
    }

private:
    void logIncrementWarning(const std::string& name);

    std::string m_name;
    uint64_t m_counter;
    uint64_t m_lastSeenTimeStamp;
    uint64_t m_firstSeenTimeStamp;
};

} // namespace utils
} // namespace brain
