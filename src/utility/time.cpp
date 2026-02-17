#include "utility/time.h"

utility::Time::Time():
	start(std::chrono::steady_clock::now())
{}



double utility::Time::passed() const
{
	auto end = std::chrono::steady_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
	return duration.count();
}

