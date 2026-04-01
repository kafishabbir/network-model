#include "program/flow-in-periodic-medium.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::FlowInPeriodicMedium::generate_parameter()  // Renamed from generate_property
{
	dst::Parameter parameter;

	// Using periodic_const_volume_injection_const_porosity as the default
	parameter.simulation.is_flow_as_opposed_to_test = true;     // true = flow simulation
	parameter.simulation.is_flow_const_flow_rate = true;        // true = constant volume injection
	parameter.simulation.is_const_porosity = true;              // true = constant porosity
	parameter.simulation.id_fluid_inject = 0;
	parameter.simulation.is_initially_filled = false;
	parameter.simulation.n_periods_of_initial_disturbance = 0.5;
	parameter.simulation.inlet_pressure = 1e6;  // Ignored for constant volume injection

	// Geometry
	parameter.geometry.n_tube_rows = 40;
	parameter.geometry.n_tube_cols = 40;
	parameter.geometry.radius_contrast = 0.2;
	parameter.geometry.length_scale = 5.0;
	parameter.geometry.n_periods = 2;
	parameter.geometry.is_skewed = true;
	parameter.geometry.is_random_radius = false;
	parameter.geometry.n_inject_boundaries = 0;  // Will be set during initialization
	
	
	// Physical constants
//	parameter.constant_physical.sigma = 10.0;
//	parameter.constant_physical.viscosity_water = 1.0;  // viscosity_ratio = 1.0, mu_scale = 1.0
//	parameter.constant_physical.viscosity_oil = 1.0;     // mu_scale / sqrt(viscosity_ratio)

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.1;
	parameter.plot.volume_max_to_inject = 0.505;

	return parameter;
}

output::Property program::FlowInPeriodicMedium::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::FlowInPeriodicMedium::run()
{
	//~ std::vector<int> id_fluid_inject_v{0, 1};
	//~ std::vector<double> sigma_v{0, 10, 1000};
	//~ std::vector<double> radius_contrast_v{0.5};
	//~ std::vector<double> viscosity_ratio_v{10, 1, 0.1};
	
	std::vector<int> id_fluid_inject_v{0};  // Changed from double to int
	std::vector<double> radius_contrast_v{0.1, 0.2, 0.3, 0.4};
	std::vector<double> sigma_v{0, 1e3, 1e5}; //1e6 does not work with 50x50
	std::vector<double> viscosity_ratio_v{1};
	//std::vector<double> n_initial_disturbance_v{1.5, 3.5, 5.5};
	std::vector<double> n_initial_disturbance_v{1};
	
	output::Result output_result;
	
	for(auto n_initial_disturbance :n_initial_disturbance_v)
	{
		for(int id_fluid_inject : id_fluid_inject_v)
		{
			for(auto radius_contrast : radius_contrast_v)
			{
				for(auto sigma : sigma_v)
				{
					for(auto viscosity_ratio : viscosity_ratio_v)
					{
						// Generate base parameter
						auto parameter = generate_parameter();
						
						// Override with loop values
						parameter.simulation.id_fluid_inject = id_fluid_inject;
						parameter.constant_physical.sigma = sigma;
						parameter.geometry.radius_contrast = radius_contrast;
						

						parameter.constant_physical.viscosity_water = 1.0;
						parameter.constant_physical.viscosity_oil = viscosity_ratio;
						parameter.simulation.n_periods_of_initial_disturbance = n_initial_disturbance;
						
						// Run simulation
						auto system = simulate::Menu::run(parameter);
						
						// Add to results
						output_result.add(system, generate_visual_property());
					}
				}
			}
		}
	}
	
}
