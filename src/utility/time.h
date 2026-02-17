#ifndef UTILITY_TIME_H
#define UTILITY_TIME_H

#include <chrono>
namespace utility
{
    class Time
    {
		std::chrono::time_point<std::chrono::steady_clock> start;

        public:

		Time();
		double passed() const;
    };
}

#endif
