#include "simulate/step0-initialization.h"

const double simulate::Step0Initialization::fluid_water_viscosity = 1;
const double simulate::Step0Initialization::fluid_water_density = 1;
const double simulate::Step0Initialization::fluid_oil_viscosity = 1;
const double simulate::Step0Initialization::fluid_oil_density = 1;
const double simulate::Step0Initialization::sigma = 1;
const double simulate::Step0Initialization::time_step_resolution = 0.1;

void simulate::Step0Initialization::assign_constants(nst::State& state)
{
	nst::Fluid fluid_water;
	fluid_water.viscosity = fluid_water_viscosity;
	fluid_water.density = fluid_water_density;
	nst::Fluid fluid_oil;
	fluid_oil.viscosity = fluid_oil_viscosity;
	fluid_oil.density = fluid_oil_density;

	state.physical_constant.fluid_v = {fluid_water, fluid_oil};
	state.physical_constant.sigma = sigma;
	state.physical_constant.time_step_resolution = time_step_resolution;

}

void simulate::Step0Initialization::assign_base_geometry(nst::State& state)
{
	const auto& [nodes, tubes] = ic::GeometryFlow::network_geometry();
	state.nodes = nodes;
	state.tubes = tubes;
}

void simulate::Step0Initialization::modify_geometry(nst::State& state)
{
	auto& nodes = state.nodes;
	nodes[0].is_open_boundary = true;
	nodes[5].is_open_boundary = true;
	nodes[2].is_open_boundary = true;
	nodes[7].is_open_boundary = true;

	nodes[0].pressure = 10;
	nodes[5].pressure = 10;
	nodes[2].pressure = 1;
	nodes[7].pressure = 1;

	state.tubes[3].radius = 1.25;
	state.tubes[0].length = 4;
	state.tubes[5].radius = 0.85;


	//state.tubes[1].fluid_first = 1;
	//state.tubes[1].mpos = {0.8};

	//state.tubes[2].fluid_first = 1;
	//state.tubes[2].mpos = {0.2};

	state.tubes[5].fluid_first = 0;
	state.tubes[5].mpos = {0.2};

	//state.tubes[6].fluid_first = 1;
	//state.tubes[6].mpos = {0.3, 0.5, 0.7};
}

void simulate::Step0Initialization::assign_reference_geometry(nst::State& state)
{
	const int n_tubes = tubes.size();
	auto& nodes = state.nodes;
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = tubes[i];
		const int id_node_first = tube.id_node_first;
		const int id_node_second = tube.id_node_second;

		nodes[id_node_first].reference.connections_tube_id_v.push_back(i);
		nodes[id_node_second].reference.connections_tube_id_v.push_back(i);
	}
}


nst::State simulate::Step0Initialization::generate_state()
{
	nst::State state;

	assign_constants(state);
	assign_base_geometry(state);
	assign_modify_geometry(state);
	assign_reference_geometry(state);

	return state;
}
