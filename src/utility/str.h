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
		static std::string vector_double(const std::vector<double>& v);
		static std::string compressed(const double value);
	};
}

#endif
