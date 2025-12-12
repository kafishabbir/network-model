#include "nst/tube.h"


std::vector<double> nst::Tube::mpos_long() const
{
	std::vector<double> v{0};
	v.insert(v.end(), mpos.cbegin(), mpos.cend());
	v.push_back(1.0);
	return v;
}
