//----------------------------------------------------------------------------
#ifndef HASHTABLE_H
#define HASHTABLE_H
#include "SgHash.h"
#include <algorithm>
#include <iostream>
//----------------------------------------------------------------------------
/** Hash size should be a prime number to reduce collisions */
const int DEFAULT_HASHSIZE = 1280023;

/** Entry in a hash table, code and data. */
template<class DATA>
struct SgHashEntry {
	SgHashEntry() = default;

	SgHashEntry(const SgHashCode& code, const DATA& data)
		: m_hash_code(code),
		m_data(data) {}

	SgHashCode m_hash_code;
	DATA m_data;
};
//----------------------------------------------------------------------------

struct SgHashStatistics {
   
  SgHashStatistics()
    : m_num_collisions(0),
      m_num_stores(0),
      m_num_newstores(0),
      m_num_lookups(0),
      m_num_found(0),
      m_entry_size(0),
      m_hash_size(0) {}
    
  /** Print formatted data to a stream */
  void PrintStats(std::ostream& out) const;
    
  /** Number of collisions on store */
  int m_num_collisions;
  
  /** Total number of stores attempted */
  int m_num_stores;
  
  /** Number of successful stores */
  int m_num_newstores;
  
  /** Total number of lookups attempted */
  int m_num_lookups;
  
  /** Number of successful lookups */
  int m_num_found; 
  
  /** Records the entry size in memory of the hash */
  int m_entry_size;
  
  /** The number of entries the hash contains */
  int m_hash_size;
};

/** Writes statistics on hash table use (not the content) */
std::ostream& operator<<(std::ostream& out, const SgHashStatistics& stats);

//----------------------------------------------------------------------------
/** Hash table implements an array of DATA */
template<class DATA>
class SgHashTable {
public:
	explicit SgHashTable(SgHashStatistics* stats = 0,
		int max_hash = DEFAULT_HASHSIZE);

	/** Copy constructor. */
	SgHashTable(const SgHashTable&);

	~SgHashTable();

	/** Leaves the positions in the hash table, but set all depth to zero. */
	void age();

	/** Clear the hash table by marking the entries as invalid. */
	void clear();

	/** return true and the data stored under that code, or false if none stored. */
	bool lookup(SgHashCode code, DATA& data) const;

	/** Try to store data under the hash code.
		Return whether the data was stored. The only reason for not storing it would be some
		better data already hashing to the same hash code. */
	bool store(SgHashCode code, DATA& data);

	/** Size of hash table. */
	int getMaxHash() const;

	SgHashTable& operator=(const SgHashTable& other);
private:
	/** Table of hash entries. */
	SgHashEntry<DATA>* m_entry;

	/** Size of hash table. */
	int m_max_hash;

	SgHashStatistics* m_stats;
};

template<class DATA>
SgHashTable<DATA>::SgHashTable(SgHashStatistics* stats, int max_hash)
	: m_entry(0), m_max_hash(max_hash), m_stats(stats) {
	m_entry = new SgHashEntry<DATA>[m_max_hash];
	clear();
	if (m_stats) {
    	m_stats->m_hash_size = m_max_hash;
    	m_stats->m_entry_size = sizeof m_entry[0];
  	}
}

template<class DATA>
SgHashTable<DATA>::SgHashTable(const SgHashTable& other)
	: m_entry(new SgHashEntry<DATA>[other.m_max_hash]),
	m_max_hash(other.m_max_hash),
	m_stats(other.m_stats ? new SgHashStatistics(*(other.m_stats)) : 0) {
	for (int i = 0; i < m_max_hash; i++)
		m_entry[i] = other.m_entry[i];
}

template<class DATA>
SgHashTable<DATA>::~SgHashTable() {
	delete[] m_entry;
	delete m_stats;
}

template<class DATA>
void SgHashTable<DATA>::age() {
	for (int i = m_max_hash - 1; i >= 0; --i) {
		m_entry[i].m_data.ageData();
	}
}

template<class DATA>
void SgHashTable<DATA>::clear() {
	for (int i = m_max_hash - 1; i >= 0; --i) {
		m_entry[i].m_data.invalidate();
	}
}

template<class DATA>
int SgHashTable<DATA>::getMaxHash() const {
	return m_max_hash;
}

template<class DATA>
bool SgHashTable<DATA>::store(SgHashCode code, DATA& data) {
	if (m_stats) ++(m_stats->m_num_stores);
	int index = code % m_max_hash;
	SgHashEntry<DATA>& entry = m_entry[index];
	if (entry.m_data.isValid() && code != entry.m_hash_code) {
		m_stats && ++(m_stats->m_num_collisions);
	} // collision
	if (!entry.m_data.isValid() || data.isBetterThan(entry.m_data)) {
		entry.m_hash_code = code;
		entry.m_data = data;
		m_stats && ++(m_stats->m_num_newstores);
		return true;
	}
	return false;
}

template<class DATA>
bool SgHashTable<DATA>::lookup(SgHashCode code, DATA& data) const {
	m_stats && ++(m_stats->m_num_lookups);
	int h = code % m_max_hash;
	const SgHashEntry<DATA>& entry = m_entry[h]; // just const ref, data is still in entry
	if (entry.m_data.isValid() && entry.m_hash_code == code) {
		data = entry.m_data;
		m_stats && ++(m_stats->m_num_found);
		return true;
	}
	return false;
}

template<class DATA>
SgHashTable<DATA>& SgHashTable<DATA>::operator=(const SgHashTable<DATA>& other) {
	SgHashTable<DATA> temp(other); // no to touch the real data
	swap(m_entry, temp.m_entry);
	swap(m_max_hash, temp.m_max_hash);
	swap(m_stats, temp.m_stats);
	return *this;
}

#endif // HASHTABLE_H