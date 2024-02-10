/**
 * @file
 * @brief     This file contains the definition of the RateHsitogram class and its functionality.
 */
#ifndef RATE_HISTOGRAM_HPP
#define RATE_HISTOGRAM_HPP

#include "common/utils/os/time/Time.hpp"
#include "histogram/TokenBucketRateHistogram.hpp"

#include <stdint.h>



namespace brain
{
namespace histogram
{

constexpr uint64_t MAX_BURST{1U};

/**
* @class: RateHistogram
* @brief: Class that implements rate histogram using 'token bucket' algorithm
*/
class RateHistogram final
{
public:

    using RateHistogramImpl = histogram_lib::TokenBucketRateHistogram<double, uint64_t>;
    using TimeType = typename RateHistogramImpl::TimeType;
    using BinData = typename RateHistogramImpl::BinDataType;
    using BurstType =  typename RateHistogramImpl::BurstType;
    using BinIntervalsVector = typename RateHistogramImpl::BinIntervalsVectorType;
    using BinDataVector = typename RateHistogramImpl::BinDataVectorType;
    using IntervalType = typename RateHistogramImpl::BinIntervalType;

    /**
     * @brief   Constructor
     * @param   BinIntervalsVector const& bins - X axis of the histogram - every bin represents interval rate.
     *          e.g. - { 0.01, 0.1, 1, 10 } - first bin is rate of 0 to 0.01 incident per second.
     *                                        second bin is rate of 0.01 to 0.1 incident per second. etc.
     *          The first bin of the histogram contains all values from 0 to bins.front(),
     *          and the last bin of the histogram will contain all values that are greater
     *          than bins.back().
     * @param   uint64_t const& maxBurst - the maximum burst
     */
    RateHistogram(BinIntervalsVector const& bins, BurstType maxBurst);

    /**
     * @brief   Add new data piece to the histogram.
     * @param   uint64_t const& time - the time of the data
     * @param   uint64_t const& weight - the weight of the data
     * @return  bool - true iff operation succeed, otherwise false.
     */
    virtual bool AddData(uint64_t time, uint64_t weight);

    /**
     * @brief   Add new data piece to the histogram.
     * @param   uint64_t const& time - the time of the data
     * @param   uint64_t const& weight - the weight of the data
     * @param   double& interval - The interval value of the matching bin.
     * @return  bool - true iff operation succeed, otherwise false.
     */
    virtual bool AddData(uint64_t time, uint64_t weight, double& interval);

    /**
     * @brief   Get histogram's bin data. Matches BinData counter to it's upper boundary interval.
     * @param   uint64_t& firstTimestamp - the first timestamp of the histogram.
     * @param   uint64_t& lastTimestamp - the last timestamp of the histogram.
     * @return  bool - true iff operation succeeds and histogram is loaded, otherwise false.
     */
    virtual bool GetHistogramValues(BinDataVector& histogramData, uint64_t& firstTimestamp, uint64_t& lastTimestamp) const;

    /**
     * @brief   Get histogram's cumulative bin data. Matches BinData counter to it's upper boundary interval.
     * @param   BinDataVector& histogramData - the histogram's cumulative bin data.
     * @param   uint64_t& firstTimestamp - the first timestamp of the histogram.
     * @param   uint64_t& lastTimestamp - the last timestamp of the histogram.
     * @return  bool - true iff operation succeeds and histogram is loaded, otherwise false.
     */
    virtual bool GetHistogramCumulativeValues(BinDataVector& histogramData, uint64_t& firstTimestamp, uint64_t& lastTimestamp) const;

    /**
     * @brief   Clears the histogram contents.
     */
    void ClearHistogramContents();

    /**
     * @brief   Is histogram empty.
     * @return  true if empty, otherwise false
     */
    inline bool Empty() const
    {
        return m_isHistogramEmpty;
    }

private:
    RateHistogramImpl m_histogram;
    uint64_t m_startPeriodTime{};
    uint64_t m_endPeriodTime{};
    bool m_isHistogramEmpty;
};

} // namespace histogram
} // namespace brain

#endif // RATE_HISTOGRAM_HPP
