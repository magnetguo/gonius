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
	TofeMove(SgPoint p, int v) : m_generation(p, v), m_type_movement(false) 
	{
		assert(v == 2 || v == 4);
	}

	/** Return whether a movement type */
	bool isMovement() const {
		return m_type_movement;
	}

	Movement getMovement() const {
		return m_movement;
	}

	SgPoint getPoint() const {
		return m_generation.first;
	}

	int getValue() const {
		return m_generation.second;
	}

private:
	Movement m_movement;
	std::pair<SgPoint, int> m_generation;
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

	int getValue() const {
		return m_value;
	}

	SgColor getColor() const {
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

	bool play(SgBlackWhite color, TofeMove move) override;

	bool legal(SgBlackWhite color, TofeMove move) override;

	void backup() override {
		m_last_board = m_board;
		m_last_empty = m_empty;
	}

	void takeback() override {
		m_board = m_last_board;
		m_empty = m_last_empty;
	}

	/** Utility to generate a random number from 0 to m_empty.size()-1 */
	SgPoint pickOneRandomEmptyPos();

	/** Return the query of empty blocks. */
	int getEmptyNum() const {
		return m_empty.size();
	}

	/** Here we can access the name in template base class.
		We only include the names if we need access them by public interface, or
		we only need add this-> */
	using SgGame<TofeState, TofeMove>::print;
	using SgGame<TofeState, TofeMove>::play;
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