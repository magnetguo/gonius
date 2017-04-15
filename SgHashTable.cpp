#include "SgHashTable.h"

/** Writes statistics on hash table use (not the content) */
void SgHashStatistics::
PrintStats(std::ostream& out) const {
  out << "HashTableStatistics:\n"
      << "StoresAttempt "  << m_num_stores << '\n'
      << "StoresSuccess "  << m_num_newstores << '\n'
      << "LookupAttempt "  << m_num_lookups << '\n'
      << "LookupSuccess "  << m_num_found << '\n'
      << "Collisions "     << m_num_collisions << '\n'
      << "Collision rate " << static_cast<float>(m_num_collisions)
                              / m_num_stores * 100 << "\n"
      << "Entry size "     << m_entry_size << '\n'
      << "HashTable Size " << m_hash_size << '\n'
      << "HashTable Size in Memory " << m_hash_size * m_entry_size / 1000 << "KB"
      << std::endl;
}

std::ostream& 
operator<<(std::ostream& out, const SgHashStatistics& stats)
{    
  stats.PrintStats(out);
  return out;
}
