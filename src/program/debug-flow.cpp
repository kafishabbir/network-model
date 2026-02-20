#include "program/debug-flow.h"

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

visualize::Property program::DebugFlow::generate_visual_property()
{
	visualize::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = decl::pi / 2.0;

	// Node visualization properties
	property.draw_node_perimeter = true;

	// Label visibility properties (all set to false by default)
	property.label_id_node = true;
	property.label_node_pressure = true;
	property.label_id_tube = true;
	property.label_tube_radius = true;
	property.label_tube_length = true;
	property.label_tube_flow_rate = true;
	property.label_tube_direction = true;
	property.label_capillary_pressure = true;
	property.label_tube_velocity = true;
	property.label_tube_time = true;
	property.label_node_details = true;
	property.label_tube_details = true;

	return property;
}

void program::DebugFlow::run()
{
	auto states = simulate::Menu::run(generate_property());

	visualize::Menu visualize_menu;
	visualize_menu.flow(states, generate_visual_property());

	io::FileWrite::flow(visualize_menu.out());
}
