#ifndef ALPHA_BETA_SEARCH_H
#define ALPHA_BETA_SEARCH_H

#include "../SgSearch.h"
#include <vector>

const unsigned DEFAULT_DEPTH = 3;
//----------------------------------------------------------------------------
template<class State, class Move>
class AlphaBetaSearch : public SgSearch<State, Move> {
public:
	AlphaBetaSearch(SgGame<State, Move>& game,
					int depth = DEFAULT_DEPTH,
					double alpha = -DBL_INFINITY, double beta = DBL_INFINITY)
		: SgSearch(game), m_depth(depth), m_alpha(alpha), m_beta(beta) {}
	
	inline Move generateMove();
private:
	unsigned m_depth;

	double m_alpha, m_beta;

	double alphaBeta(unsigned depth, double alpha, double beta, Move& move);
};

//----------------------------------------------------------------------------
template<class State, class Move>
double AlphaBetaSearch<State, Move>::alphaBeta(unsigned depth, double alpha, double beta, Move& best_move) {
	std::vector<Move> moves;
	getSnap().generate(moves);

	if (getSnap().hasWin())
		return -DBL_INFINITY;

	if (depth == 0)
		return getSnap().evaluate();

	if (moves.size() == 0 || getSnap().endOfGame()) {
		return 0;
	}

	double local_alpha = alpha, best_value = -DBL_INFINITY;

	for (size_t i = 0; i < moves.size(); ++i) {
		Move move = moves.at(i);
		bool played = getSnap().play(move);
		if (!played) break;
		double value = -alphaBeta(depth - 1, -beta, -local_alpha, Move());
		getSnap().takeback();
		if (value > best_value) {
			best_value = value;
			best_move = move;
		}
		if (best_value >= beta)
			break;
		if (best_value > local_alpha)
			local_alpha = best_value;
	}

	return best_value;
}

template<class State, class Move>
Move AlphaBetaSearch<State, Move>::generateMove() {
	Move move;
	double value = alphaBeta(m_depth, m_alpha, m_beta, move);
	return move;
}

#endif // ALPHA_BETA_SEARCH_H