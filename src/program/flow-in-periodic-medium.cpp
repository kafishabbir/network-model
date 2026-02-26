#include "program/flow-in-periodic-medium.h"
#include "output/result.h"


simulate::Property program::FlowInPeriodicMedium::generate_property()
{
	simulate::Property property;

	//property.type_simulation = simulate::Property::TypeSimulation::periodic_const_pressure_variable_porosity;
	property.type_simulation = simulate::Property::TypeSimulation::periodic_const_volume_injection_variable_porosity;
	//property.type_simulation = simulate::Property::TypeSimulation::periodic_const_volume_injection_const_porosity;
	property.n_tube_rows = 40;
	property.n_tube_cols = 40;
	property.id_fluid_inject = 0;
	property.constant_sigma = 0.0;
	property.constant_radius_contrast = 0.5;
	property.constant_mu1_by_mu2 = 1.0;
	property.constant_mu_scale = 1.0;
	property.constant_length_scale = 10.0;
	property.capture_frequency_in_volume_fraction = 0.1;
	property.volume_max_to_inject = 0.8;
	property.n_periods = 2;
	property.inlet_pressure = 100;

	return property;
}

output::Property program::FlowInPeriodicMedium::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = decl::pi / 2.0;

	return property;
}

void program::FlowInPeriodicMedium::run()
{
	std::vector<double> sigma_v{0, 10, 1e2, 1e3, 1e4};
	std::vector<double> radius_contrast_v{0.8};
	output::Result output_result;
	for(auto sigma: sigma_v)
	{
		for(auto radius_contrast: radius_contrast_v)
		{
			auto simulate_property = generate_property();
			simulate_property.constant_sigma = sigma;
			simulate_property.constant_radius_contrast = radius_contrast;
			auto solution_states = simulate::Menu::run(simulate_property );
			output_result.add(solution_states, simulate_property, generate_visual_property());
		}
	}
}
