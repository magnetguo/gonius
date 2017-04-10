//----------------------------------------------------------------------------
#include "TofeHeurReverse.h"
#include <map>

int TofeHeurReverse::reverseCalc(TofeMove::Movement m) const {
	int m_int = static_cast<int>(m);
	SgGrid cols = m_to_evaluate_game.getCols(), rows = m_to_evaluate_game.getRows();
	SgPoint outer_end = (m_int < 2) ? cols : rows;
	SgPoint inner_start = (m_int % 2 == 1) ? ((m_int < 2) ? rows : cols) : 1;
	SgPoint inner_end = (m_int % 2 == 1) ? 1 : ((m_int < 2) ? rows : cols);
	int change = (m_int % 2 == 1) ? -1 : 1;

	int reverse_num = 0;
	std::map<int, int> mp_statics;
	for (SgGrid m = 1; m <= outer_end; m++) {
		for (SgGrid n = inner_start; n != inner_end + change; n += change) {
			SgPoint p = (m_int < 2) ? m_to_evaluate_game.getPt(m, n) : m_to_evaluate_game.getPt(n, m);
			// update num_p
			if (mp_statics.find(m_to_evaluate_game.getState(p).getValue()) != mp_statics.end())
				mp_statics.insert(std::make_pair(m_to_evaluate_game.getState(p).getValue(), 1));
			else
				mp_statics[m_to_evaluate_game.getState(p).getValue()]++;

			// update reverse number
			for (auto it = mp_statics.upper_bound(m_to_evaluate_game.getState(p).getValue());
				it != mp_statics.end(); it = mp_statics.upper_bound(it->first))
				reverse_num += it->second;
		}
		mp_statics.clear();
	}
	return reverse_num;
}

int TofeHeurReverse::reverseNum() const {
	int row_reverse =
		(reverseCalc(TofeMove::TOFE_LEFT) > reverseCalc(TofeMove::TOFE_RIGHT))
		? reverseCalc(TofeMove::TOFE_RIGHT) : reverseCalc(TofeMove::TOFE_LEFT);
	int col_reverse =
		(reverseCalc(TofeMove::TOFE_UP) > reverseCalc(TofeMove::TOFE_DOWN))
		? reverseCalc(TofeMove::TOFE_DOWN) : reverseCalc(TofeMove::TOFE_UP);
	return row_reverse + col_reverse;
}

int TofeHeurReverse::getReverseSum(bool isCol) const {
	if (isCol) 
		return (m_to_evaluate_game.getCols() 
		* (m_to_evaluate_game.getRows()*m_to_evaluate_game.getRows() - m_to_evaluate_game.getRows()) / 2);
	else 
		return (m_to_evaluate_game.getRows()
		* (m_to_evaluate_game.getCols()*m_to_evaluate_game.getCols() - m_to_evaluate_game.getCols()) / 2);
}

double TofeHeurReverse::score() const {
	double reverse_sum = getReverseSum(true) + getReverseSum(false);
	return ((reverse_sum - (double)reverseNum()) / reverse_sum);
}