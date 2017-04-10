//----------------------------------------------------------------------------
#ifndef EVALUATOR_H
#define EVALUATOR_H
//----------------------------------------------------------------------------
template <class GameType>
class SgEvaluator {
public:
	virtual double score() const = 0;
	virtual ~SgEvaluator() { }
};

//----------------------------------------------------------------------------
#endif // EVALUATOR_H