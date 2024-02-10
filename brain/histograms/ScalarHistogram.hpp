/**
 * @file
 * @brief     This file contains the definition of the ScalarHistogram class and its functionality.
 */
#ifndef SCALAR_HISTOGRAM_HPP
#define SCALAR_HISTOGRAM_HPP

#include "histogram/ScalarHistogram.hpp"


namespace brain
{
namespace histogram
{
/**
* @class: ScalarHistogram
* @brief: Class that represents implementation of scalar histogram.
*/
class ScalarHistogram final
{
public:

    using ScalarHistogramImpl = histogram_lib::ScalarHistogram<double, uint64_t>;
    using BinData = typename ScalarHistogramImpl::BinDataType;
    using BinIntervalsVector = typename ScalarHistogramImpl::BinIntervalsVector;
    using BinDataVector = typename ScalarHistogramImpl::BinDataVectorType;
    using IntervalType = typename ScalarHistogramImpl::BinIntervalType;

    /**
     * @brief   Init histogram data structures. Must be called before histogram usage.
     * @param   BinIntervalsVector bins
     * @return  true iff operation succeed.
     */
    ScalarHistogram(BinIntervalsVector bins);

    /**
     * @brief   Add new data piece to the histogram.
     * @param   uint64_t time - the time of the data
     * @param   double const data - the data
     *          e.g. if data value is between bins, it goes in to smaller one.
                     if bins = {3, 5}, the data = 4. m_binsContents will be updated to: {1, 0}.
     * @param   uint32_t weight - the weight of the data
     * @param   double& interval - The interval value of the matching bin.
     * @return  bool - true iff operation succeed, otherwise false.
     */
    virtual bool Update(uint64_t time, double data, uint64_t weight, double& interval);

    /**
     * @brief       Get histogram's bin data. Matches BinData counter to it's upper boundary interval.
     * @param[out]  histogramData
     * @param[out]  uint64_t firstTimestamp - histogram's first seen timestamp (S)
     * @param[out]  uint64_t lastTimestamp - histogram's last seen timestamp (S)
     * @return      true iff operation succeeds and histogram isn't empty, false otherwise.
     */
    virtual bool GetHistogramValues(BinDataVector& histogramData, uint64_t& firstTimestamp, uint64_t& lastTimestamp) const;

private:

    ScalarHistogramImpl m_histogram;
    uint64_t m_startPeriodTime{};
    uint64_t m_endPeriodTime{};
    bool m_isHistogramEmpty;
};

} //namespace histogram
} //namespace brain

#endif // SCALAR_HISTOGRAM_HPP
