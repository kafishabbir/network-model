#include "nst/tank.h"

nst::Tank::Tank():
	fluid_v(std::vector<FluidFlow>(2))
{}

void nst::Tank::add_fluid(const int fluid_id, const double volume)
{
	auto& fluid = fluid_v[fluid_id];
	fluid.volume += volume;
	fluid.has_flowed = true;
}

void nst::Tank::fill_from_another_tank(const Tank& other)
{
	const int n_tank = other.tank_v.size();
	for(int i = 0; i < n_tank; ++ i)
	{
		const auto& fluid_flow = other.tank_v[i];
		if(fluid_flow.has_flowed)
		{
			add_fluid(fluid_flow.volume, i);
		}
	}
}

void nst::Tank::total() const
{
	double sum = 0;
	for(const auto& fluid: fluid_v)
	{
		sum += fluid.volume;
	}

	return sum;
}

