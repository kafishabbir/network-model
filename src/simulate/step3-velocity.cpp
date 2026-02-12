#include "simulate/step3-velocity.h"

double simulate::Step3Velocity::flow_rate(
	const nst::Tube& tube,
	const nst::State& state
)
{
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];

	const double delta_pressure = node_first.pressure - node_second.pressure;

	const double a = tube.calculated.resistance_coefficient;
	const double b = tube.calculated.capillary_pressure_magnitude;

	return a * (delta_pressure + b);
}

void simulate::Step3Velocity::flow_rate(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.flow_rate = flow_rate(tube, state);
	}
}


void simulate::Step3Velocity::velocity(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.velocity = tube.calculated.flow_rate / tube.area();
	}
}


void simulate::Step3Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(
	nst::State& state
)
{
	flow_rate(state);
	velocity(state);
}
