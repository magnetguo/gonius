#ifndef SEARCH_H
#define SEARCH_H

#include <limits>
#include "SgGame.h"
#include "Timer.h"

const double DBL_INFINITY = std::numeric_limits<double>::infinity();
//----------------------------------------------------------------------------
template<class State, class Move>
class SgSearch {
public:
	SgSearch(SgGame<State, Move>& s) : m_snap(s) { }

	double getSerachDuration() const {
		return t.getDuration();
	}

	virtual ~SgSearch() {
		delete &m_snap;
	}

	virtual Move generateMove() = 0;
protected:
	SgGame<State, Move>& getSnap() {
		return m_snap;
	}
private:
	SgGame<State, Move>& m_snap;
	Timer t;

	/** not implemented to prevent copying. */
	SgSearch(const SgSearch&);
	SgSearch& operator=(const SgSearch&);
};

#endif // SEARCH_H