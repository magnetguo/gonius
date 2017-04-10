//----------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_FACTORY_H
#define TOFE_HEURISTIC_FACTORY_H
#include "../../SgHeuristic.h"
#include "../TofeGame.h"
//----------------------------------------------------------------------------
class TofeHeuristicFactory {
public:
	virtual SgHeuristic* makeHeuristic(const TofeGame& g) = 0;
	virtual ~TofeHeuristicFactory() { }
};

#endif // TOFE_HEURISTIC_FACTORY_H