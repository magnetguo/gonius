#ifndef ALPHA_BETA_SEARCH_H
#define ALPHA_BETA_SEARCH_H

#include "../SgSearch.h"
#include "AlphaBetaSearchHashData.h"
#include <vector>

const unsigned DEFAULT_DEPTH = 3;
//----------------------------------------------------------------------------
template<class State, class Move>
class AlphaBetaSearch : public SgSearch<State, Move, ABSearchHashData<Move> > {
public:
	typedef ABSearchHashData<Move> HashDataType;
	AlphaBetaSearch(int depth = DEFAULT_DEPTH,
					SgHashTable<ABSearchHashData<Move>>* black_hash = 0,
					SgHashTable<ABSearchHashData<Move>>* white_hash = 0,
					double alpha = -DBL_INFINITY, double beta = DBL_INFINITY)
		: SgSearch<State, Move, ABSearchHashData<Move> >()
		, m_depth(depth), m_alpha(alpha), m_beta(beta) {}
	
	inline Move generateMove();
private:
	unsigned m_depth;

	double m_alpha, m_beta;

	double alphaBeta(unsigned depth, double alpha, double beta, Move& move);
};

//----------------------------------------------------------------------------
template<class State, class Move>
double AlphaBetaSearch<State, Move>::alphaBeta(unsigned depth, double alpha, double beta, Move& best_move) {
	if (this->getBlackHash() && this->getWhiteHash()) {
		ABSearchHashData<Move> hash_data;
		if (this->getSnap()->getToPlay() == SG_BLACK) {
			if (this->getBlackHash()->lookup(this->getSnap()->getHashCode(), 
				hash_data)
			&& hash_data.getDepth() >= depth) {
				if (hash_data.isExactValue()) {
					best_move = hash_data.getBestMove();
					return -hash_data.getValue();
				} else
					hash_data.adjustBounds(alpha, beta);
			}
		} else {
			if (this->getWhiteHash()->lookup(this->getSnap()->getHashCode(), 
				hash_data)
			&& hash_data.getDepth() >= depth) {
				if (hash_data.isExactValue()) {
					best_move = hash_data.getBestMove();
					return -hash_data.getValue();
				} else
					hash_data.adjustBounds(alpha, beta);
			}
		}
	}
	std::vector<Move> moves;
	this->getSnap()->generate(moves);
	
	if (this->getSnap()->hasWin())
		return -DBL_INFINITY;

	if (depth == 0) {
#ifdef DEBUG
		std::cout << "evaluate!" << std::endl;
#endif
		return this->getSnap()->evaluate();
	}

	if (moves.size() == 0 || this->getSnap()->endOfGame()) {
		return 0;
	}

	double local_alpha = alpha, best_value = -DBL_INFINITY;

	for (size_t i = 0; i < moves.size(); ++i) {
#ifdef DEBUG
		std::cout << depth << "->" << i << ": " << moves.size() << std::endl;
#endif
		Move move = moves.at(i);
		bool played = this->getSnap()->play(move);
		if (!played) {
#ifdef DEBUG
		std::cout << "playing: "<< this->getSnap()->getToPlay() << std::endl;
		std::cout << "break!" << std::endl;
#endif
			break;
		}

		Move nullmove = Move();
		double value = -alphaBeta(depth - 1, -beta, -local_alpha, nullmove);
		this->getSnap()->takeback();
		this->getSnap()->switchToPlay();
		if (value > best_value) {
			best_value = value;
			best_move = move;
		}
		if (best_value >= beta) {
#ifdef DEBUG
			std::cout << "beta pruning" << std::endl;
#endif
			break;
		}		
		if (best_value > local_alpha)
			local_alpha = best_value;
	}
	if (this->getBlackHash() && this->getWhiteHash()) {
		bool is_upper_bound = false, is_lower_bound = false, is_exact_value = false;
		SgBlackWhite to_play = this->getSnap()->getToPlay();
		if (best_value >= beta)
			is_upper_bound = true;
		else if (best_value <= local_alpha)
			is_lower_bound = true;
		else
			is_exact_value = true;
		ABSearchHashData<Move> new_data(depth, best_value, best_move, is_upper_bound, is_lower_bound, is_exact_value);
		
		if (to_play == SG_BLACK) {
			this->getBlackHash()->store(this->getSnap()->getHashCode(), new_data);
		} else {
			this->getWhiteHash()->store(this->getSnap()->getHashCode(), new_data);
		}
	}
	return best_value;
}

template<class State, class Move>
Move AlphaBetaSearch<State, Move>::generateMove() {
	this->t.start();

	Move move;
	double value = alphaBeta(m_depth, m_alpha, m_beta, move);
	
	this->t.end();
	return move;
}

#endif // ALPHA_BETA_SEARCH_H