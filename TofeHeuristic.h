//---------------------------------------------------------------------------------------------
#ifndef TOFE_HEURISTIC_H
#define TOFE_HEURISTIC_H
#include "TofeGame.h"
//---------------------------------------------------------------------------------------------
/** return reverse score of the current state,
	which is the proportion of non-reverses 
	of all potential reverses. */
double reverseScore(const TofeGame& g);

/** return empty score of the current state,
	which is the proportion of empty blocks of all blocks. */
double emptyScore(const TofeGame& g);

/** return diff score of the current state,
	which is the diff level between two adj blocks. */

//---------------------------------------------------------------------------------------------
#endif // TOFE_HEURISTIC_H