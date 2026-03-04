#include "step/part03-velocity.h"

double step::Part03Velocity::flow_rate(
	const nst::Tube& tube,
	const dst::System& state
)
{
	const auto& node_first = state.nodes[tube.id_node_first];
	const auto& node_second = state.nodes[tube.id_node_second];

	const double delta_pressure = node_first.calculated.pressure - node_second.calculated.pressure;

	const double resistance = tube.calculated.resistance_coefficient;
	const double capillary_pressure = tube.calculated.capillary_pressure_magnitude;

	return resistance  * (delta_pressure + capillary_pressure);
}

void step::Part03Velocity::flow_rate(
	dst::System& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.flow_rate = flow_rate(tube, state);
	}
}


void step::Part03Velocity::velocity(
	dst::System& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.velocity = tube.calculated.flow_rate / tube.area();
	}
}


void step::Part03Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(
	dst::System& state
)
{
	flow_rate(state);
	velocity(state);
}
