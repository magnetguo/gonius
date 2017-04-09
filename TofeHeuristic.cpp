//---------------------------------------------------------------------------------------------
#include "TofeHeuristic.h"
#include <map>
#include <cmath>
#include <utility>
//---------------------------------------------------------------------------------------------
int reverseCalc(const TofeGame& g, TofeMove::Movement m) {
	int m_int = static_cast<int>(m);
	SgGrid cols = g.getCols(), rows = g.getRows();
	SgPoint outer_end = (m_int < 2) ? cols : rows;
	SgPoint inner_start = (m_int % 2 == 1) ? ((m_int < 2) ? rows : cols) : 1;
	SgPoint inner_end = (m_int % 2 == 1) ? 1 : ((m_int < 2) ? rows : cols);
	int change = (m_int % 2 == 1) ? -1 : 1;

	int reverse_num = 0;
	std::map<int,int> mp_statics;
	for (SgGrid m = 1; m <= outer_end; m++) {
		for (SgGrid n = inner_start; n != inner_end + change; n += change) {
			SgPoint p = (m_int < 2) ? g.getPt(m, n) : g.getPt(n, m);
			// update num_p
			if (mp_statics.find(g.getState(p).getValue()) != mp_statics.end())
				mp_statics.insert(std::make_pair(g.getState(p).getValue(), 1));
			else
				mp_statics[g.getState(p).getValue()]++;

			// update reverse number
			for (auto it = mp_statics.upper_bound(g.getState(p).getValue());
				it != mp_statics.end(); it = mp_statics.upper_bound(it->first))
				reverse_num += it->second;
		}
		mp_statics.clear();
	}
	return reverse_num;
}

int reverseNum(const TofeGame& g) {
	int row_reverse =
		(reverseCalc(g, TofeMove::TOFE_LEFT) > reverseCalc(g, TofeMove::TOFE_RIGHT))
		? reverseCalc(g, TofeMove::TOFE_RIGHT) : reverseCalc(g, TofeMove::TOFE_LEFT);
	int col_reverse =
		(reverseCalc(g, TofeMove::TOFE_UP) > reverseCalc(g, TofeMove::TOFE_DOWN))
		? reverseCalc(g, TofeMove::TOFE_DOWN) : reverseCalc(g, TofeMove::TOFE_UP);
	return row_reverse + col_reverse;
}

/** Return the all reverses of current board at one direction.
Used by heuristic functions to evaluate board.*/
int getReverseSum(const TofeGame& g, bool isCol) {
	if (isCol) return (g.getCols() * (g.getRows()*g.getRows() - g.getRows()) / 2);
	else return (g.getRows() * (g.getCols()*g.getCols() - g.getCols()) / 2);
}

double reverseScore(const TofeGame& g) {
	double reverse_sum = getReverseSum(g, true) + getReverseSum(g, false);
	return ((reverse_sum - (double)reverseNum(g)) / reverse_sum);
}

//----------------------------------------------------------------------------

double emptyScore(const TofeGame& g) {
	return (double)g.getEmptyNum() / (double)g.getGameSize();
}

//----------------------------------------------------------------------------

/** v1 and v2 are guaranteed as power of 2. */
int diffLevel(int v1, int v2) {
	if (v1 == v2) return 0;
	else {
		int v = v1 + v2;
		int diff = 0;
		bool begin = false;
		while (v != 0) {
			if (begin)
				diff++;
			if (v % 2 == 1)
				begin = true;
			v >>= 1;
		}
		return diff;
	}
}

int diffSum(const TofeGame& g) {
	SgGrid cols = g.getCols(), rows = g.getRows();
	int sum_row = 0, sum_col = 0;
	for (SgGrid it_row = 1; it_row <= rows; it_row++) {
		for (SgGrid it_col = 1; it_col <= cols-1; it_col++) {
			SgPoint c_p = g.getPt(it_col, it_row), n_p = g.getPt(it_col + 1, it_row);
			sum_row += diffLevel(g.getState(c_p).getValue(), g.getState(n_p).getValue());
		}
	}
	for (SgGrid it_col = 1; it_col <= cols; it_col++) {
		for (SgGrid it_row = 1; it_row <= rows - 1; it_row++) {
			SgPoint c_p = g.getPt(it_col, it_row), n_p = g.getPt(it_col, it_row + 1);
			sum_col += diffLevel(g.getState(c_p).getValue(), g.getState(n_p).getValue());
		}
	}
	return sum_row + sum_col;
}

double diffScore(const TofeGame& g) {
	int cols = g.getCols(), rows = g.getRows();
	int num_diff = cols * (rows - 1) + rows * (cols - 1);
	double max_diff = num_diff * log(g.getMaxBlock());
	return (max_diff - (double)diffSum(g)) / max_diff;
}