#ifndef TIMER_H
#define TIMER_H

#include <chrono>
#include <cassert>
//----------------------------------------------------------------------------
class Timer {
public:
	Timer() : m_time_used(0), m_is_running(false) { }
	
	void start() {
		assert(!m_is_running);
		m_is_running = true;
		m_start_time = std::chrono::steady_clock::now();
	}

	void end() {
		assert(m_is_running);
		m_time_used += std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1, 1000> > >
			(std::chrono::steady_clock::now() - m_start_time);
		m_is_running = false;
	}

	double getDuration() const {
		return m_time_used.count();
	}

private:
	std::chrono::duration<double, std::ratio<1, 1000> > m_time_used;
	std::chrono::steady_clock::time_point m_start_time;
	bool m_is_running;
};


#endif // TIMER_H