#include "simulate/step2-flow-rate.h"


void simulate::Step2FlowRate::calculate_and_assign_flow_rates_to_tubes(
	State& state
)
{
	for(auto& tube: state.tubes)
	{
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second;
		const auto& node_first = state.nodes[id_node_first];
		const auto& node_second = state.nodes[id_node_second];

		const double p1 = node_first.pressure;
		const double p2 = node_second.pressure;
		const double delta_p = p1 - p2;
		const double a = simulate::Physics::calculate_a(tube, state);
		const double flow_rate = a * delta_p;
		tube.flow_rate = flow_rate;
	}
}
