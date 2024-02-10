/**
 * @file
 * @brief     This file contains the definition of the NatCountersTable class and its functionality.
 *            Basically this class encapsulates the NatCountersTable related functionalities, like
 *            adding and deleting elements to a nat table, with respect to the requirements.
 */
#ifndef NAT_COUNTERS_TABLE_HPP
#define NAT_COUNTERS_TABLE_HPP

#include <list>
#include <unordered_map>
#include "NatCountersEntries.hpp"
#include "NatCountersTableEntry.hpp"
#include "brain/config/BrainConfigConstants.hpp"
#include "common/configuration/Configuration.hpp"

namespace brain
{
namespace engines
{
namespace security_events
{

using NatCountersEntriesList = std::list<NatCountersEntriesStruct>;
using ConfigurationPtr       = common::configuration::Pointer;

// maximum size of NAT table, if cannot be read out from the static configuration
static constexpr uint32_t NAT_TABLE_SIZE_MAX = 500U;

class NatCountersTable
{
public:
    /**
     * @brief   Constructor of the NatCountersTable class.
     */
    NatCountersTable() = default;

    /**
     * @brief Constructor for the NatCountersTable with support for configuration read-out for the MAX_NAT_TABLE_SIZE
     * parameter
     * @param config - pointer to the configuration object.
     * @return NatCountersTable object with either the default size (fail to read out the config data),
     *         the configuration specified size (successfully read out the config data) or with size 0, in case when
     *         the configuration pointer is null.
     */
    explicit NatCountersTable(ConfigurationPtr config)
    {
        m_maxNatTableSize = NAT_TABLE_SIZE_MAX;
        if (config)
        {
            std::ignore = config->GetValue(brain::config_keys::MAX_NAT_TABLE_SIZE, m_maxNatTableSize);
        }
        if (m_maxNatTableSize >= std::numeric_limits<uint16_t>::max())
        {
            constructionSizesWarning(m_maxNatTableSize, NAT_TABLE_SIZE_MAX);
            m_maxNatTableSize = NAT_TABLE_SIZE_MAX;
        }
    }

    /**
     * @brief Constructor of the NatCountersTable class, which initializes also the
     * maximum nat table size parameter.
     * @param maxNatTableSize - maximum number of entries in the nat table
     * @return NatCountersTable object
     */
    explicit NatCountersTable(uint32_t maxNatTableSize)
      : m_maxNatTableSize(maxNatTableSize)
    {
    }

    /**
     * @brief Returns a reference to the list of entries in a nat table.
     * @param entry - used to identify the nat table in the map
     * @return the reference to the list of the nat table entries (nat table rows)
     */
    inline NatCountersEntriesList const&
    GetEntryList(NatCountersTableEntry entry)
    {
        return m_natCountersTable[entry];
    }

    /**
     * @brief Sets the maximum table size value
     * @param newSize - the new table size
     */
    inline constexpr void
    SetMaxNatTableSize(uint32_t newSize)
    {
        m_maxNatTableSize = newSize;
    }

    /**
     * @brief Gets the maximum number of entries in a nat table
     * @return the maximum number of entries in a nat table
     */
    inline constexpr uint32_t
    GetMaxNatTableSize() const
    {
        return m_maxNatTableSize;
    }

    /**
     * @brief Gets the actual size of the specified nat table
     * @param entry - used to identify the nat table in the map
     * @return the size of the selected nat table (list)
     */
    inline uint64_t
    GetCurrentTableSize(NatCountersTableEntry const& entry) const
    {
        return m_natCountersTable.at(entry).size();
    }

    /**
     * @brief Returns the actual number of nat tables in the map.
     * @return the actual number of nat tables.
     */
    inline uint64_t
    GetNumTables() const
    {
        return m_natCountersTable.size();
    }

    /**
     * @brief Tests if there are any nat tables in the map.
     * @return true - if there are no nat tables in the map (empty map)
     *         false - if there are at least one nat table in the map
     */
    inline bool
    IsEmpty() const
    {
        return m_natCountersTable.empty();
    }

    /**
     * @brief Tests if the maximum number of entries reached in a given nat table.
     * @param entry - used to identify the nat table
     * @return true - if the maximum nat table size is equal with the size of the selected table
     *         false - otherwise
     */
    inline bool
    IsMaxReached(NatCountersTableEntry const& entry) const
    {
        return m_maxNatTableSize == static_cast<uint32_t>(m_natCountersTable.at(entry).size());
    }

    /**
     * @brief Appends a new table row to the specified nat table, if not already there, and if there is space
     * @param entry - used to identify the nat table
     * @param newNatTableRow - the row to be appended to the selected nat table
     * @return Returns the status of the append operation.
     *         true - the new table row was successfully appended to the selected nat table
     *         false - in the case when there are no more space in the selected nat table (maximum number of entries
     * reached) false - when the new table row is already presend in the selected nat table (duplicate entry) If this
     * function returns false, then the IsMaxReached method shall be called, to decide on which case we are.
     */
    bool Append(NatCountersTableEntry const& entry, NatCountersEntriesStruct const& newNatTableRow);

    /**
     * @brief Deletes the natTableRow from the selected nat table
     * @param entry - used to identify the nat table
     * @param natTableRow - the row to be deleted from the selected nat table
     * @return true - if the row was found in the nat table, and was successfully removed
     *         false - if the row was not found in the selected nat table.
     */
    bool Delete(NatCountersTableEntry const& entry, NatCountersEntriesStruct const& natTableRow);

private:
    void constructionSizesWarning(size_t actual, size_t max) const;

    // the map of the nat tables. one table is identified by the entry and consist of the list of rows
    std::unordered_map<NatCountersTableEntry, NatCountersEntriesList> m_natCountersTable;
    // the maximum nat table size refers to the maximum size of the list of NatCountersEntriesStruct part
    uint32_t m_maxNatTableSize{};
};

}  // namespace security_events
}  // namespace engines
}  // namespace brain


#endif  // NAT_COUNTERS_TABLE_HPP
