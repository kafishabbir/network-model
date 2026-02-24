#include "utility/str.h"
#include <iomanip>

std::string visualize::Draw::num(const double val)
{
	std::stringstream ss;
	ss << "\\num{";
	ss << std::setprecision(3) << val;
	ss << "}";
	return ss.str();
}


std::string utility::Str::d(const double value)
{
	std::stringstream ss;
	ss << std::setprecision(3) << value;
	return ss.str();
}
