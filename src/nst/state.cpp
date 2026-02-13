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


nst::State::State():
	physical_constant(),
	simulation_constant(),
	nodes(),
	tubes(),
	calculated()
{}


nst::State::PhysicalConstant::PhysicalConstant():
	sigma(1),
	fluid_v(decl::n_fluids)
{}

nst::State::SimulationConstant::SimulationConstant():
	time_step_resolution(0.1)
{}

nst::State::Calculated::Calculated():
	id_step(-1),
	time_step(-1),
	time_elapsed(0),
	fluid_added(),
	fluid_evacuated(),
	total_fluid_added(),
	total_fluid_evacuated()
{}
