#include "simulate/accuracy.h"


double simulate::Accuracy::total_delta(
	const dst::System& system
)
{
	// Using initial_fluid from Measured class
	const double vol_initial = system.measured.initial_fluid.volume_total();
	
	// Using fluid_added/evacuated from State::Measured
	const double volume_total_injected = system.state.measured.fluid_added.volume_total();
	const double volume_total_evacuated = system.state.measured.fluid_evacuated.volume_total();
	
	// Using fluid_in_system from State::Calculated
	const double volume_current = system.state.calculated.fluid_in_system.volume_total();
	
	// Mass balance: initial + injected = current + evacuated
	// Therefore: (initial + injected) - (current + evacuated) should be near zero
	return std::abs((vol_initial + volume_total_injected) - (volume_current + volume_total_evacuated)) / vol_initial;
}

double simulate::Accuracy::water_delta(
	const dst::System& system
)
{
	const double vol_initial_total = system.measured.initial_fluid.volume_total();

	const double water_initial = system.measured.initial_fluid.volume_water();
	const double water_current = system.state.calculated.fluid_in_system.volume_water();
	const double water_injected = system.state.measured.fluid_added.volume_water();
	const double water_evacuated = system.state.measured.fluid_evacuated.volume_water();

	return std::abs((water_injected + water_initial) - (water_evacuated + water_current)) / vol_initial_total;
}

double simulate::Accuracy::oil_delta(
	const dst::System& system
)
{
	const double vol_initial_total = system.measured.initial_fluid.volume_total();

	const double oil_initial = system.measured.initial_fluid.volume_oil();
	const double oil_current = system.state.calculated.fluid_in_system.volume_oil();
	const double oil_injected = system.state.measured.fluid_added.volume_oil();
	const double oil_evacuated = system.state.measured.fluid_evacuated.volume_oil();

	return std::abs((oil_injected + oil_initial) - (oil_evacuated + oil_current)) / vol_initial_total;
}
