//----------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_H
#define TOFE_HEURISTIC_H
#include "TofeGame.h"
#include "SgHeuristic.h"
//----------------------------------------------------------------------------
class TofeHeuristic : public SgHeuristic{
public:
	TofeHeuristic(const TofeGame& g):
		m_to_evaluate(g) { }
	virtual ~TofeHeuristic() { }
protected:
	const TofeGame& m_to_evaluate;
};

//----------------------------------------------------------------------------
#endif // TOFE_HEURISTIC_H