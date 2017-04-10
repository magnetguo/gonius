//----------------------------------------------------------------------------
#include "igame.h"
#include "cgame.h"
#include "dgame.h"
#include "search.h"
//----------------------------------------------------------------------------
int main() {
	DGame cg;
	/** No concrete Move and State type can explicitly occur */
	Search<decltype(cg)::MoveType, decltype(cg)::StateType> s(&cg);

	s.UsePlay(0, 1); // there will be a link warning here, but it's fine

	return 0;
}