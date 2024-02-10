/**
 * @file
 * @brief     This file contains the implementation of the NatCountersTable class and its functionality.
 *            Basically this class encapsulates the NatCountersTable related functionalities, like
 *            adding and deleting elements to a nat table, with respect to the requirements.
 */
#include "NatCountersTable.hpp"

#include "common/utils/logger/Logger.hpp"

#include <algorithm>  // for std::find

using brain::engines::security_events::NatCountersTable;

bool
NatCountersTable::Append(NatCountersTableEntry const& entry, NatCountersEntriesStruct const& newNatTableRow)
{
    auto& entryTable = m_natCountersTable[entry];
    // max nat table size exceeded => nat flooding
    if (entryTable.size() >= m_maxNatTableSize)
    {
        return false;
    }

    // check if the list already contains such an entry
    auto entryIt = std::find(entryTable.begin(), entryTable.end(), newNatTableRow);
    if (entryIt == entryTable.end())
    {
        // entry not in table, so add it
        entryTable.push_back(newNatTableRow);
        return true;
    }

    // entry is in table. => duplicated nat entry
    return false;
}

bool
NatCountersTable::Delete(NatCountersTableEntry const& entry, NatCountersEntriesStruct const& natTableRow)
{
    auto& entryTable = m_natCountersTable[entry];
    // lookup if the element exists in the list
    auto       rowIterator = std::find(entryTable.begin(), entryTable.end(), natTableRow);
    bool const retVal      = rowIterator != entryTable.end();
    if (retVal)
    {
        std::ignore = entryTable.erase(rowIterator);
    }
    return retVal;
}

void
NatCountersTable::constructionSizesWarning(size_t actual, size_t max) const
{
    LOG_WARNING << "NAT max table size in configuration is very big " << actual << ", default value " << max
                << " will be used." << LOG_NOOP;
}