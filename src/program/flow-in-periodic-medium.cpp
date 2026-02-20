#include "program/flow-in-periodic-medium.h"




simulate::Property program::FlowInPeriodicMedium::generate_property()
{
	simulate::Property property;

	property.type_simulation = simulate::Property::TypeSimulation::periodic_const_pressure_variable_porosity;
	property.n_tube_rows = 10;
	property.n_tube_cols = 10;
	property.id_fluid_inject = 0;
	property.constant_sigma = 0.0;
	property.constant_radius_contrast = 0.5;
	property.constant_mu1_by_mu2 = 1.0;
	property.constant_mu_scale = 1.0;
	property.constant_length_scale = 10.0;
	property.capture_frequency_in_volume_fraction = 0.1;
	property.volume_max_to_inject = 0.4;
	property.n_periods = 2;
	property.inlet_pressure = 100;

	return property;
}

visualize::Property program::FlowInPeriodicMedium::generate_visual_property()
{
	visualize::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = decl::pi / 2.0;

	// Node visualization properties
	property.draw_node_perimeter = true;

	// Label visibility properties (all set to false by default)
	property.label_id_node = false;
	property.label_node_pressure = false;
	property.label_id_tube = false;
	property.label_tube_radius = false;
	property.label_tube_length = false;
	property.label_tube_flow_rate = false;
	property.label_tube_direction = false;
	property.label_capillary_pressure = false;
	property.label_tube_velocity = false;
	property.label_tube_time = false;
	property.label_node_details = false;
	property.label_tube_details = false;

	return property;
}

void program::FlowInPeriodicMedium::run()
{
	auto states = simulate::Menu::run(generate_property());

	visualize::Menu visualize_menu;
	visualize_menu.flow(states, generate_visual_property());

	io::FileWrite::flow(visualize_menu.out());
}
