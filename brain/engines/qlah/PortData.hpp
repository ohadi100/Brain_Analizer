#pragma once
/**
 * @file
 * @brief     PortData data class
 */

#include "brain/histograms/ScalarHistogram.hpp"
#include "policer/PolicerTokenBucket.hpp"
#include "common/utils/CPP/optional/Optional.hpp"

namespace brain
{
namespace data_unit
{

using histogram_lib::PolicerTokenBucket;
using brain::histogram::ScalarHistogram;

class PortData
{
public:
    ScalarHistogram::BinIntervalsVector const m_linkUtilizationRateBins = { 0.0, 1.0, 10.0, 20.0, 30.0, 40.0, 50.0, 60.0, 70.0, 80.0, 90.0 };

    PortData(uint32_t bucketThresholdRate, uint32_t bucketMaxBurst)
      : m_tokenBucket(bucketThresholdRate, bucketMaxBurst)
      , m_linkUtilizationInHistogram(m_linkUtilizationRateBins)
    {}

    void addTimeStamp(uint64_t timeStamp)
    {
        if (0U == m_firstSeenTimeStamp)
        {
            m_firstSeenTimeStamp = timeStamp;
        }

        m_lastSeenTimeStamp = timeStamp;
    }

    bool m_isMonitoringDoS = true;

    uint64_t m_firstSeenTimeStamp{};
    uint64_t m_lastSeenTimeStamp{};

    cm::optional<uint64_t> m_discardedFramesValue;
    cm::optional<uint64_t> m_unknownProtocolFramesValue;
    cm::optional<uint64_t> m_illegalVlanDropValue;
    cm::optional<uint64_t> m_illegalIpDropValue;
    cm::optional<uint64_t> m_vlanIngressDropValue;
    cm::optional<uint64_t> m_vlanEgressDropValue;
    cm::optional<uint64_t> m_vlanLookupMissDropValue;
    cm::optional<uint64_t> m_aclLookupMissDropValue;
    cm::optional<uint64_t> m_ifInOctetsValue;
    cm::optional<uint64_t> m_etherStatsPkts64OctetsValue;
    cm::optional<uint64_t> m_etherStatsPkts65to127OctetsValue;
    cm::optional<uint64_t> m_etherStatsPkts128to255OctetsValue;
    cm::optional<uint64_t> m_etherStatsPkts256to511OctetsValue;
    cm::optional<uint64_t> m_etherStatsPkts512to1023OctetsValue;
    cm::optional<uint64_t> m_etherStatsPkts1024to1518OctetsValue;
    cm::optional<uint64_t> m_etherStatsOversizePktsValue;
    cm::optional<uint64_t> m_etherStatsUndersizePktsValue;

    PolicerTokenBucket m_tokenBucket;

    ScalarHistogram m_linkUtilizationInHistogram;
};

} // namespace data_unit
} // namespace brain
