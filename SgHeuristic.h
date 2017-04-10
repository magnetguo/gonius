//----------------------------------------------------------------------------
#ifndef HEURISTIC_H
#define HEURISTIC_H
//----------------------------------------------------------------------------
class SgHeuristic {
public:
	virtual double score() const = 0;
	virtual ~SgHeuristic() { }
};

#endif // HEURISTIC_H