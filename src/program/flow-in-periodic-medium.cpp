#include "program/flow-in-periodic-medium.h"
#include "output/result.h"


simulate::Property program::FlowInPeriodicMedium::generate_property()
{
	simulate::Property property;

	//property.type_simulation = simulate::Property::TypeSimulation::periodic_const_pressure_variable_porosity;
	//property.type_simulation = simulate::Property::TypeSimulation::periodic_const_volume_injection_variable_porosity;
	property.type_simulation = simulate::Property::TypeSimulation::periodic_const_volume_injection_const_porosity;
	property.n_tube_rows = 30;
	property.n_tube_cols = 90;
	property.id_fluid_inject = 0;
	property.constant_sigma = 0.0;
	property.constant_radius_contrast = 0.5;
	property.constant_mu1_by_mu2 = 1.0;
	property.constant_mu_scale = 1.0;
	property.constant_length_scale = 10.0;
	property.capture_frequency_in_volume_fraction = 0.2;
	property.volume_max_to_inject = 0.65;
	property.n_periods = 6;
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
	std::vector<double> id_fluid_inject_v{0, 1};
	std::vector<double> sigma_v{0, 10, 1000};
	std::vector<double> radius_contrast_v{0.5};
	std::vector<double> viscosity_ratio_v{10, 1, 0.1};
	output::Result output_result;
	for(int id_fluid_inject: id_fluid_inject_v)
	{
		for(auto radius_contrast: radius_contrast_v)
		{
			for(auto sigma: sigma_v)
			{
				for(auto viscosity_ratio: viscosity_ratio_v)
				{
					auto simulate_property = generate_property();
					simulate_property.id_fluid_inject = id_fluid_inject;
					simulate_property.constant_sigma = sigma;
					simulate_property.constant_radius_contrast = radius_contrast;
					simulate_property.constant_mu1_by_mu2 = viscosity_ratio;
					
					auto solution_states = simulate::Menu::run(simulate_property);
					output_result.add(solution_states, simulate_property, generate_visual_property());
				}
			}
		}
	}
}
