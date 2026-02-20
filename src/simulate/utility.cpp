#include "simulate/utility.h"

void simulate::Utility::assign_pressure(
	nst::State& state,
	const double pressure_left_boundary,
	const double pressure_right_boundary
)
{
	for(auto& node: state.nodes)
	{
		if(node.is_open_boundary)
		{
			if(node.is_inlet)
			{
				node.pressure = pressure_left_boundary;
			}
			else
			{
				node.pressure = pressure_right_boundary;
			}
		}
	}


}

nst::Tank simulate::Utility::tube_inventory(const nst::Tube& tube)
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

nst::Tank simulate::Utility::total_fluid_in_system(const nst::State& state)
{
	nst::Tank tank;
	for(const auto& tube: state.tubes)
	{
		tank.add_fluid(tube_inventory(tube));
	}

	return tank;
}



void simulate::Utility::reset_calculated(nst::State& state)
{
	state.calculated = nst::State::Calculated();
	for(auto& node: state.nodes)
	{
		node.calculated = nst::Node::Calculated();
	}
	for(auto& tube: state.tubes)
	{
		tube.calculated = nst::Tube::Calculated();
	}
}


bool simulate::Utility::decide_if_more_fluid_still_needs_to_be_injected(const nst::State& state)
{
	const double volume_system = state.measured.initial_total_fluid.volume_total();
	const double volume_injected = state.measured.total_fluid_added.volume_total();
	const double frac = state.simulation_constant.volume_max_to_inject;

	return volume_injected <= (volume_system * frac);
}


bool simulate::Utility::decide_if_capture_state_for_plot(nst::State& state)
{
	const double volume_system = state.measured.initial_total_fluid.volume_total();
	const double volume_injected = state.measured.total_fluid_added.volume_total();
	const double frac = volume_injected / volume_system;

	if(frac >= state.simulation_constant.capture_frequency_in_volume_fraction * state.measured.count_captured)
	{
		++ state.measured.count_captured;
		return true;
	}
	return false;
}
