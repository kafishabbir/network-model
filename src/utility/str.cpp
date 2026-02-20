#include "utility/str.h"

std::string utility::Str::d(const double value)
{
	std::stringstream ss;
	ss << std::setprecision(3) << value;
	return ss.str();
}
