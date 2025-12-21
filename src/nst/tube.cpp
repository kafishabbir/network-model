#include "nst/tube.h"


std::vector<double> nst::Tube::mpos_long() const
{
	std::vector<double> v{0};
	v.insert(v.end(), mpos.cbegin(), mpos.cend());
	v.push_back(1.0);
	return v;
}

nst::Tube::Tube():
	id_node_first(-1),
	id_node_second(-1),
	radius(1),
	length(1),
	fluid_first(0)
{}
