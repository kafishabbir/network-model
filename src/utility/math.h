#ifndef UTILITY_MATH_H
#define UTILITY_MATH_H

#include "global/dst.h"

namespace utility
{
	class Math
	{
		public:
		static std::vector<double> gaussian_elimination(
			global::Matrix set_linear_equaitions
		);
	};
}

#endif
