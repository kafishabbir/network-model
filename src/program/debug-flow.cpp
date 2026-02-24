#include "program/debug-flow.h"
#include "output/result.h"

simulate::Property program::DebugFlow::generate_property()
{
	simulate::Property property;

	property.type_simulation = simulate::Property::TypeSimulation::test_simple;
	property.n_tube_rows = 2;
	property.n_tube_cols = 4;
	property.id_fluid_inject = 0;
	property.constant_sigma = 0.0;
	property.constant_radius_contrast = 0.5;
	property.constant_mu1_by_mu2 = 1.0;
	property.constant_mu_scale = 1.0;
	property.constant_length_scale = 10.0;
	property.capture_frequency_in_volume_fraction = 0.1;
	property.volume_max_to_inject = 0.8;
	property.n_periods = 2;
	property.inlet_pressure = 1000;

	return property;
}

output::Property program::DebugFlow::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = decl::pi / 2.0;

	return property;
}

void program::DebugFlow::run()
{
	const auto simulate_property = generate_property();
	auto solution_states = simulate::Menu::run(simulate_property );
	
	output::Result output_result;
	output_result.add(solution_states, simulate_property, generate_visual_property());
}
