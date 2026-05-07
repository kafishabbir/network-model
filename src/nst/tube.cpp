#include "nst/tube.h"

double nst::Tube::area() const
{
	return std::acos(-1) * std::pow(radius, 2);
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

std::pair<int, std::vector<double>> nst::Tube::tube_simple_reversed(
	std::pair<int, std::vector<double>> tube
)
{
	tube.first = (tube.first + tube.second.size()) % 2;
	for(auto& x: tube.second)
	{
		x = 1.0 - x;
	}
	
	std::reverse(tube.second.begin(), tube.second.end());
	return tube;
}

std::pair<int, std::vector<double>> nst::Tube::tube_simple() const
{
	return {id_fluid_first, mpos};
}

std::pair<int, std::vector<double>> nst::Tube::tube_simple_reversed() const
{
	return tube_simple_reversed(tube_simple());
}

std::pair<int, std::vector<double>> nst::Tube::return_simple_tube_from_orientation(const bool direction_forward) const 
{
	if(direction_forward)
	{
		return tube_simple();
	}
	
	return tube_simple_reversed();	
}



