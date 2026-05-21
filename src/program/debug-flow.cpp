#include "program/debug-flow.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::DebugFlow::generate_parameter()  // Renamed from generate_property
{
	dst::Parameter parameter;

	// Set simulation type using the flags
	parameter.simulation.is_mode_overlapping_tubes_of_various_radii = false;
	parameter.simulation.is_flow_as_opposed_to_test = false;  // false = test simulation
	parameter.simulation.is_flow_const_flow_rate = false;     // false = constant pressure
	parameter.simulation.is_const_porosity = false;   
	parameter.simulation.is_tubes_divided = false;            // variable porosity
	parameter.simulation.id_fluid_inject = 0;
	parameter.simulation.inlet_pressure = 1000;

	
	// Geometry
	parameter.geometry.n_tube_rows = 2;
	parameter.geometry.n_tube_cols = 2;
	parameter.geometry.radius_contrast = 0.2;
	parameter.geometry.length_scale = 5.0;
	parameter.geometry.is_random_radius = true;
	//parameter.geometry.n_periods = 3;
	//parameter.geometry.is_skewed = true;
	//parameter.geometry.n_inject_boundaries = -1;  // Will be set during initialization

	// Physical constants
	parameter.constant_physical.sigma = 1e2;
	parameter.constant_physical.viscosity_water = 1.0;  // viscosity_ratio = 1.0, mu_scale = 1.0
	parameter.constant_physical.viscosity_oil = 1.0;

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.01;
	parameter.plot.volume_max_to_inject = 0.1;
	parameter.plot.max_time_steps_for_debug = 20;
	
	return parameter;
}

output::Property program::DebugFlow::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.05;
	property.tube_radius_max = 0.15;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::DebugFlow::run()
{
	output::Result output_result;
	auto parameter = generate_parameter();
	auto system = simulate::Menu::run(parameter);
	output_result.add(system, generate_visual_property());
}
