#ifndef SIMULATE_PREPARATION_H
#define SIMULATE_PREPARATION_H

namespace simulate
{
	class Preparation
	{
	public:
		static void blank();
	};
}

#endif



bool is_flow_const_flow_rate;
			
			double inlet_pressure; // Ignored by const_q simulations	
		



void simulate::Step0Preparation::modify_boundary(
	dst::System& system,
	const dst::Parameter& parameter
)
{		
	Utility::assign_pressure(
		state,
		parameter.inlet_pressure,
		0
	);
}

void simulate::Step0Preparation::create_connections_id_tube_v_for_node(
	dst::System& system
)
{
	const int n_tubes = state.tubes.size();
	auto& nodes = state.nodes;
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = state.tubes[i];
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second;

		nodes[id_node_first].reference.connections_id_tube_v.push_back(i);
		nodes[id_node_second].reference.connections_id_tube_v.push_back(i);
	}
}

void simulate::Step0Preparation::assign_initial_total_fluid_to_state(
	dst::System& system
)
{
	state.measured.initial_total_fluid = Utility::total_fluid_in_system(state);

}



		


dst::State simulate::Step0Preparation::generate_state(const dst::Parameter& parameter)
{

	modify_boundary(state, parameter);

	create_connections_id_tube_v_for_node(state);

	assign_initial_total_fluid_to_state(state);

	return state;
}

