#include "nst/tube.h"

double nst::Tube::area() const
{
	return decl::pi * std::pow(radius, 2);
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

nst::Tube::Calculated::Calculated():
	resistance_coefficient(-1),
	capillary_pressure_magnitude(-1),
	flow_rate(-1),
	velocity(-1),
	time(-1),
	is_time_min(false),
	length_displacement_p(-1),
	volume_displacement(-1),
	id_node_sink(-1),
	tank_pour_into_node(),
	add_proportion(-1)
{}


nst::Tube::Tube():
	id_node_first(-1),
	id_node_second(-1),
	radius(1),
	length(1),
	id_fluid_first(0),
	calculated()
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
	std::reverse(mpos.begin(), mpos.end());
	id_fluid_first = (id_fluid_first + mpos.size()) % 2;
}

nst::Tube nst::Tube::reversed() const
{
	nst::Tube tube(*this);
	tube.reverse();
	return tube;
}
