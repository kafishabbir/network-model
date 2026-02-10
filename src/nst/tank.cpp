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

nst::Tank nst::Tank::return_sliced(const double volume) const
{
	nst::Tank tank = *this;
	auto& water = tank.tank_v[0];
	auto& oil = tank.tank_v[1];

	if(oil.volume > volume)
	{
		oil.volume -= volume;
		return tank;
	}
	oil.has_flowed = false;
	water.volume -= (volume - oil.volume);
	oil.volume = 0;

	return tank;
}



bool nst::Tank::is_single_fluid() const
{
	int sum = 0;
	for(const auto& fluid: fluid_v)
	{
		sum += fluid.has_flowed;
	}

	return (sum == 1);
}

bool nst::Tank::id_single_fluid() const
{
	return fluid_v[1].has_flowed;
}

