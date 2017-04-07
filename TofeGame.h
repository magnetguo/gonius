#ifndef TOFE_GAME_H
#define TOFE_GAME_H

#include "SgGame.h"
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <random>

//----------------------------------------------------------------------------
/** Define the type move we will use in 2048 game. */
class TofeMove {
	/** TOFE movement */
public:
	enum Movement {
		TOFE_UP,
		TOFE_DOWN,
		TOFE_LEFT,
		TOFE_RIGHT
	};
	TofeMove() {}

	/** construct with movement type */
	TofeMove(Movement m) 
	: m_movement(m)
	, m_type_movement(true)
	{
		assert(m>=TOFE_UP && m<=TOFE_RIGHT);
	}

	/** construct with random type */
	TofeMove(SgPoint p, int v) : m_p(p), m_value(v), m_type_movement(false) 
	{
		assert(v == 2 || v == 4);
	}

	/** Return whether a movement type */
	bool isMovement() const {
		return m_type_movement;
	}

	Movement GetMovement() const {
		return m_movement;
	}

	SgPoint GetPoint() const {
		return m_p;
	}

	int GetValue() const {
		return m_value;
	}

private:
	Movement m_movement;
	SgPoint m_p;
	int m_value;
	bool m_type_movement;
};

/** Define the type of State of each point */
class TofeState {
public:
	/** Construct as a empty point or border on the board */
	TofeState(SgColor c) 
	: m_color(c), m_value(0) 
	{
		assert(c == SG_EMPTY || c == SG_BORDER);
	}

	/** Construct as a non-empty point on the board.
		We are treated as WHITE, so only type it as white */
	TofeState(SgColor c, int v)
	: m_color(c), m_value(v) {
		assert(c == SG_WHITE);
		//assert(v >= 2 && v <= 131072);
	}

	std::string str() const {
		if (m_color == SG_BORDER)
			return std::string("*");
		else 
			return std::to_string(m_value);
	}

	int GetValue() const {
		return m_value;
	}

	SgColor GetColor() const {
		return m_color;
	}

private:
	SgColor m_color;
	int m_value;
};
//----------------------------------------------------------------------------
bool operator==(const TofeState &&lhs, const TofeState &&rhs);

//----------------------------------------------------------------------------
class TofeGame : public SgGame<TofeState, TofeMove> {
public:
	TofeGame(SgGrid rows, SgGrid cols, SgBlackWhite toPlay);

	bool Play(SgBlackWhite color, TofeMove move) override;

	bool Legal(SgBlackWhite color, TofeMove move) override;

	void Backup() override {
		m_last_board = m_board;
		m_last_empty = m_empty;
	}

	void TakeBack() override {
		m_board = m_last_board;
		m_empty = m_last_empty;
	}

	/** Utility to generate a random number from 0 to m_empty.size()-1 */
	SgPoint PickOneRandomEmptyPos();

	/** Here we can access the name in tmeplate base class.
		We only include the names if we need access them publically, or
		we only need add this-> */
	using SgGame<TofeState, TofeMove>::Print;
	using SgGame<TofeState, TofeMove>::Play;
private:
	/** The storage of still empty point,
		used for random.
		As the frequent erase op in the vector, perhaps list is better,
		but since the size of this vector is small, it's fine. */
	std::vector<SgPoint> m_empty;
	std::vector<SgPoint> m_last_empty;

	/** Move to given direction, return whether we can move. */

	std::random_device rd;

	bool toMove(TofeMove::Movement m);
};


//----------------------------------------------------------------------------
#endif // TOFE_GAME_H