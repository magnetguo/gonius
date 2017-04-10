//----------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_EMPTY_FACTORY_H
#define TOFE_HEURISTIC_EMPTY_FACTORY_H
#include "../TofeHeuristicFactory.h"
#include "../../../SgHeuristicEvaluator.h"
#include "TofeHeuristicEmpty.h"
#include <string>

using std::string;
//----------------------------------------------------------------------------
class TofeHeuristicEmptyFactory : public TofeHeuristicFactory {
	SgHeuristic* makeHeuristic(const TofeGame& g) override {
		return new TofeHeuristicEmpty(g);
	}

	// register factory
	static string register_key;
};

#endif // TOFE_HEURISTIC_EMPTY_FACTORY_H