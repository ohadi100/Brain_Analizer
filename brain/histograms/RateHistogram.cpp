#include "RateHistogram.hpp"
#include "common/utils/logger/Logger.hpp"


using brain::histogram::RateHistogram;

RateHistogram::RateHistogram(BinIntervalsVector const& bins, BurstType maxBurst) :
    m_histogram(std::move(bins), maxBurst)
    ,m_isHistogramEmpty(true)
{
    if (false == m_histogram.Init())
    {
        LOG_ERROR << "Failed to initialize the rate histogram" << LOG_NOOP;
    }
}

bool RateHistogram::AddData(uint64_t time, uint64_t weight)
{
    IntervalType interval{};
    return AddData(time, weight, interval);
}

bool RateHistogram::AddData(uint64_t time, uint64_t weight, double& interval)
{
    if (!m_histogram.AddEvent(time, weight, interval))
    {
        return false;
    }

    if (m_isHistogramEmpty)
    {
        m_isHistogramEmpty = false;
        m_startPeriodTime = time;
    }
    m_endPeriodTime = time;

    return true;
}

bool RateHistogram::GetHistogramValues(BinDataVector& histogramData, uint64_t& firstTimestamp, uint64_t& lastTimestamp) const
{
    if (m_isHistogramEmpty)
    {
        return false;
    }

    histogramData.clear();
    firstTimestamp = m_startPeriodTime;
    lastTimestamp = m_endPeriodTime;
    
    return m_histogram.GetHistValues(histogramData);
}

bool RateHistogram::GetHistogramCumulativeValues(BinDataVector& histogramData, uint64_t& firstTimestamp, uint64_t& lastTimestamp) const
{
    if (m_isHistogramEmpty)
    {
        return false;
    }

    histogramData.clear();
    firstTimestamp = m_startPeriodTime;
    lastTimestamp = m_endPeriodTime;
    return m_histogram.GetHistCumulativeValues(histogramData);
}

void RateHistogram::ClearHistogramContents()
{
    std::ignore        = m_histogram.Clear();
    m_startPeriodTime  = 0U;
    m_endPeriodTime    = 0U;
    m_isHistogramEmpty = true;
}