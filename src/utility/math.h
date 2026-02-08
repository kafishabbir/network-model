#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include "global/dst.h"

namespace utility
{
	class Math
	{
		public:
		static std::vector<double> gaussian_elimination(
			const global::Matrix A,
			const std::vector<double> B
		);
	};
}

#endif
