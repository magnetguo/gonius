//----------------------------------------------------------------------------
#ifndef HEURISTIC_AVERAGE_EVALUATOR_H
#define HEURISTIC_AVERAGE_EVALUATOR_H
#include "SgHeuristicEvaluator.h"
//----------------------------------------------------------------------------
template <class GameType, class FactoryType>
class SgHeuristicAverageEvaluator : public SgHeuristicEvaluator<GameType, FactoryType> {
public:
	SgHeuristicAverageEvaluator(const GameType& g, vector<string> heuristic_ids):
	SgHeuristicEvaluator<GameType, FactoryType>(g, heuristic_ids) { }

	double score() const override {
		double score = 0.0;
		assert (!this->m_heuristics.empty());
		for (auto it = this->m_heuristics.begin(); it != this->m_heuristics.end(); it++) {
			score += (*it)->score();
		}
		score /= this->m_heuristics.size();
		return score;			
	}
};


#endif // HEURISTIC_AVERAGE_EVALUATOR_H