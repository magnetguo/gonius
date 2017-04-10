//----------------------------------------------------------------------------
/**
 * This file declared a template class with virtual functions.
 * It will be used as abstract base class.
 */
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
#ifndef I_GAME_H
#define I_GAME_H
template<class Move, class State>
class IGame {
public:
	virtual ~IGame() {}
	virtual bool Play(Move m, State s) = 0;
};
#endif // I_GAME_H