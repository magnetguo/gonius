#ifndef HEURISTIC_WEIGHT_EVALUATOR_H
#define HEURISTIC_WEIGHT_EVALUATOR_H

#include "SgHeuristic.h"
#include <string>
#include <vector>
//----------------------------------------------------------------------------
template <class GameType, class FactoryType>
class SgHeuristicWeightEvaluator : public SgHeuristicEvaluator<GameType, FactoryType> {
public:
	SgHeuristicWeightEvaluator(std::vector<std::string> heuristic_ids, 
		std::vector<double> heuristic_weights, const GameType& g)
		: SgHeuristicEvaluator<GameType, FactoryType>(g, heuristic_ids),
		m_heuristic_weights(heuristic_weights) {
		assert(heuristic_ids.size() == heuristic_weights.size());
	}
	double score() const override {
		double score = 0.0;
		assert(!this->m_heuristics.empty());
		for (size_t i=0; i != m_heuristics.size(); i++) {
			score += m_heuristics[i]->score() * m_heuristic_weights[i];
		}
		return score;
	}
private:
	std::vector<double> m_heuristic_weights;
};

#endif // HEURISTIC_WEIGHT_EVALUATOR_H
