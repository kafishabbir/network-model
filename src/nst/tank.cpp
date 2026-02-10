#include "nst/tank.h"

nst::Tank::Tank():
	fluid_v(std::vector<Fluid>(2))
{}

void nst::Tank::add_fluid(const int fluid_id, const double volume)
{
	auto& fluid = fluid_v[fluid_id];
	fluid.volume += volume;
	fluid.used = true;
}
