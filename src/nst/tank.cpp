#include "nst/tank.h"

nst::Tank::Fluid::Fluid():
	volume(0),
	is_used(false)
{}

nst::Tank::Tank():
	fluid_v(decl::n_fluids)
{}

nst::Tank::Tank(const double volume, const int id_fluid):
Tank()
{
	add_fluid(volume, id_fluid);
}


void nst::Tank::add_fluid(const double volume, const int id_fluid)
{
	if(volume <= 0)
	{
		throw std::invalid_argument("Volume must be positive");
	}
	if(id_fluid < 0 || id_fluid >= decl::n_fluids)
	{
		throw std::runtime_error("Invalid id_fluid");
	}

	auto& fluid = fluid_v[id_fluid];
	fluid.volume += volume;
	fluid.is_used = true;
}

void nst::Tank::add_fluid(const nst::Tank& other)
{
	for(int i = 0; i < decl::n_fluids; ++ i)
	{
		const auto& fluid = other.fluid_v[i];
		if(fluid.is_used)
		{
			add_fluid(fluid.volume, i);
		}
	}
}

double nst::Tank::total_volume() const
{
	double sum = 0;
	for(const auto& fluid: fluid_v)
	{
		if(fluid.is_used)
		{
			sum += fluid.volume;
		}
	}

	return sum;
}

nst::Tank nst::Tank::return_sliced_tank(const double volume) const
{
	if(volume <= 0)
	{
        throw std::invalid_argument("Volume must be positive");
    }
    if(total_volume() < volume)
    {
        throw std::runtime_error("Insufficient volume in tank to slice");
    }

	nst::Tank tank = *this;
	auto& water = tank.fluid_v[0];
	auto& oil = tank.fluid_v[1];

	if(oil.is_used && oil.volume > volume)
	{
		oil.volume -= volume;
		return tank;
	}
	water.volume -= (volume - oil.volume);
	oil.is_used = false;
	oil.volume = 0;

	return tank;
}



bool nst::Tank::is_only_water() const
{
	return (fluid_v[0].is_used == true) && (fluid_v[1].is_used == false);
}

