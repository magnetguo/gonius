#ifndef RANDOM_SEARCH_H
#define RANDOM_SEARCH_H
#include "../SgSearch.h"
#include <random>
//----------------------------------------------------------------------------
template<class State, class Move>
class RandomSearch : public SgSearch<State, Move> {
public:
	RandomSearch(SgGame<State, Move>& game)
		: SgSearch<State, Move>(game) { }
	inline Move generateMove();

private:
	std::random_device rd;
};
//----------------------------------------------------------------------------
template<class State, class Move>
Move RandomSearch<State, Move>::generateMove() {
	this->t.start();
	std::vector<Move> moves;
	this->getSnap().generate(moves);
	if (moves.empty())
		return Move();
	std::uniform_int_distribution<int> uni(0, moves.size() - 1);
	int rand = uni(rd);
	this->t.end();
	return moves.at(rand);
}

#endif // RANDOM_SEARCH_H