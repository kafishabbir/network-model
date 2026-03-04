#include "utility/time.h"

utility::Time::Time():
	start(std::chrono::high_resolution_clock::now())
{}



double utility::Time::passed()
{
	auto end = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);
	start = end;
	const double duration_double = duration.count();
	
	return duration_double / 1e6;
}

