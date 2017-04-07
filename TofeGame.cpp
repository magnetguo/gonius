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
	for (SgGrid n=1; n<=GetRows(); n++) {
		for (SgGrid m=1; m<=GetCols(); m++) {
			SetState(GetPt(m, n), TofeState(SG_EMPTY));
			m_empty.push_back(GetPt(m, n));
		}
	}

	// then we pick 2 random position and put a 2 and 4 on them
	SetState(PickOneRandomEmptyPos(), TofeState(SG_WHITE, 2));
	SetState(PickOneRandomEmptyPos(), TofeState(SG_WHITE, 4));
}

SgPoint TofeGame::PickOneRandomEmptyPos() {
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
	Backup();
	SgGrid cols = this->GetCols(), rows = this->GetRows();
	SgPoint outer_end = (m_int < 2) ? cols : rows;
	SgPoint inner_start = (m_int % 2 == 1) ? ((m_int < 2) ? rows : cols) : 1;
	SgPoint inner_end = (m_int % 2 == 1) ? 1 : ((m_int < 2) ? rows : cols);
	int change = (m_int % 2 == 1) ? -1 : 1;
	for (SgGrid m=1; m<=outer_end; m++) {
		for (SgGrid n=inner_start; n != inner_end+change; n+=change) {
			SgPoint p = (m_int < 2) ? this->GetPt(m, n) : this->GetPt(n, m);
			//std::cout << m << n <<std::endl;
			if (this->GetState(p).GetColor() == SG_EMPTY)
				continue;

			for (SgGrid k=n-change; ; k-=change) {
				//std::cout << k << std::endl;
				SgPoint p2 = (m_int < 2) ? this->GetPt(m, k) : this->GetPt(k, m);
				if (this->GetState(p2).GetColor() == SG_EMPTY){
					changed = true;
					continue;
				}
				if (this->GetState(p2).GetColor() == SG_BORDER) {
					SgPoint nextToBorder = 
					(m_int < 2) ? this->GetPt(m, k+change) : this->GetPt(k+change, m);
					if (nextToBorder != p) {
						// not next to border
						// if next to border, nothing to do
						this->SetState(nextToBorder, this->GetState(p));
						this->SetState(p, TofeState(SG_EMPTY));
						m_empty.erase(find(m_empty.begin(), m_empty.end(), nextToBorder));
						m_empty.push_back(p);
						changed = true;
					}
					break;
				}
				if (this->GetState(p2) == this->GetState(p)) {
					//std::cout << "combine happen " << p2 << p << std::endl;
					this->SetState(p2, TofeState(SG_WHITE, 2*this->GetState(p2).GetValue()));
					this->SetState(p, TofeState(SG_EMPTY));
					m_empty.push_back(p);
					changed = true;
				} else {
					SgPoint n_k = 
					(m_int < 2) ? this->GetPt(m, k+change) : this->GetPt(k+change, m);
					if (n_k != p) {
						assert(this->GetState(n_k).GetColor() == SG_EMPTY);
						this->SetState(n_k , this->GetState(p));
						m_empty.erase(find(m_empty.begin(), m_empty.end(), n_k));
						this->SetState(p, TofeState(SG_EMPTY));
						m_empty.push_back(p);	
					}
				} 
				break;
			}			
		}
	}
	return changed;
}

bool TofeGame::Legal(SgBlackWhite color, TofeMove move) {
	/** First, a legal should be at proper turn
		, if not, a fatal error, drop out. */
	// assert(color == SG_BLACK && !move.isMovement());

	// assert(color == SG_WHITE && move.isMovement());

	if (color == SG_BLACK)
		return !m_empty.empty();
	else {
		if (toMove(move.GetMovement())) {
			//std::cout << "before takeback" << std::endl;
			//Print(std::cout);
			TakeBack();
			//std::cout << "after takeback" << std::endl;
			//Print(std::cout);
			return true;
		}
		return false;
	}
}

/** The move and state transfer logic of 2048 game */
bool TofeGame::Play(SgBlackWhite color, TofeMove move) {
	if (Legal(color, move)) {
	//if (true) {
		if (color == SG_BLACK)
			/** We can have a random 2 or 4 in the future */
			SetState(move.GetPoint(), TofeState(SG_WHITE, move.GetValue())); 
		else{
			toMove(move.GetMovement());
		}
		this->SwitchToPlay();
		return true;
	} else
		return false;
}

//----------------------------------------------------------------------------
bool operator==(const TofeState &&lhs, const TofeState &&rhs) {
	return (lhs.GetColor() == rhs.GetColor() 
			&& lhs.GetValue() == rhs.GetValue());
}