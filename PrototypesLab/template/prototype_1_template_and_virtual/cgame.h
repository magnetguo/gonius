//----------------------------------------------------------------------------
/**
 * This file declared a concrete class derived from a template base class
 * with virtual functions, and will make that pure virtual function concrete.
 * The concrete class is not a class template, it will provide type info in
 * the same file.
 */
//----------------------------------------------------------------------------
#ifndef CGAME_H
#define CGAME_H
#include "igame.h"
//----------------------------------------------------------------------------
class CMove{
public:
	CMove() : m_move(0) {}
	CMove(int m) : m_move(m) {}
	int GetMove() {
		return m_move;
	}

private:
	int m_move;
};

class CState{
public:
	CState() : m_state(0) {}
	CState(int s) : m_state(s) {}
	int GetState() {
		return m_state;
	}

private:
	int m_state;
};

class CGame : public IGame<CMove, CState> {
public:
	typedef CMove MoveType;
	typedef CState StateType;
	bool Play(CMove m, CState s) override; // Play is not a template now.
};
#endif // CGAME_H
