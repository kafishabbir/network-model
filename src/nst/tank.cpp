#include "nst/tank.h"

nst::Tank::Fluid::Fluid():
	volume(0),
	is_used(false)
{}

nst::Tank::Tank():
	fluid_v(decl::n_fluids)
{}

void nst::Tank::add_fluid(const double volume, const int id_fluid)
{
	if(volume < 0)
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

bool nst::Tank::is_only_water() const
{
	return is_contain_water() && (!is_contain_oil());
}

bool nst::Tank::is_contain_oil() const
{
	return fluid_v[1].is_used;
}

bool nst::Tank::is_contain_water() const
{
	return fluid_v[0].is_used;
}

double nst::Tank::volume_water() const
{
	return fluid_v[0].volume;
}

double nst::Tank::volume_oil() const
{
	return fluid_v[1].volume;
}

