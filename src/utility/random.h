#ifndef UTILITY_RANDOM_H
#define UTILITY_RANDOM_H

#include <random>

namespace utility
{
	class Random
	{
		public:

		static int integer_from_zero_until_n(const int n);
		static double rational_between_zero_and_one();
	};
}

#endif
