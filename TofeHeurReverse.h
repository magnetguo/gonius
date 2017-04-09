#ifndef TOFE_HEUR_REVERSE_H
#define TOFE_HEUR_REVERSE_H

#include "TofeHeuristic.h"
//----------------------------------------------------------------------------
class TofeHeurReverse : public TofeHeuristic {
public:
	TofeHeurReverse(const TofeGame& to_evaluate)
		: TofeHeuristic(to_evaluate) { }
	/** return reverse score of the current state,
	which is the proportion of non-reverses
	of all potential reverses. */
	double score() const override;
private:
	int reverseCalc(TofeMove::Movement m) const;

	int reverseNum() const;

	/** Return the all reverses of current board at one direction.
	Used by heuristic functions to evaluate board.*/
	int getReverseSum(bool isCol) const;
};

#endif // TOFE_HEUR_REVERSE_H
