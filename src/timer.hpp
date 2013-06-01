#ifndef MMX_TIMER_HPP
#define MMX_TIMER_HPP 1

#include "config.hpp"

#include <chrono>

namespace mmx {

	class timer {
	public:
		MMX_CONSTEXPR timer()
			: _start()
			, _end()
		{
		}

		virtual ~timer() {}

		ulonglong hours() const { return std::chrono::duration_cast<std::chrono::hours>(_end - _start ).count(); }
		ulonglong minutes() const { return std::chrono::duration_cast<std::chrono::minutes>(_end - _start ).count(); }
		ulonglong seconds() const { return std::chrono::duration_cast<std::chrono::seconds>(_end - _start ).count(); }
		ulonglong milli() const { return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start ).count(); }
		ulonglong ms() const { return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start ).count(); }
		ulonglong micro() const { return std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count(); }
		ulonglong us() const { return std::chrono::duration_cast<std::chrono::microseconds>(_end - _start).count(); }
		ulonglong nano() const { return std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start).count(); }
		ulonglong ns() const { return std::chrono::duration_cast<std::chrono::nanoseconds>(_end - _start).count(); }

		//void pause();
		//void resume();
		//void pause_for();

		void start() { _start = std::chrono::high_resolution_clock::now(); }
		timer& stop() {
			_end = std::chrono::high_resolution_clock::now();
			return *this;
		}

	private:
		std::chrono::high_resolution_clock::time_point _start;
		std::chrono::high_resolution_clock::time_point _end;
	};

}           // ~namespace mmx

#endif      // MMX_TIMER_HPP
