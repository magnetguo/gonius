#ifndef TOFE_HEUR_EMPTY_H
#define TOFE_HEUR_EMPTY_H

#include "../TofeHeuristic.h"
//----------------------------------------------------------------------------
class TofeHeuristicEmpty : public TofeHeuristic{
public:
	TofeHeuristicEmpty(const TofeGame& g)
		: TofeHeuristic(g) { }

	/** return empty score of the current state,
	which is the proportion of empty blocks of all blocks. */
	double score() const override {
		return (m_to_evaluate.getToPlay() == SG_WHITE) ?
		(double)m_to_evaluate.getEmptyNum() / (double)m_to_evaluate.getGameSize():
		-((double)m_to_evaluate.getEmptyNum() / (double)m_to_evaluate.getGameSize());
	}
};

#endif // TOFE_HEUR_REVERSE_H
