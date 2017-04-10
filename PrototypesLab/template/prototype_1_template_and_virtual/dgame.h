//----------------------------------------------------------------------------
/**
 * This file declared a concrete class derived from a template base class
 * with virtual functions, and will make that pure virtual function concrete.
 * The concrete class is not a class template, it will provide type info in
 * the same file.
 */
//----------------------------------------------------------------------------
#ifndef D_GAME_H
#define D_GAME_H
#include "igame.h"
//----------------------------------------------------------------------------
class DMove{
public:
	DMove() : m_move(0) {}
	DMove(double m) : m_move(m) {}
	double GetMove() {
		return m_move;
	}

private:
	double m_move;
};

class DState{
public:
	DState() : m_state(0) {}
	DState(double s) : m_state(s) {}
	double GetState() {
		return m_state;
	}

private:
	double m_state;
};

class DGame : public IGame<DMove, DState> {
public:
	typedef DMove MoveType;
	typedef DState StateType;
	bool Play(DMove m, DState s) override; // Play is not a template now.
};
#endif // D_GAME_H