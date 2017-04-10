//----------------------------------------------------------------------------
/**
 * This is the implementation of dgame
 */
//----------------------------------------------------------------------------
#include "dgame.h"
#include "iostream"
//----------------------------------------------------------------------------
bool
DGame::Play(DMove m, DState s) {
	std::cout << "this is dgame playing" << std::endl;	
	return (m.GetMove() != s.GetState()); // different type and different op
}