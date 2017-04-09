#ifndef TOFE_HEUR_DIFF_H
#define TOFE_HEUR_DIFF_H
#include "TofeHeuristic.h"
//----------------------------------------------------------------------------
class TofeHeurDiff : public TofeHeuristic {
public:
	TofeHeurDiff(const TofeGame& to_evaluate)
		: TofeHeuristic(to_evaluate) { }
	double score() const override;
private:
	int diffLevel(int v1, int v2) const;
	int diffSum() const;
};

#endif // TOFE_HEUR_DIFF_H