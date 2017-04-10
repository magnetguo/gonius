//----------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_DIFF_FACTORY_H
#define TOFE_HEURISTIC_DIFF_FACTORY_H
#include "TofeHeuristicFactory.h"
#include "SgHeuristicEvaluator.h"
#include "TofeHeuristicDiff.h"
#include <string>

using std::string;
//----------------------------------------------------------------------------
class TofeHeuristicDiffFactory : public TofeHeuristicFactory {
	SgHeuristic* makeHeuristic(const TofeGame& g) override {
		return new TofeHeuristicDiff(g);
	}

	// register factory
	static string register_key;
};

#endif // TOFE_HEURISTIC_DIFF_FACTORY_H