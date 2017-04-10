//----------------------------------------------------------------------------
/**
 * This is the implementation of cgame
 */
//----------------------------------------------------------------------------
#include "cgame.h"
#include "iostream"
//----------------------------------------------------------------------------
bool
CGame::Play(CMove m, CState s) {
	std::cout << "this is cgame playing" << std::endl;
	return (m.GetMove() == s.GetState());
}
