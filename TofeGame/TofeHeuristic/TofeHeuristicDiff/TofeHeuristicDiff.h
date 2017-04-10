//----------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_DIFF_H
#define TOFE_HEURISTIC_DIFF_H

#include "../TofeHeuristic.h"

//----------------------------------------------------------------------------
class TofeHeuristicDiff : public TofeHeuristic {
public:
	TofeHeuristicDiff(const TofeGame& g)
	: TofeHeuristic(g) { }

	double score() const override;
private:
	int diffLevel(int v1, int v2) const;
	int diffSum() const;
};

#endif // TOFE_HEURISTIC_DIFF_H