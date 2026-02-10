#include "simulate/step5-integration.h"

void simulate::Step5Integration::determine_tube_pour_node(
	nst::State& state
)
{



}

void simulate::Step5Integration::assign_tank_to_nodes_from_tubes(
	nst::State& state
)
{
	for(const auto& tube: state.tubes)
	{





}

void simulate::Step5Integration::determine_direction_tube_flow_in_node(
	nst::State& state
)
{
	const int n_nodes = state.nodes;;
	for(int i = 0; i < n_nodes; ++ i)
	{
		auto& node = state.nodes[i];

		const auto& connections_v = nodes.reference.connections_tube_id_v[i];
		const int n_connections = connections_v.size();

		std::vector<bool> is_flow_out_v(n_connections);

		for(int j = 0; j < n_connections; ++ j)
		{
			const int tube_id = connections_v[j];
			const auto& tube = state.tubes[tube_id];

			const bool direction = tube.correct_direction(i);
			const bool flow_negative = (tube.calculated.flow_rate < 0);

			is_flow_out_v[j] = (direction ^ flow_negative);
		}

		node.reference.is_flow_out_of_node_into_tube_v = is_flow_out_v;
	}
}


void simulate::Step5Integration::assign_tank_to_open_node(
	nst::State& state
)
{

}

void simulate::Step5Integration::measure_volume_and_type_fluid_flow_into_system(
	nst::State& state
)
{

}

void simulate::Step5Integration::empty_tanks_to_tubes(
	nst::State& state
)
{

}

void simulate::Step5Integration::recombine_meniscus_in_tubes(
	nst::State& state
)
{

}

static void simulate::Step5Integration::integrate(nst::State& state)
{
	determine_tube_pour_node(state);
	assign_tank_to_nodes_from_tubes(state);

	determine_direction_tube_flow_in_node(state);

	assign_tank_to_open_node(state);
	measure_volume_and_type_fluid_flow_into_system(state);
	empty_tanks_to_tubes(state);
	recombine_meniscus_in_tubes(state);
}
