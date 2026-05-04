#include "step/part03-velocity.h"

double step::Part03Velocity::flow_rate(
	const nst::Tube& tube,
	const dst::System& system
)
{
	const auto& node_first = system.state.nodes[tube.id_node_first];
	const auto& node_second = system.state.nodes[tube.id_node_second];

	const double delta_pressure = node_first.calculated.pressure - node_second.calculated.pressure;

	const double resistance = tube.calculated.resistance_coefficient;
	const double capillary_pressure = tube.calculated.capillary_pressure_magnitude;

	return resistance * (delta_pressure + capillary_pressure);
}

void step::Part03Velocity::flow_rate(
	dst::System& system
)
{
	for(auto& tube: system.state.tubes)
	{
		tube.calculated.flow_rate = flow_rate(tube, system);
	}
}

void step::Part03Velocity::velocity(
	dst::System& system
)
{
	for(auto& tube: system.state.tubes)
	{
		
		double Area = tube.area();
		
		if(system.parameter.simulation.is_tubes_divided)
		{
			const double R_max = system.parameter.geometry_distributions.radius.max;
			Area = std::acos(-1) * std::pow(R_max, 2);
		}
		tube.calculated.velocity = tube.calculated.flow_rate / Area;
	}
}

void step::Part03Velocity::calculate_and_assign_flow_rate_and_velocity_to_tube(
	dst::System& system
)
{
	flow_rate(system);
	velocity(system);
}
