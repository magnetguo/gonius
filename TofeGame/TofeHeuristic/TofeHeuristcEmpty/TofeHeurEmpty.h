#ifndef TOFE_HEUR_EMPTY_H
#define TOFE_HEUR_EMPTY_H

#include "TofeHeuristic.h"
//----------------------------------------------------------------------------
class TofeHeurEmpty : public TofeHeuristic{
public:
	TofeHeurEmpty(const TofeGame& to_evaluate)
		: TofeHeuristic(to_evaluate) { }

	/** return empty score of the current state,
	which is the proportion of empty blocks of all blocks. */
	double score() const override {
		return (double)m_to_evaluate_game.getEmptyNum() / (double)m_to_evaluate_game.getGameSize();
	}
};

#endif // TOFE_HEUR_REVERSE_H
