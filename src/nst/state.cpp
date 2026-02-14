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
	measured(),
	reference(),
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
	time_step(-1),
	fluid_added(),
	fluid_evacuated(),
	total_fluid_in_system(),
	total_volume_delta(-1),
	water_volume_delta(-1),
	oil_volume_delta(-1)
{}

nst::State::Measured::Measured():
	time_elapsed(0),
	total_fluid_added(),
	total_fluid_evacuated(),
	initial_total_fluid()
{}

nst::State::Reference::Reference():
	id_step(-1),
	comment("comment=null")
{}
