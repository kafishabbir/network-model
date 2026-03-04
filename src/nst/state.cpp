#include "nst/state.h"

double nst::State::water_viscosity() const
{
	const auto& fluid = physical_constant.fluid_v[0];
	return fluid.viscosity;
}

double nst::State::oil_viscosity() const
{
	const auto& fluid = physical_constant.fluid_v[1];
	return fluid.viscosity;
}





nst::State::PhysicalConstant::PhysicalConstant():
	sigma(1),
	fluid_v(decl::n_fluids)
{}

nst::State::SimulationConstant::SimulationConstant():
	time_step_resolution(0.1),
	capture_frequency_in_volume_fraction(0.1),
	volume_max_to_inject(0.8)
{}




