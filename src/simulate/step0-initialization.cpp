#include "simulate/step0-initialization.h"

nst::State simulate::Step0Initialization::state_flow_test()
{
	nst::State state;
	auto& fluid_water = state.physical_constant.fluid_v[0];
	auto& fluid_oil = state.physical_constant.fluid_v[1];

	state.physical_constant.sigma = 1;

	fluid_water.viscosity = 1;
	fluid_water.density = 1;
	fluid_oil.viscosity = 1;
	fluid_oil.density = 1;

	state.simulation_constant.time_step_resolution = 0.1;

	const auto& [nodes_a, tubes_a] = ic::GeometryFlow::network_geometry();
	state.nodes = nodes_a;
	state.tubes = tubes_a;

	auto& nodes = state.nodes;
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

	state.tubes[3].radius = 1.25;
	state.tubes[0].length = 4;
	state.tubes[5].radius = 0.85;

	state.tubes[5].fluid_first = 0;
	state.tubes[5].mpos = {0.2};

	return state;
}

nst::State simulate::Step0Initialization::choose_state()
{
	return state_flow_test();
}
