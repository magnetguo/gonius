#ifndef GAME_H
#define GAME_H

#include <cassert>
#include <iostream>
#include <vector>

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
template<class State, class Move>
class SgGame {
public:
	SgGame(SgGrid rows, SgGrid cols, SgBlackWhite toPlay);

	virtual ~SgGame() {}

	/** Plays a move.
		For turn-based games, plays the move for the current side to play and
		switches the current side.
		Returns whether or not the move was successfully played. */
	bool Play(Move move) {
		return Play(GetToPlay(), move);
	}

	/** Return next player */
    SgBlackWhite GetToPlay() const { 
       return m_toPlay; 
    }

    /** Switch the to_play to the opposite side. */
    void SwitchToPlay() {
    	m_toPlay = Opposite(GetToPlay());
    }

	/** Plays a move for the given color.
      	Returns whether or not the move was successfully played. 
      	The state State transition rules differ by concrete games. */
	virtual bool Play(SgBlackWhite color, Move move) = 0;

  	/** Returns whether or not move is legal.
      	A move is legal if it can be played from the current position for the 
      	specified color. Should allow for making moves out-of-turn. */
  	virtual bool Legal(SgBlackWhite color, Move move) = 0;

  	/** Takes back the last played move.
      	Restores the game to the condition it was in before the move was made.
      	Very important to restore the correct side-to-play as searches use this.
      	Returns whether or not the take back was successful. */
  	virtual void TakeBack() {
  		m_board = m_last_board;
  	}

	virtual void Backup() {
		m_last_board = m_board;
	}

  	/** Returns whether or not the game is over. */
  	//virtual bool EndOfGame() const = 0;
  
  	/** Returns whether or not there is a winner. */
  	//virtual bool HasWin() const = 0;

  	/** Evaluate the current position as being good or bad for the current player.
      	Used by search algorithms.  Higher values are better. */
  	//virtual double Evaluate() const = 0;

	/** Print all current board.
		Here we offer a 'template method' like method, traverse all board,
		but not implement by virtual functions. Instead, we use 
		yype State's print */
	void Print(std::ostream& out) const;

  	/** Return the number of rows in the game. */
  	SgGrid GetRows() const {
   		return m_rows;
  	}
  	/** Return the number of columns in the game. */
  	SgGrid GetCols() const {
    	return m_cols;
  	}
  	/** Return the size of the game board as the number of points on the board.
      	Includes border points. */
  	SgPoint GetSize() const {
    	return m_size;
  	}

  	/** Returns the state of the board at the point (row, col).
  		row: 1 to m_row, col: 1 to m_col */
  	State GetState(SgGrid row, SgGrid col) const {
  		assert(row > 0 && row <= m_rows);
  		assert(col > 0 && col <= m_cols);
  		SgPoint p = GetPt(row, col);
  		return GetState(p);
  	}

  	/** Returns the state of the board at point p.
  		Includes color black, white, empty or border, and
  		the piece. */
  	State GetState(SgPoint p) const {
  		assert(p >= 0 && p < m_size);
  		return m_board[p];
  	}

	/** Transfer all grid row and col to points on board. */
	SgPoint GetPt(SgGrid col_id, SgGrid row_id) const {
		assert(col_id >= 0 && col_id < m_cols+2);
		assert(row_id >= 0 && row_id < m_rows+2);
		return row_id * (m_cols+2) + col_id;
	}

protected:
	void SetState(SgPoint p, State s) {
		assert(p < m_size && p >= 0);
		m_board[p] = s;
	}

	/** the board of the game. */
	std::vector<State> m_board;

	/** the board of next step. */
	std::vector<State> m_last_board;

private:
	/** the rows and cols of the board, the actual part. */
	SgGrid m_rows, m_cols;

	/** Actual size of board including border */
	SgPoint m_size;

	/** Number of different types in a grid. Used for Zobrist hasing in future */
	//int m_numPiece;

	SgBlackWhite m_firstPlayer, m_toPlay;

	/** last board, for the tackback of game. */

	/** Utilities */
	/** Compute the board size by cols and rows of inner playing grid. */
	SgPoint ComputeBoardSize(SgGrid in_cols, SgGrid in_rows) {
		return in_rows * in_cols + 2 * (in_rows+1) + 2 * (in_cols+1);
	}

	SgBlackWhite Opposite(SgBlackWhite state) {
		return (SgBlackWhite) (SG_WHITE + SG_BLACK - state);
	}	
};

//----------------------------------------------------------------------------
template<class State, class Move>
SgGame<State, Move>::SgGame(SgGrid rows, SgGrid cols, SgBlackWhite toPlay)
	: m_rows(rows),
	m_cols(cols),
	m_size(ComputeBoardSize(m_rows, m_cols)),
	//m_numPiece(State::GetNumPiece()),
	m_firstPlayer(toPlay),
	m_toPlay(toPlay)
	
{
	m_board = std::vector<State>(m_size, State(SG_BORDER));
	/** The initialization of playing grid is the duty of all concrete games */
}

/** Print, as a so called 'template method'.
	Here we will only do the iteration, the print of each point depends
	depends on each State type. */
template<class State, class Move>
void SgGame<State, Move>::Print(std::ostream& out) const {
	for (SgGrid n=0; n<m_rows+2; n++) {
		for (SgGrid m=0; m<m_cols+2; m++) {
			out << m_board[GetPt(m, n)].str() << "\t";
		}
		out << std::endl;
	}
}


//----------------------------------------------------------------------------
#endif // GAME_H