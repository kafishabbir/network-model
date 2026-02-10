#include "simulate/step5-integration.h"

void simulate::Step5Integration::assign_empty_tank_to_all_nodes(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		node.calculated.tank = nst::Tank();
	}
}

void simulate::Step5Integration::determine_tube_pour_node(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		const double flow_rate = tube.calculated.flow_rate;
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second ;
		tube.calculated.id_node_pour = ((flow_rate < 0) ? id_node_first : id_node_second);
	}
}

void simulate::Step5Integration::determine_tube_pour_fluids(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.tank_pour_into_node = tube.slice(state.calculated.time_step);
	}
}


void simulate::Step5Integration::pour_from_tubes_to_node_tanks(
	nst::State& state
)
{
	for(const auto& tube: state.tubes)
	{
		const auto& tank_from = tube.calculated.tank_pour_into_node;
		auto& tank_to = state.nodes[tube.calculated.id_node_pour].calculated.tank;
		tank_to.fill_from_another_tank(tank_from);
	}
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
	assign_empty_tank_to_all_nodes(state);
	determine_tube_pour_node(state);
	determine_tube_pour_fluids(state);
	pour_from_tubes_to_node_tanks(state);

	determine_direction_tube_flow_in_node(state);

	assign_tank_to_open_node(state);
	measure_volume_and_type_fluid_flow_into_system(state);
	empty_tanks_to_tubes(state);
	recombine_meniscus_in_tubes(state);
}
