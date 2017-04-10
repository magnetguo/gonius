//----------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_REVERSE_FACTORY_H
#define TOFE_HEURISTIC_REVERSE_FACTORY_H
#include "../TofeHeuristicFactory.h"
#include "../../../SgHeuristicEvaluator.h"
#include "TofeHeuristicReverse.h"
#include <string>

using std::string;
//----------------------------------------------------------------------------
class TofeHeuristicReverseFactory : public TofeHeuristicFactory {
	SgHeuristic* makeHeuristic(const TofeGame& g) override {
		return new TofeHeuristicReverse(g);
	}

	// register factory
	static string register_key;
};

#endif // TOFE_HEURISTIC_REVERSE_FACTORY_H