#include "simulate/step-preparation.h"


void simulate::StepPreparation::choose_network_geometry(
	nst::State& state
)
{
	const auto& [nodes, tubes] = ic::Menu::network_geometry_flow();
	state.nodes = nodes;
	state.tubes = tubes;
}


void simulate::StepPreparation::modify_constants(
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

void simulate::StepPreparation::modify_boundary(
	nst::State& state
)
{
	auto& nodes = state.nodes;
	auto& tubes = state.tubes;

	nodes[0].is_open_boundary = true;
	nodes[0].fluid_to_input = 0;

	nodes[5].is_open_boundary = true;
	nodes[5].fluid_to_input = 0;

	nodes[2].is_open_boundary = true;
	nodes[2].fluid_to_input = 1;

	nodes[7].is_open_boundary = true;
	nodes[7].fluid_to_input = 1;

	nodes[0].pressure = 10;
	nodes[5].pressure = 10;
	nodes[2].pressure = 1;
	nodes[7].pressure = 1;

	tubes[3].radius = 1.25;
	tubes[0].length = 4;
	tubes[5].radius = 0.85;

	tubes[5].fluid_first = 0;
	tubes[5].mpos = {0.2};
}

void simulate::StepPreparation::create_connections_id_tube_v_for_node(
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

		nodes[id_node_first].calculated.connections_id_tube_v.push_back(i);
		nodes[id_node_second].calculated.connections_id_tube_v.push_back(i);
	}
}


nst::State simulate::StepPreparation::generate_state()
{
	nst::State state;

	choose_network_geometry(state);
	modify_constants(state);
	modify_boundary(state);
	create_connections_id_tube_v_for_node(state);

	return state;
}
