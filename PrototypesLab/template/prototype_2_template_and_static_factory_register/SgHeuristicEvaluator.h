//----------------------------------------------------------------------------
#ifndef HEURISTIC_EVALUATOR_H
#define HEURISTIC_EVALUATOR_H
#include <map>
#include <string>
#include <vector>
#include <cassert>
#include <iostream>
#include "SgEvaluator.h"

using std::map;
using std::string;
using std::vector;
//----------------------------------------------------------------------------
class SgHeuristic;
//----------------------------------------------------------------------------
template <class GameType, class FactoryType>
class SgHeuristicEvaluator : public SgEvaluator<GameType> {
public:
	typedef map<string, FactoryType*> FactoryMap;

	/** The constructor is to make heuristics by registered factory 
		and store the board to evaluate. */
	SgHeuristicEvaluator(const GameType& g, vector<string> heuristic_ids) {
		assert(!heuristic_ids.empty());
		FactoryMap& factory_map = getFactoryMap();
		assert(!factory_map.empty());
		for (auto it=heuristic_ids.begin(); it != heuristic_ids.end(); it++) {
			std::cout << *it << std::endl;
			auto itm = factory_map.find(*it);
			assert (itm != factory_map.end());
			//	throw "unknown heuristic " + *it;
			m_heuristics.push_back((itm->second)->makeHeuristic(g));
		}
	}

	virtual ~SgHeuristicEvaluator() { 
		for (auto it = m_heuristics.begin(); it != m_heuristics.end(); it++) {
			delete *it;
		}
	}

	/** how to use heuristics we have?
	 	we should define this in derived function. */
	virtual double score() const = 0;

	/** Offered to concrete heuristic factory for registering them. */
	static string registerFactory(string heuristic_id, FactoryType* rf) {
		getFactoryMap().insert(std::make_pair(heuristic_id, rf));
		std::cout << "has registerd" << std::endl;
		std::cout << heuristic_id << std::endl;
		std::cout << getFactoryMap().size() << std::endl;
		return heuristic_id;
	}
protected:
	/** the heuristic we initialized. */
	vector<SgHeuristic*> m_heuristics;
private:
	/** singleton, we only havn one map for an type of evaluator. */
	static FactoryMap& getFactoryMap() {
		static FactoryMap sm_registered_factory;
		return sm_registered_factory;
	}
};

#endif // HEURISTIC_EVALUATOR_H