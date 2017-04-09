#ifndef TOFE_HEURISTIC_H
#define TOFE_HEURISTIC_H

#include "TofeGame.h"
//----------------------------------------------------------------------------
class TofeHeuristic {
public:
	TofeHeuristic(const TofeGame& game_to_evaluate)
		: m_to_evaluate_game(game_to_evaluate) { }
	
	virtual ~TofeHeuristic() { }

	virtual double score() const = 0;
protected:
	const TofeGame& m_to_evaluate_game;
};

#endif // TOFE_HEURISTIC_H
