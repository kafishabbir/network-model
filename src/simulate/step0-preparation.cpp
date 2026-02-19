#include "simulate/step0-preparation.h"

std::pair<dst::Nodes, dst::Tubes> simulate::Step0Preparation::choose_network_geometry(
	const simulate::Property& simulate_property
)
{
	const auto& simulation = simulate_property.type_simulation;
	if(simulation == Property::TypeSimulation::test_simple)
	{
		return ic::GeometryBase::rectangular(
			simulate_property.n_tube_rows,
			simulate_property.n_tube_cols,
			simulate_property.id_fluid_inject
		);
	}
	if(simulation == Property::TypeSimulation::test_random)
	{
		return ic::GeometryRand::network_geometry();
	}
	if(simulation == Property::TypeSimulation::periodic_const_pressure_variable_porosity)
	{
		return ic::GeometryFlow::network_geometry(
			simulate_property.n_tube_rows,
			simulate_property.n_tube_cols,
			simulate_property.id_fluid_inject,
			simulate_property.constant_radius_contrast,
			simulate_property.constant_length_scale,
			simulate_property.n_periods
		);
	}
	if(simulation == Property::TypeSimulation::periodic_const_pressure_const_porosity)
	{
		std::cout << "This case has not been dealt with yet" << std::endl;
	}
	if(simulation == Property::TypeSimulation::periodic_const_volume_injection_variable_porosity)
	{
		std::cout << "This case has not been dealt with yet" << std::endl;
	}
	if(simulation == Property::TypeSimulation::periodic_const_volume_injection_const_porosity)
	{
		std::cout << "This case has not been dealt with yet" << std::endl;
	}

	throw std::invalid_argument("Unknown case of  simulate_property.type_simulation.");
	return {dst::Nodes(), dst::Tubes()};
}

void simulate::Step0Preparation::choose_network_geometry(
	nst::State& state,
	const simulate::Property& simulate_property
)
{
	const auto& [nodes, tubes] = choose_network_geometry(simulate_property);
	state.nodes = nodes;
	state.tubes = tubes;
}


void simulate::Step0Preparation::modify_constants(
	nst::State& state,
	const simulate::Property& simulate_property
)
{
	auto& fluid_water = state.physical_constant.fluid_v[0];
	auto& fluid_oil = state.physical_constant.fluid_v[1];

	state.physical_constant.sigma = simulate_property.constant_sigma;

	fluid_water.viscosity = simulate_property.constant_mu1_by_mu2 * simulate_property.constant_mu_scale;
	fluid_water.density = 1;

	fluid_oil.viscosity = (1.0 - simulate_property.constant_mu1_by_mu2) * simulate_property.constant_mu_scale;
	fluid_oil.density = 1;

	state.simulation_constant.time_step_resolution = 0.1;

	state.simulation_constant.capture_frequency_in_volume_fraction = simulate_property.capture_frequency_in_volume_fraction;
	state.simulation_constant.volume_max_to_inject = simulate_property.volume_max_to_inject;

}

void simulate::Step0Preparation::modify_boundary(
	nst::State& state,
	const simulate::Property& simulate_property
)
{
	Utility::assign_pressure(
		simulate_property.inlet_pressure,
		0
	);
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


nst::State simulate::Step0Preparation::generate_state(const simulate::Property& simulate_property)
{
	nst::State state;

	choose_network_geometry(state);

	modify_constants(state);

	modify_boundary(state);

	create_connections_id_tube_v_for_node(state);

	state.measured.initial_total_fluid = utility::Measure::total_fluid_in_system(state);

	return state;
}


