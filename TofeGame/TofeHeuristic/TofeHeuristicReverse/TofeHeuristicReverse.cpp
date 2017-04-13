//----------------------------------------------------------------------------
#include "TofeHeuristicReverse.h"
#include <map>

int TofeHeuristicReverse::reverseCalc(TofeMove::Movement m) const {
	int m_int = static_cast<int>(m);
	SgGrid cols = m_to_evaluate.getCols(), rows = m_to_evaluate.getRows();
	SgPoint outer_end = (m_int < 2) ? cols : rows;
	SgPoint inner_start = (m_int % 2 == 1) ? ((m_int < 2) ? rows : cols) : 1;
	SgPoint inner_end = (m_int % 2 == 1) ? 1 : ((m_int < 2) ? rows : cols);
	int change = (m_int % 2 == 1) ? -1 : 1;

	int reverse_num = 0;
	std::map<int, int> mp_statics;
	for (SgGrid m = 1; m <= outer_end; m++) {
		for (SgGrid n = inner_start; n != inner_end + change; n += change) {
			SgPoint p = (m_int < 2) ? m_to_evaluate.getPt(m, n) : m_to_evaluate.getPt(n, m);
			// update num_p
			if (mp_statics.find(m_to_evaluate.getState(p).getValue()) != mp_statics.end())
				mp_statics.insert(std::make_pair(m_to_evaluate.getState(p).getValue(), 1));
			else
				mp_statics[m_to_evaluate.getState(p).getValue()]++;

			// update reverse number
			for (auto it = mp_statics.upper_bound(m_to_evaluate.getState(p).getValue());
				it != mp_statics.end(); it = mp_statics.upper_bound(it->first))
				reverse_num += it->second;
		}
		mp_statics.clear();
	}
	return reverse_num;
}

int TofeHeuristicReverse::reverseNum() const {
	int row_reverse =
		(reverseCalc(TofeMove::TOFE_LEFT) > reverseCalc(TofeMove::TOFE_RIGHT))
		? reverseCalc(TofeMove::TOFE_RIGHT) : reverseCalc(TofeMove::TOFE_LEFT);
	int col_reverse =
		(reverseCalc(TofeMove::TOFE_UP) > reverseCalc(TofeMove::TOFE_DOWN))
		? reverseCalc(TofeMove::TOFE_DOWN) : reverseCalc(TofeMove::TOFE_UP);
	return row_reverse + col_reverse;
}

int TofeHeuristicReverse::getReverseSum(bool isCol) const {
	if (isCol) 
		return (m_to_evaluate.getCols() 
		* (m_to_evaluate.getRows()*m_to_evaluate.getRows() - m_to_evaluate.getRows()) / 2);
	else 
		return (m_to_evaluate.getRows()
		* (m_to_evaluate.getCols()*m_to_evaluate.getCols() - m_to_evaluate.getCols()) / 2);
}

double TofeHeuristicReverse::score() const {
	double reverse_sum = getReverseSum(true) + getReverseSum(false);
	return (m_to_evaluate.getToPlay() == SG_WHITE) ?
	((reverse_sum - (double)reverseNum()) / reverse_sum)
	: -((reverse_sum - (double)reverseNum()) / reverse_sum);
}