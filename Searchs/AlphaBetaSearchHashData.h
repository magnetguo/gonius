#ifndef ALPHA_BETA_SEARCH_HASH_DATA_H
#define ALPHA_BETA_SEARCH_HASH_DATA_H

#include <algorithm>
//----------------------------------------------------------------------------
/** Hash data used in search. */
template<class Move>
class ABSearchHashData {
public:
	ABSearchHashData();

	ABSearchHashData(int depth, float value, Move best_move,
		bool is_only_upper_bound = false,
		bool is_only_lower_bound = false,
		bool is_exact_value = false);

	~ABSearchHashData() {}

	unsigned int getDepth() const {
		return m_depth;
	}

	double getValue() const {
		return m_value;
	}

	Move getBestMove() const {
		return m_best_move;
	}

	bool isOnlyUpperBound() const {
		return m_is_upper_bound;
	}

	bool isOnlyLowerBound() const {
		return m_is_lower_bound;
	}

	void adjustBounds(double& lower, double& upper);

	bool isBetterThan(const ABSearchHashData& data) const;

	bool isValid() const {
		return m_is_valid;
	}

	bool isExactValue() const {
		return m_is_exact_value;
	}

	void invalidate() {
		m_is_valid = false;
	}

	void ageData() {
		m_depth = 0;
	}

	bool operator==(const ABSearchHashData& other) const;

	bool operator!=(const ABSearchHashData& other) const;

private:
	unsigned int m_depth;
	bool m_is_upper_bound;
	bool m_is_lower_bound;
	bool m_is_valid;
	bool m_is_exact_value;
	double m_value;
	Move m_best_move;
};

//----------------------------------------------------------------------------
template<class Move>
ABSearchHashData<Move>::ABSearchHashData()
	: m_depth(0),
	m_is_upper_bound(false),
	m_is_lower_bound(false),
	m_is_valid(false),
	m_is_exact_value(false),
	m_value(-1),
	m_best_move() {} // all Move type default constructed as NULLMOVE

template<class Move>
ABSearchHashData<Move>::ABSearchHashData(int depth, float value,
	Move best_move,
	bool is_only_upper_bound,
	bool is_only_lower_bound,
	bool is_exact_value)
	: m_depth(depth),
	m_is_upper_bound(is_only_upper_bound),
	m_is_lower_bound(is_only_lower_bound),
	m_is_valid(true),
	m_is_exact_value(is_exact_value),
	m_value(value),
	m_best_move(best_move) {}

template<class Move>
void ABSearchHashData<Move>::adjustBounds(double& lower, double& upper) {
	if (isOnlyUpperBound())
		upper = std::min(upper, getValue());
	else if (isOnlyLowerBound())
		lower = std::max(lower, getValue());
	else {
		// exact value
		lower = getValue();
		upper = getValue();
	}
}

/** Check if this data is better than the other data.
It is better if the depth is deeper.
If the depth is the same, then it is better:
- if the value is exact or
- if both value are lower bound and this value is greater than the other value or
- if both value are upper bound and this value is less than the other value. */
template<class Move>
bool ABSearchHashData<Move>::isBetterThan(const ABSearchHashData<Move>& data) const {
	if (m_depth > data.m_depth)
		return true;
	if (m_depth < data.m_depth)
		return false;
	return (!m_is_upper_bound && !m_is_lower_bound)
		|| (m_is_lower_bound && data.m_is_lower_bound && m_value > data.m_value)
		|| (m_is_upper_bound && data.m_is_upper_bound && m_value < data.m_value);
}

template<class Move>
bool ABSearchHashData<Move>::operator==(const ABSearchHashData<Move>& other) const {
	return m_depth == other.m_depth &&
		m_value == other.m_value &&
		m_best_move == other.m_best_move &&
		m_is_lower_bound == other.m_is_lower_bound &&
		m_is_upper_bound == other.m_is_upper_bound &&
		m_is_valid == other.m_is_valid &&
		m_is_exact_value == other.m_is_exact_value;
}

template<class Move>
bool ABSearchHashData<Move>::operator!=(const ABSearchHashData<Move>& other) const {
	return !(*this == other);
}

#endif // ALPHA_BETA_SEARCH_HASH_DATA_H
