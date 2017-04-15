#ifndef GAME_H
#define GAME_H

#include "SgHash.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <stack>

//----------------------------------------------------------------------------
/** As for two side player games, we can define the color of both sides,
	and also include the empty and border state for grids on board. */
enum SgColor {
  SG_WHITE,
  SG_BLACK,
  SG_EMPTY,
  SG_BORDER
};

typedef SgColor SgBlackWhite;
typedef SgColor SgBlackWhiteEmpty;


/** Point and Grid type */
typedef unsigned SgPoint;
typedef unsigned SgGrid;

//----------------------------------------------------------------------------
/** Utility functions. */
namespace {
	SgBlackWhite opposite(SgBlackWhite state) {
		return (SgBlackWhite) (SG_WHITE + SG_BLACK - state);
	}	

	/** Compute the board size by cols and rows of inner playing grid. */
	SgPoint computeBoardSize(SgGrid in_cols, SgGrid in_rows) {
		return in_rows * in_cols + 2 * (in_rows+1) + 2 * (in_cols+1);
	}
}
//----------------------------------------------------------------------------
template<class State, class Move>
class SgGame {
public:
	SgGame(SgGrid rows, SgGrid cols, int num_piece, SgBlackWhite toPlay);

	SgGame() = default;

	SgGame(const SgGame& g) = default;

	virtual ~SgGame() {}

	virtual SgGame* copy() const = 0;

	/** Plays a move.
		For turn-based games, plays the move for the current side to play and
		switches the current side.
		Returns whether or not the move was successfully played. */
	bool play(Move move) {
		return play(getToPlay(), move);
	}

	/** Return next player */
    SgBlackWhite getToPlay() const { 
       return m_toPlay; 
    }

    /** Switch the to_play to the opposite side. */
    void switchToPlay() {
    	m_toPlay = opposite(getToPlay());
    }

	/** Plays a move for the given color.
      	Returns whether or not the move was successfully played. 
      	The state State transition rules differ by concrete games. */
	virtual bool play(SgBlackWhite color, Move move) = 0;

  	/** Returns whether or not move is legal.
      	A move is legal if it can be played from the current position for the 
      	specified color. Should allow for making moves out-of-turn. */
  	virtual bool legal(SgBlackWhite color, Move move) = 0;

  	/** Takes back the last played move.
      	Restores the game to the condition it was in before the move was made.
      	Very important to restore the correct side-to-play as searches use this.
      	Returns whether or not the take back was successful. */
  	virtual void takeback() {
  		m_board = m_last_board_stack.top();
  		m_last_board_stack.pop();
  	}

	virtual void backup() {
		m_last_board_stack.push(m_board);
	}

  	/** Returns whether or not the game is over. */
  	virtual bool endOfGame() = 0;
  
  	/** Returns whether or not there is a winner. */
  	virtual bool hasWin() = 0;

  	/** Evaluate the current position as being good or bad for the current player.
      	Used by search algorithms.  Higher values are better. */
  	virtual double evaluate() const = 0;

  	/** Generate the set of all legal moves at current game position,
  		Store them in the vector pointed by moves.(copy ref for speed). */
  	virtual void generate(std::vector<Move>& moves) = 0;

	SgHashCode getHashCode() const;

	/** Print all current board.
		Here we offer a 'template method' like method, traverse all board,
		but not implement by virtual functions. Instead, we use 
		type State's print */
	void print(std::ostream& out) const;

  	/** Return the number of rows in the game. */
  	SgGrid getRows() const {
   		return m_rows;
  	}
  	/** Return the number of columns in the game. */
  	SgGrid getCols() const {
    	return m_cols;
  	}
  	/** Return the size of the game board as the number of points on the board.
      	Includes border points. */
  	SgPoint getSize() const {
    	return m_size;
  	}

	/** Return the size of the game board as the number of points on the board.
	Not includes border points. */
	SgPoint getGameSize() const {
		return m_rows*m_cols;
	}

  	/** Returns the state of the board at the point (row, col).
  		row: 1 to m_row, col: 1 to m_col */
  	State getState(SgGrid row, SgGrid col) const {
  		assert(row > 0 && row <= m_rows);
  		assert(col > 0 && col <= m_cols);
  		SgPoint p = getPt(row, col);
  		return getState(p);
  	}

  	/** Returns the state of the board at point p.
  		Includes color black, white, empty or border, and
  		the piece. */
  	State getState(SgPoint p) const {
  		assert(p >= 0 && p < m_size);
  		return m_board[p];
  	}

	/** Transfer all grid row and col to points on board. */
	SgPoint getPt(SgGrid col_id, SgGrid row_id) const {
		assert(col_id >= 0 && col_id < m_cols+2);
		assert(row_id >= 0 && row_id < m_rows+2);
		return row_id * (m_cols+2) + col_id;
	}

protected:
	void setState(SgPoint p, State s) {
		assert(p < m_size && p >= 0);
		m_board[p] = s;
	}

	/** the board of the game. */
	std::vector<State> m_board;

	/** the board of next step. */
	std::stack<std::vector<State> > m_last_board_stack;

private:
	/** the rows and cols of the board, the actual part. */
	SgGrid m_rows, m_cols;

	/** Actual size of board including border */
	SgPoint m_size;

	/** Number of different types in a grid. Used for Zobrist hasing in future */
	int m_num_piece;

	SgBlackWhite m_firstPlayer, m_toPlay;
};
//----------------------------------------------------------------------------
template<class State, class Move>
SgGame<State, Move>::SgGame(SgGrid rows, SgGrid cols, int num_piece, SgBlackWhite toPlay)
	: m_rows(rows),
	m_cols(cols),
	m_num_piece(num_piece),
	m_size(computeBoardSize(m_rows, m_cols)),
	//m_numPiece(State::GetNumPiece()),
	m_firstPlayer(toPlay),
	m_toPlay(toPlay)
	
{
	m_board = std::vector<State>(m_size, State(SG_BORDER));
	/** The initialization of playing grid is the duty of all concrete games */
}

template<class State, class Move>
SgHashCode SgGame<State, Move>::getHashCode() const {
	SgHashCode code = 0;
	ZobristNumbers zobrist_numbers = ZobristNumbers::global();
	SgGrid rows = getRows();
	SgGrid cols = getCols();
	for (SgGrid it_row = 1; it_row <= rows; it_row++) {
		for (SgGrid it_col = 1; it_col <= cols; it_col++) {
			SgPoint pt = getPt(it_col, it_row);
			State state = getState(pt);
			if (state.getColor() != SG_EMPTY) {
				// all none empty block will have a hash code
				int index = pt * m_num_piece + state.getColor(); 
				// each piece at each block will get an unique hash code
				// from the random hash code library
				code ^= zobrist_numbers.get(index);
			}
		}
	}
	return code;
}

/** Print, as a so called 'template method'.
	Here we will only do the iteration, the print of each point depends
	depends on each State type. */
template<class State, class Move>
void SgGame<State, Move>::print(std::ostream& out) const {
	for (SgGrid n=0; n<m_rows+2; n++) {
		for (SgGrid m=0; m<m_cols+2; m++) {
			out << m_board[getPt(m, n)].str() << "\t";
		}
		out << std::endl;
	}
}


//----------------------------------------------------------------------------
#endif // GAME_H