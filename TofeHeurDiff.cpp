//----------------------------------------------------------------------------
#include "TofeHeurDiff.h"

/** v1 and v2 are guaranteed as power of 2. */
int TofeHeurDiff::diffLevel(int v1, int v2) const {
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

int TofeHeurDiff::diffSum() const {
	SgGrid cols = m_to_evaluate_game.getCols(), rows = m_to_evaluate_game.getRows();
	int sum_row = 0, sum_col = 0;
	for (SgGrid it_row = 1; it_row <= rows; it_row++) {
		for (SgGrid it_col = 1; it_col <= cols - 1; it_col++) {
			SgPoint c_p = m_to_evaluate_game.getPt(it_col, it_row), n_p = m_to_evaluate_game.getPt(it_col + 1, it_row);
			sum_row += diffLevel(m_to_evaluate_game.getState(c_p).getValue(), m_to_evaluate_game.getState(n_p).getValue());
		}
	}
	for (SgGrid it_col = 1; it_col <= cols; it_col++) {
		for (SgGrid it_row = 1; it_row <= rows - 1; it_row++) {
			SgPoint c_p = m_to_evaluate_game.getPt(it_col, it_row), n_p = m_to_evaluate_game.getPt(it_col, it_row + 1);
			sum_col += diffLevel(m_to_evaluate_game.getState(c_p).getValue(), m_to_evaluate_game.getState(n_p).getValue());
		}
	}
	return sum_row + sum_col;
}

double TofeHeurDiff::score() const {
	int cols = m_to_evaluate_game.getCols(), rows = m_to_evaluate_game.getRows();
	int num_diff = cols * (rows - 1) + rows * (cols - 1);
	double max_diff = num_diff * log(m_to_evaluate_game.getMaxBlock());
	return (max_diff - (double)diffSum()) / max_diff;
}
