#include "utility/str.h"
#include <iomanip>
#include <sstream>

std::string utility::Str::general(const double value)
{
	std::stringstream ss;
	ss << std::setprecision(3) << value;
	return ss.str();
}

std::string utility::Str::scientific(const double value)
{
	std::stringstream ss;
	ss << "\\num{";
	ss << std::setprecision(3) << value;
	ss << "}";
	return ss.str();
}

std::string utility::Str::compressed(const double value)
{
	std::stringstream ss;
	ss << "\\num{";
	ss << std::setprecision(2) << std::fixed << value;
	ss << "}";
	return ss.str();
}

std::string utility::Str::vector(const std::vector<int>& v)
{
	std::stringstream ss;
	ss << "$\\{";
	
	if(v.empty())
	{
		ss << "null";
	}
	else
	{
		const int n = v.size();
		for(int i = 0; i < n; ++ i)
		{
			if(i > 0)
			{
				ss << ", ";
			}
			ss << v[i];
		}
	}
	ss << "\\}$";
	return ss.str();
}

std::string utility::Str::vector_double(const std::vector<double>& v)
{
	std::stringstream ss;
	ss << "$\\{";
	
	if(v.empty())
	{
		ss << "null";
	}
	else
	{
		const int n = v.size();
		for(int i = 0; i < n; ++ i)
		{
			if(i > 0)
			{
				ss << ", ";
			}
			ss << scientific(v[i]);
		}
	}
	ss << "\\}$";
	return ss.str();
}
