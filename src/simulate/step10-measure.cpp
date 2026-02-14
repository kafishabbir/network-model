#include "simulate/step10-measure.h"

nst::Tank simulate::Step10Measure::tube_inventory(const nst::Tube& tube)
{
	const auto& v = tube.mpos_long();
	const int n = v.size();
	const double vol = tube.volume();
	nst::Tank tank;
	for(int i = 1; i < n; ++ i)
	{
		const int id_fluid = (tube.id_fluid_first + 1 + i) % 2;
		const double l = v[i] - v[i - 1];
		tank.add_fluid(vol * l, id_fluid);
	}

	return tank;
}

nst::Tank simulate::Step10Measure::total_fluid_in_system(const nst::State& state)
{
	nst::Tank tank;
	for(const auto& tube: state.tubes)
	{
		tank.add_fluid(tube_inventory(tube));
	}

	return tank;
}


double simulate::Step10Measure::total_delta(const nst::State& state)
{
	const double volume_total_injected = state.measured.total_fluid_added.total_volume();
	const double volume_total_evacuated = state.measured.total_fluid_evacuated.total_volume();

	return std::abs(volume_total_injected - volume_total_evacuated) / volume_total_evacuated;
}

double simulate::Step10Measure::water_delta(const nst::State& state)
{
	const double vol = state.measured.initial_total_fluid.total_volume();

	const double water_initial = state.measured.initial_total_fluid.volume_water();
	const double water_current = state.calculated.total_fluid_in_system.volume_water();
	const double water_injected = state.measured.total_fluid_added.volume_water();
	const double water_evacuated = state.measured.total_fluid_evacuated.volume_water();

	return std::abs((water_injected + water_initial) - (water_evacuated + water_current)) / vol;
}

double simulate::Step10Measure::oil_delta(const nst::State& state)
{
	const double vol = state.measured.initial_total_fluid.total_volume();

	const double oil_initial = state.measured.initial_total_fluid.volume_oil();
	const double oil_current = state.calculated.total_fluid_in_system.volume_oil();
	const double oil_injected = state.measured.total_fluid_added.volume_oil();
	const double oil_evacuated = state.measured.total_fluid_evacuated.volume_oil();

	return std::abs((oil_injected + oil_initial) - (oil_evacuated + oil_current)) / vol;
}

void simulate::Step10Measure::measure(nst::State& state)
{
	state.calculated.total_fluid_in_system = total_fluid_in_system(state);
	state.calculated.saturation = state.calculated.total_fluid_in_system.volume_water() / state.calculated.total_fluid_in_system.total_volume();
	state.calculated.total_volume_delta = total_delta(state);
	state.calculated.water_volume_delta = water_delta(state);
	state.calculated.oil_volume_delta = oil_delta(state);
}

