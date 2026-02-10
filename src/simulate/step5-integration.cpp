#include "simulate/step5-integration.h"


void simulate::Step5Integration::assign_displacement_values_to_tubes(
	nst::State& state
)
{
	const double time_step = state.calculated.time_step;
	for(auto& tube: state.tubes)
	{
		tube.calculated.length_displacement = time_step * std::abs(tube.calculated.velocity);
		tube.calculated.length_unit_less_displacement = tube.calculated.length_displacement / tube.length;
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
	for(auto& node: state.nodes)
	{
		const auto& connections_v = nodes.reference.connections_tube_id_v;
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


void simulate::Step5Integration::assign_total_outflow_from_node(
	nst::State& state
)
{
	for(auto& node: state.nodes)
	{
		const auto& connections_v = nodes.reference.connections_tube_id_v;
		const auto& is_flow_out_v = nodes.reference.is_flow_out_v;

		const int n_connections = connections_v.size();
		double volume_flowout = 0;
		for(int j = 0; j < n_connections; ++ j)
		{
			const int tube_id = connections_v[j];
			const bool is_flow_out = is_flow_out_v[j];
			if(is_flow_out)
			{
				const auto& tube = state.tubes[tube_id];
				volume_flowout += tube.calculated.volume_displacement;
			}
		}

		node.calculated.volume_fluid_out = volume_flowout;
	}
}


void simulate::Step5Integration::assign_tank_to_open_node_and_state_volume_in_out(
	nst::State& state
)
{
	nst::Tank evacuation_tank;
	nst::Tank addition_tank;

	for(auto& node: state.nodes)
	{
		const double flow_in_total = node.calculated.tank.total();
		const double flow_out_total = node.calculated.volume_fluid_out;
		const double delta_volume = std::abs(flow_in_total - flow_out_total);
		auto& tank_node = node.calculated.tank;
		if(flow_in_total < flow_out_total)
		{
			// add
			const int fluid_id = node.fluid_to_input;
			tank_node.add_fluid(delta_volume, fluid_id);
			addition_tank.add_fluid(delta_volume, fluid_id);
		}
		else
		{
			//evacualate
			const auto& sliced_tank = tank_node.return_sliced(delta_volume);
			evacuation_tank.fill_from_another_tank(sliced_tank);
		}
	}

	state.calculated.fluid_added = addition_tank;
	state.calculated.fluid_evacuated = evacuation_tank;

	state.calculated.total_fluid_evacuated.fill_from_another_tank(addition_tank);
	state.calculated.total_fluid_added.fill_from_another_tank(evacuation_tank)
}


void simulate::Step5Integration::empty_tanks_to_tubes(
	nst::State& state
)
{
	for(const auto& node: state.nodes)
	{
		const auto& connections_v = nodes.reference.connections_tube_id_v;
		const auto& is_flow_out_v = nodes.reference.is_flow_out_v;
		auto& tank = node.calculated.tank;

		const int n_connections = connections_v.size();
		std::vector<int> tube_id_flow_out_v;
		for(int j = 0; j < n_connections; ++ j)
		{
			const int tube_id = connections_v[j];
			const bool is_flow_out = is_flow_out_v[j];
			if(!is_flow_out)
			{
				continue;
			}
			tube_id_flow_out_v.push_back(tube_id);
		}

		if(tank.is_single_fluid())
		{
			const int fluid_id = tank.id_single_fluid();
			for(const int x: tube_id_flow_out_v)
			{
				auto& tube = state.tubes[x];
				nst::Tank tank_temp;
				const double vol = tube.calculated.volume_displacement;
				tank_temp.add_fluid(fluid_id, vol);
				tube.calculated.add_tank = tank_temp;
			}
			continue;
		}
		std::vector<std::pair<double, int>> pair_radius_id_v;
		for(const int x: tube_id_flow_out_v)
		{
			const double radius = state.tubes[x].radius;
			pair_radius_id_v.push_back({radius, x}};
		}

		std::sort(pair_radius_id_v.begin(), pair_radius_id_v.end());
		for(const auto& [radius, tube_id]: pair_radius_id_v)
		{

	}
}


void simulate::Step5Integration::recombine_meniscus_in_tubes(
	nst::State& state
)
{

}


static void simulate::Step5Integration::integrate(nst::State& state)
{
	assign_displacement_values_to_tubes(state);

	assign_empty_tank_to_all_nodes(state);
	determine_tube_pour_node(state);
	determine_tube_pour_fluids(state);
	pour_from_tubes_to_node_tanks(state);

	determine_direction_tube_flow_in_node(state);
	assign_total_outflow_from_node(state);

	assign_tank_to_open_node_and_state_volume_in_out(state);

	empty_tanks_to_tubes(state);
	recombine_meniscus_in_tubes(state);
}
