#include "simulate/step5-integration.h"


void simulate::Step5Integration::assign_displacement_values_to_tubes(
	nst::State& state
)
{
	const double time_step = state.calculated.time_step;
	for(auto& tube: state.tubes)
	{
		tube.calculated.length_displacement = time_step * std::abs(tube.calculated.velocity);
		tube.calculated.length_displacement_p = tube.calculated.length_displacement / tube.length;
		tube.calculated.volume_displacement = time_step * std::abs(tube.calculated.flow_rate);
	}
}


void simulate::Step5Integration::assign_empty_tank_to_all_nodes(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		node.calculated.tank = nst::Tank();
	}
}

void simulate::Step5Integration::determine_tube_pour_fluids(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.tank_pour_into_node = tube.slice();
	}
}

void simulate::Step5Integration::determine_tube_pour_id_node(
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




void simulate::Step5Integration::pour_from_tubes_to_node_tanks(
	nst::State& state
)
{
	for(const auto& tube: state.tubes)
	{
		const auto& tank_from = tube.calculated.tank_pour_into_node;
		auto& tank_to = state.nodes[tube.calculated.id_node_pour].calculated.tank;
		tank_to.add_fluid(tank_from);
	}
}


void simulate::Step5Integration::determine_direction_tube_flow_in_node(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		const auto& connections_v = nodes.calculated.connections_id_tube_v;
		const int n_connections = connections_v.size();

		std::vector<bool> is_flow_out_v(n_connections);

		for(int j = 0; j < n_connections; ++ j)
		{
			const int id_tube = connections_v[j];
			const auto& tube = state.tubes[id_tube];

			const bool direction = tube.correct_direction(i);
			const bool flow_negative = (tube.calculated.flow_rate < 0);

			is_flow_out_v[j] = (direction ^ flow_negative);
		}

		node.calculated.is_flow_out_id_tube_v = is_flow_out_v;
	}
}


void simulate::Step5Integration::assign_id_tubes_sorted_to_nodes(
	nst::State& state
)
{
	for(const auto& node: state.nodes)
	{
		const auto& connections_v = nodes.calculated.connections_id_tube_v;
		const auto& is_flow_out_v = nodes.reference.is_flow_out_v;

		const int n_connections = connections_v.size();
		std::vector<std::pair<double, int>> pair_radius_id_v;
		for(int j = 0; j < n_connections; ++ j)
		{
			const int id_tube = connections_v[j];
			const bool is_flow_out = is_flow_out_v[j];
			if(!is_flow_out)
			{
				continue;
			}

			const double radius = state.tubes[id_tube].radius;
			pair_radius_id_v.push_back({radius, id_tube}};
		}

		std::sort(pair_radius_id_v.begin(), pair_radius_id_v.end());
		std::vector<int> id_tube_flow_out_sorted_temp_v;
		for(const auto& [radius, id_tube]: pair_radius_id_v)
		{
			id_tube_flow_out_sorted_temp_v.push_back(id_tube);
		}

		node.calculated.id_tube_flow_out_sorted_v = id_tube_flow_out_sorted_temp_v;
	}
}

void simulate::Step5Integration::assign_total_flow_out_from_node(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		const auto& connections_v = nodes.calculated.connections_id_tube_v;
		const auto& is_flow_out_v = nodes.reference.is_flow_out_v;

		double volume_flow_out = 0;
		for(const int id_tube: id_tube_flow_out_sorted_v)
		{
			const auto& tube = state.tubes[id_tube];
			volume_flow_out += tube.calculated.volume_displacement;
		}

		node.calculated.volume_fluid_out = volume_flow_out;
	}
}




void simulate::Step5Integration::assign_tank_to_open_nodes_where_flow_in(
	nst::State& state
)
{
	nst::Tank addition_tank;

	for(auto& node: state.nodes)
	{
		if(!node.is_open_boundary)
		{
			continue;
		}
		auto& node_tank = node.calculated.tank;

		const double flow_in_total = node_tank.total_volume();
		const double flow_out_total = node.calculated.volume_fluid_out;
		const double delta_volume = std::abs(flow_in_total - flow_out_total);

		if(flow_in_total < flow_out_total)
		{
			// add
			const int id_fluid = node.fluid_to_input;
			node_tank.add_fluid(delta_volume, id_fluid);
			addition_tank.add_fluid(delta_volume, id_fluid);
			node.calculated.is_evacuate_fluid = false;
		}
		else
		{
			//evacualate
			node.calculated.is_evacuate_fluid = true;
		}
	}

	state.calculated.fluid_added = addition_tank;
	state.calculated.total_fluid_added.add_fluid(addition_tank);
}


void simulate::Step5Integration::empty_node_tanks_to_tubes(
	nst::State& state
)
{
	for(const auto& node: state.nodes)
	{
		auto& tank = node.calculated.tank;
		const auto& flow_out_id_tube_v = nodes.calculated.id_tube_flow_out_sorted_v;
		unlock_all_tubes(state, flow_out_id_tube_v);
		distrubite_water(state, flow_out_id_tube_v, tank);
		distrubite_oil(state, flow_out_id_tube_v, tank);
	}
}


void simulate::Step5Integration::calculate_total_flow_out(
	nst::State& state
)
{
	nst::Tank evacuation_tank;

	for(auto& node: state.nodes)
	{
		if(!node.is_open_boundary)
		{
			continue;
		}
		if(!node.is_evacuate_fluid)
		{
			continue;
		}

		auto& node_tank = node.calculated.tank;


		evacuation_tank.add_fluid(node_tank);
	}

	state.calculated.fluid_evacuated = evacuation_tank;
	state.calculated.total_fluid_evacuated.add_fluid(evacuation_tank);
}

void simulate::Step5Integration::combine_tubes_with_added_tank(
	nst::State& state
)
{
	for(const auto& tube: state.tubes)
	{
		tube.mpos = join_tank_to_tube(tube, tube.calculated.tank);
	}
}


void simulate::Step5Integration::integrate(nst::State& state)
{
	assign_displacement_values_to_tubes(state); // 1
	assign_empty_tank_to_all_nodes(state); // 2

	determine_tube_pour_fluids(state); // 3
	determine_tube_pour_id_node(state);  // 4
	pour_from_tubes_to_node_tanks(state); // 5

	determine_direction_tube_flow_in_node(state);  // 6
	assign_id_tubes_sorted_to_nodes(state); // 7

	assign_total_flow_out_from_node(state); // 8
	assign_tank_to_open_nodes_where_flow_in(state); // 9

	empty_node_tanks_to_tubes(state); // 10
	calculate_total_flow_out(state); // 11
	combine_tubes_with_added_tank(state); // 12
}
