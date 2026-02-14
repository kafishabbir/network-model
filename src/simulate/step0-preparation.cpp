#include "simulate/step0-preparation.h"


void simulate::Step0Preparation::choose_network_geometry(
	nst::State& state
)
{
	const auto& [nodes, tubes] = ic::Menu::network_geometry_flow();
	state.nodes = nodes;
	state.tubes = tubes;
}


void simulate::Step0Preparation::modify_constants(
	nst::State& state
)
{
	auto& fluid_water = state.physical_constant.fluid_v[0];
	auto& fluid_oil = state.physical_constant.fluid_v[1];

	state.physical_constant.sigma = 1;

	fluid_water.viscosity = 1;
	fluid_water.density = 1;
	fluid_oil.viscosity = 1;
	fluid_oil.density = 1;

	state.simulation_constant.time_step_resolution = 0.1;
}

void simulate::Step0Preparation::modify_boundary(
	nst::State& state
)
{
	auto& nodes = state.nodes;
	auto& tubes = state.tubes;

	for(auto& tube: tubes)
	{
		tube.id_fluid_first = 1;
	}

	for(int a = 0; a <= 168; a += 21)
	{
		nodes[a].pressure = 1000;
		nodes[a].is_open_boundary = true;
		nodes[a].id_fluid_inject = 0;

		nodes[a+10].pressure = 0;
		nodes[a+10].is_open_boundary = true;
		nodes[a+10].id_fluid_inject = 1;
	}

	//~ nodes[0].pressure = 10;
	//~ nodes[0].is_open_boundary = true;
	//~ nodes[0].id_fluid_inject = 1;

	//~ nodes[5].pressure = 10;
	//~ nodes[5].is_open_boundary = true;
	//~ nodes[5].id_fluid_inject = 1;

	//~ nodes[2].pressure = 1;
	//~ nodes[2].is_open_boundary = true;
	//~ nodes[2].id_fluid_inject = 1;

	//~ nodes[7].pressure = 1;
	//~ nodes[7].is_open_boundary = true;
	//~ nodes[7].id_fluid_inject = 1;

	//~ tubes[0].length = 4;

	//~ tubes[3].radius = 1.25;

	//~ tubes[5].radius = 0.85;
	//tubes[5].id_fluid_first = 0;
	//tubes[5].mpos = {0.2};
}

void simulate::Step0Preparation::create_connections_id_tube_v_for_node(
	nst::State& state
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


nst::State simulate::Step0Preparation::generate_state()
{
	nst::State state;

	choose_network_geometry(state);

	modify_constants(state);

	modify_boundary(state);

	create_connections_id_tube_v_for_node(state);

	return state;
}


void simulate::Step0Preparation::reset_calculated(nst::State& state)
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
