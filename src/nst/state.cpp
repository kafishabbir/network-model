#include "nst/state.h"

double nst::State::fluid_zero_viscosity() const
{
	const auto& fluid = physical_constant.fluid_v[0];
	return fluid.viscosity;
}

double nst::State::fluid_one_viscosity() const
{
	const auto& fluid = physical_constant.fluid_v[1];
	return fluid.viscosity;
}
