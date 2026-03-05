#include "simulate/step0-preparation.h"



std::pair<dst::Nodes, dst::Tubes> simulate::Step0Preparation::choose_network_geometry(
	const dst::Parameter& simulate_property
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
		return ic::GeometryFlow::network_geometry_const_porosity(
			simulate_property.n_tube_rows,
			simulate_property.n_tube_cols,
			simulate_property.id_fluid_inject,
			simulate_property.constant_radius_contrast,
			simulate_property.constant_length_scale,
			simulate_property.n_periods
		);
	}
	if(simulation == Property::TypeSimulation::periodic_const_volume_injection_variable_porosity)
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
	if(simulation == Property::TypeSimulation::periodic_const_volume_injection_const_porosity)
	{
		return ic::GeometryFlow::network_geometry_const_porosity(
			simulate_property.n_tube_rows,
			simulate_property.n_tube_cols,
			simulate_property.id_fluid_inject,
			simulate_property.constant_radius_contrast,
			simulate_property.constant_length_scale,
			simulate_property.n_periods
		);
	}

	throw std::invalid_argument("Unknown case of  simulate_property.type_simulation.");
	return {dst::Nodes(), dst::Tubes()};
}

void simulate::Step0Preparation::choose_network_geometry(
	dst::System& system,
	const dst::Parameter& simulate_property
)
{
	const auto& [nodes, tubes] = choose_network_geometry(simulate_property);
	state.nodes = nodes;
	state.tubes = tubes;
}

void simulate::Step0Preparation::modify_constants(
	dst::System& system,
	const dst::Parameter& simulate_property
)
{
	auto& fluid_water = state.physical_constant.fluid_v[0];
	auto& fluid_oil = state.physical_constant.fluid_v[1];

	state.physical_constant.sigma = simulate_property.constant_sigma;

	fluid_water.viscosity = std::sqrt(simulate_property.constant_mu1_by_mu2) * simulate_property.constant_mu_scale;
	fluid_water.density = 1;

	fluid_oil.viscosity = simulate_property.constant_mu_scale / std::sqrt(simulate_property.constant_mu1_by_mu2);
	fluid_oil.density = 1;

	state.simulation_constant.time_step_resolution = 0.1;

	state.simulation_constant.capture_frequency_in_volume_fraction = simulate_property.capture_frequency_in_volume_fraction;
	state.simulation_constant.volume_max_to_inject = simulate_property.volume_max_to_inject;
	state.simulation_constant.is_const_volume_injection_simple = 
		(
			(simulate_property.type_simulation == Property::TypeSimulation::periodic_const_volume_injection_variable_porosity)
			||
			(simulate_property.type_simulation == Property::TypeSimulation::periodic_const_volume_injection_const_porosity)
		);
		
	
}

void simulate::Step0Preparation::calculate_and_set_lr_min_max(dst::System& system)
{
    // Initialize with first tube values
    double r_min = state.tubes.front().radius;
    double r_max = state.tubes.front().radius;
    double l_min = state.tubes.front().length;
    double l_max = state.tubes.front().length;
    
    double radius_sum = 0.0;
    double length_sum = 0.0;
    
    // Iterate through all tubes to find min, max, and calculate sum for average
    for (const auto& tube : state.tubes)
    {
        // Update radius min/max
        r_min = std::min(r_min, tube.radius);
        r_max = std::max(r_max, tube.radius);
        
        // Update length min/max
        l_min = std::min(l_min, tube.length);
        l_max = std::max(l_max, tube.length);
        
        // Add to sums for averages
        radius_sum += tube.radius;
        length_sum += tube.length;
    }
    
    // Calculate averages
    double tube_count = state.tubes.size();
    double radius_average = radius_sum / tube_count;
    double length_average = length_sum / tube_count;
    
    double radius_ratio = r_min / r_max;
    double length_ratio = l_min / l_max;
    
    // Assign all values to state.reference
    state.reference.radius_min = r_min;
    state.reference.radius_max = r_max;
    state.reference.radius_average = radius_average;
    state.reference.radius_ratio = radius_ratio;
    
    state.reference.length_min = l_min;
    state.reference.length_max = l_max;
    state.reference.length_average = length_average;
    state.reference.length_ratio = length_ratio;
}

void simulate::Step0Preparation::modify_boundary(
	dst::System& system,
	const dst::Parameter& simulate_property
)
{		
	Utility::assign_pressure(
		state,
		simulate_property.inlet_pressure,
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

void simulate::Step0Preparation::assign_str_of_simulate_property_to_state(
	dst::System& system,
	const dst::Parameter& simulate_property
)
{
	state.reference.comment = simulate_property.str();
}


int simulate::Step0Preparation::count_inlet_nodes(
	const dst::System& system
)
{
	int count = 0;
	for(const auto& node: state.nodes)
	{
		if(node.is_open_boundary && node.is_inlet)
		{
			++ count;
		}
	}
	
	return count;	
}
		
void simulate::Step0Preparation::set_other_references(
	dst::System& system,
	const dst::Parameter& simulate_property
)
{		
	state.reference.id_fluid_inject = simulate_property.id_fluid_inject;
	state.reference.viscosity_ratio = simulate_property.constant_mu1_by_mu2;
	state.reference.radius_contrast = simulate_property.constant_radius_contrast;
	state.reference.n_tube_rows = simulate_property.n_tube_rows;
	state.reference.n_tube_cols = simulate_property.n_tube_cols;
	state.reference.n_periods = simulate_property.n_periods;
	state.reference.n_inject_boundaries = count_inlet_nodes(state);
}

nst::State simulate::Step0Preparation::generate_state(const dst::Parameter& simulate_property)
{
	nst::State state;
	
	
	assign_str_of_simulate_property_to_state(state, simulate_property);

	choose_network_geometry(state, simulate_property);

	modify_constants(state, simulate_property);
	
	calculate_and_set_lr_min_max(state);
	set_other_references(state, simulate_property);
	
	modify_boundary(state, simulate_property);

	create_connections_id_tube_v_for_node(state);

	assign_initial_total_fluid_to_state(state);

	return state;
}







