//----------------------------------------------------------------------------
/**
 * This file will offer another template class which will polymorphicly use
 * Play defined in igame
 */
//----------------------------------------------------------------------------
#ifndef SEARCH_H
#define SEARCH_H
#include "igame.h"
//----------------------------------------------------------------------------
template<class Move, class State>
class Search{
public:
	Search(IGame<Move, State>* new_game) : m_game(new_game) {}
	bool UsePlay(Move m, State s) {
		m_game->Play(m, s);
	}
private:
	IGame<Move, State>* m_game;
};
#endif // SEARCH_H