#include "program/debug-flow.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::DebugFlow::generate_parameter()  // Renamed from generate_property
{
	dst::Parameter parameter;

	// Set simulation type using the flags
	parameter.simulation.is_flow_as_opposed_to_test = true;  // false = test simulation
	parameter.simulation.is_flow_const_flow_rate = true;     // false = constant pressure
	parameter.simulation.is_const_porosity = true;           // variable porosity
	parameter.simulation.id_fluid_inject = 1;
	//parameter.simulation.inlet_pressure = 1000;
	parameter.simulation.is_initially_filled = true;
	parameter.simulation.n_periods_of_initial_disturbance = 0.5;

	// Geometry
	parameter.geometry.n_tube_rows = 50;
	parameter.geometry.n_tube_cols = 100;
	parameter.geometry.radius_contrast = 0.1;
	parameter.geometry.length_scale = 10.0;
	parameter.geometry.is_random_radius = true;
	//parameter.geometry.n_periods = 3;
	//parameter.geometry.is_skewed = true;
	//parameter.geometry.n_inject_boundaries = -1;  // Will be set during initialization

	// Physical constants
	parameter.constant_physical.sigma = 1e4;
	parameter.constant_physical.viscosity_water = 1.0;  // viscosity_ratio = 1.0, mu_scale = 1.0
	parameter.constant_physical.viscosity_oil = 1.0;

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.01;
	parameter.plot.volume_max_to_inject = 0.001;

	return parameter;
}

output::Property program::DebugFlow::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::DebugFlow::run()
{
	std::vector<double> n_initial_disturbance_v{0.5, 1.5, 2.5, 3.5, 5.5, 7.5, 9.5};

	
	output::Result output_result;

	for(auto n_initial_disturbance :n_initial_disturbance_v)
	{
		// Generate base parameter
		auto parameter = generate_parameter();
		
		// Override with loop values
		parameter.simulation.n_periods_of_initial_disturbance = n_initial_disturbance;
		
		// Run simulation
		auto system = simulate::Menu::run(parameter);
		
		// Add to results
		output_result.add(system, generate_visual_property());
	}
}
