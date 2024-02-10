#include "ScalarHistogram.hpp"
#include "common/utils/logger/Logger.hpp"

using brain::histogram::ScalarHistogram;

ScalarHistogram::ScalarHistogram(BinIntervalsVector bins)
  : m_histogram(std::move(bins))
  , m_isHistogramEmpty(true)
{
    if (false == m_histogram.Init())
    {
        LOG_ERROR << "Failed to initialize the scalar histogram" << LOG_NOOP;
    }
}

bool ScalarHistogram::Update(uint64_t time, double data, uint64_t weight, double& interval)
{
    if (!m_histogram.Update(data, weight, interval))
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

bool ScalarHistogram::GetHistogramValues(BinDataVector& histogramData, uint64_t& firstTimestamp, uint64_t& lastTimestamp) const
{
    if (m_isHistogramEmpty)
    {
        return false;
    }

    firstTimestamp = m_startPeriodTime;
    lastTimestamp = m_endPeriodTime;
    
    histogramData.clear();
    return m_histogram.GetHistValues(histogramData);
}
