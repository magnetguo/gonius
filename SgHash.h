#ifndef HASH_H
#define HASH_H
#include <random>
#include <cassert>
//----------------------------------------------------------------------------
typedef uint64_t SgHashCode;

class ZobristNumbers {
public:
	static const size_t MAX_HASH_INDEX = 1500;
	static const ZobristNumbers& global() {
		static ZobristNumbers s_zobrist_numbers;
		return s_zobrist_numbers;
	}

	SgHashCode get(size_t index) const {
		assert(index < MAX_HASH_INDEX);
		return m_zobrist_number[index];
	}
private:
	SgHashCode m_zobrist_number[MAX_HASH_INDEX];

	ZobristNumbers() {
		for (size_t i = 0; i < MAX_HASH_INDEX; ++i) {
			m_zobrist_number[i] = rd64();
		}
	}

	std::mt19937_64 rd64;
};

#endif // HASH_H