#ifndef SEARCH_H
#define SEARCH_H

#include <limits>
#include "SgGame.h"
#include "Timer.h"
#include "SgHashTable.h"

const double DBL_INFINITY = std::numeric_limits<double>::infinity();
//----------------------------------------------------------------------------
template<class State, class Move, class DATA>
class SgSearch {
public:
	SgSearch(SgGame<State, Move>& s, 
		SgHashTable<DATA>* black_hash, 
		SgHashTable<DATA>* white_hash) 
	: m_snap(s), 
	m_black_hash(black_hash),
	m_white_hash(white_hash) { }

	double getSerachDuration() const {
		return t.getDuration();
	}

	SgHashTable<DATA>* getBlackHash() {
		return m_black_hash;
	}

	SgHashTable<DATA>* getWhiteHash() {
		return m_white_hash;
	}

	virtual ~SgSearch() {
		delete &m_snap;
	}

	virtual Move generateMove() = 0;
protected:
	SgGame<State, Move>& getSnap() {
		return m_snap;
	}
	Timer t;
private:
	SgGame<State, Move>& m_snap;

	SgHashTable<DATA>* m_black_hash;

	SgHashTable<DATA>* m_white_hash;

	/** not implemented to prevent copying. */
	SgSearch(const SgSearch&);
	SgSearch& operator=(const SgSearch&);
};

#endif // SEARCH_H