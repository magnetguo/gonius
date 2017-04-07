#include "TofeGame.h"

//----------------------------------------------------------------------------

TofeGame::TofeGame(SgGrid rows, SgGrid cols, SgBlackWhite toPlay)
	: SgGame<TofeState, TofeMove>(rows, cols, SG_WHITE)
{
	/* After the initial of base class,
		We should initialize the first 2 or 4 on a random place */

	/** first we initialize the empty positions 
		We should do the initialization of empty at concrete game,
		as like chess, not all game are initialized as all empty. */
	for (SgGrid it_row=1; it_row<=getRows(); it_row++) {
		for (SgGrid it_col=1; it_col<=getCols(); it_col++) {
			setState(getPt(it_col, it_row), TofeState(SG_EMPTY));
			m_empty.push_back(getPt(it_col, it_row));
		}
	}

	// then we pick 2 random position and put a 2 and 4 on them
	setState(pickOneRandomEmptyPos(), TofeState(SG_WHITE, 2));
	setState(pickOneRandomEmptyPos(), TofeState(SG_WHITE, 4));
}

SgPoint TofeGame::pickOneRandomEmptyPos() {
	assert(!m_empty.empty()); // there should be available point
	std::uniform_int_distribution<int> uni(0, m_empty.size()-1);
	int rand = uni(rd);
	SgPoint pos = m_empty[rand];
	//std::cout << pos << std::endl;
	m_empty.erase(m_empty.begin()+rand);
	return pos;
}

bool TofeGame::toMove(TofeMove::Movement m) {
	int m_int = static_cast<int>(m);
	bool changed = false;
	backup();
	SgGrid cols = this->getCols(), rows = this->getRows();
	SgPoint outer_end = (m_int < 2) ? cols : rows;
	SgPoint inner_start = (m_int % 2 == 1) ? ((m_int < 2) ? rows : cols) : 1;
	SgPoint inner_end = (m_int % 2 == 1) ? 1 : ((m_int < 2) ? rows : cols);
	int change = (m_int % 2 == 1) ? -1 : 1;
	for (SgGrid m=1; m<=outer_end; m++) {
		for (SgGrid n=inner_start; n != inner_end+change; n+=change) {
			SgPoint p = (m_int < 2) ? this->getPt(m, n) : this->getPt(n, m);
			//std::cout << m << n <<std::endl;
			if (this->getState(p).getColor() == SG_EMPTY)
				continue;

			for (SgGrid k=n-change; ; k-=change) {
				//std::cout << k << std::endl;
				SgPoint p2 = (m_int < 2) ? this->getPt(m, k) : this->getPt(k, m);
				if (this->getState(p2).getColor() == SG_EMPTY){
					changed = true;
					continue;
				}
				if (this->getState(p2).getColor() == SG_BORDER) {
					SgPoint nextToBorder = 
					(m_int < 2) ? this->getPt(m, k+change) : this->getPt(k+change, m);
					if (nextToBorder != p) {
						// not next to border
						// if next to border, nothing to do
						this->setState(nextToBorder, this->getState(p));
						this->setState(p, TofeState(SG_EMPTY));
						m_empty.erase(find(m_empty.begin(), m_empty.end(), nextToBorder));
						m_empty.push_back(p);
						changed = true;
					}
					break;
				}
				if (this->getState(p2) == this->getState(p)) {
					//std::cout << "combine happen " << p2 << p << std::endl;
					this->setState(p2, TofeState(SG_WHITE, 2*this->getState(p2).getValue()));
					this->setState(p, TofeState(SG_EMPTY));
					m_empty.push_back(p);
					changed = true;
				} else {
					SgPoint n_k = 
					(m_int < 2) ? this->getPt(m, k+change) : this->getPt(k+change, m);
					if (n_k != p) {
						assert(this->getState(n_k).getColor() == SG_EMPTY);
						this->setState(n_k , this->getState(p));
						m_empty.erase(find(m_empty.begin(), m_empty.end(), n_k));
						this->setState(p, TofeState(SG_EMPTY));
						m_empty.push_back(p);	
					}
				} 
				break;
			}			
		}
	}
	return changed;
}

bool TofeGame::legal(SgBlackWhite color, TofeMove move) {
	/** First, a legal should be at proper turn
		, if not, a fatal error, drop out. */
	// assert(color == SG_BLACK && !move.isMovement());

	// assert(color == SG_WHITE && move.isMovement());

	if (color == SG_BLACK)
		return !m_empty.empty();
	else {
		if (toMove(move.getMovement())) {
			//std::cout << "before takeback" << std::endl;
			//Print(std::cout);
			takeback();
			//std::cout << "after takeback" << std::endl;
			//Print(std::cout);
			return true;
		} else {
			takeback();
			return false;
		}
	}
}

/** The move and state transfer logic of 2048 game */
bool TofeGame::play(SgBlackWhite color, TofeMove move) {
	if (legal(color, move)) {
	//if (true) {
		if (color == SG_BLACK)
			/** We can have a random 2 or 4 in the future */
			setState(move.getPoint(), TofeState(SG_WHITE, move.getValue())); 
		else{
			toMove(move.getMovement());
		}
		this->switchToPlay();
		return true;
	} else
		return false;
}

//----------------------------------------------------------------------------
bool operator==(const TofeState &&lhs, const TofeState &&rhs) {
	return (lhs.getColor() == rhs.getColor() 
			&& lhs.getValue() == rhs.getValue());
}