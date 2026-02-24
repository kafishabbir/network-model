#ifndef UTILITY_STR_H
#define UTILITY_STR_H

#include <string>
#include <vector>

namespace utility
{
	class Str
	{
		public:

		static std::string general(const double value);
		static std::string scientific(const double value);
		static std::string vector(const std::vector<int>& v);
	};
}

#endif
