#include "nst/tube.h"

double nst::Tube::area() const
{
	return std::pow(radius, 2) * length;
}

double nst::Tube::volume() const
{
	return area() * length;
}

std::vector<double> nst::Tube::mpos_long() const
{
	std::vector<double> v{0, 1};
	v.insert(v.begin() + 1, mpos.cbegin(), mpos.cend());
	return v;
}

nst::Tube::Tube():
	id_node_first(-1),
	id_node_second(-1),
	radius(1),
	length(1),
	id_fluid_first(0)
{}


nst::Tube nst::Tube::original() const
{
	return *this;
}

void nst::Tube::reverse()
{
	for(auto& x: mpos)
	{
		x = 1.0 - x;
	}
	id_fluid_first = (id_fluid_first + mpos.size()) % 2;
}

nst::Tube nst::Tube::reversed() const
{
	nst::Tube tube(*this);
	tube.reverse();
	return tube;
}
