#include "program/flow-in-periodic-medium.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::FlowInPeriodicMedium::generate_parameter()  // Renamed from generate_property
{
	dst::Parameter parameter;

	// Using periodic_const_volume_injection_const_porosity as the default
	parameter.simulation.is_flow_as_opposed_to_test = true;     // true = flow simulation
	parameter.simulation.is_flow_const_flow_rate = true;        // true = constant volume injection
	parameter.simulation.is_const_porosity = false;              // true = constant porosity
	parameter.simulation.id_fluid_inject = 0;
	//parameter.simulation.inlet_pressure = 100;  // Ignored for constant volume injection

	// Geometry
	parameter.geometry.n_tube_rows = 4;
	parameter.geometry.n_tube_cols = 4;
	parameter.geometry.radius_contrast = 0.8;
	parameter.geometry.length_scale = 10.0;
	parameter.geometry.n_periods = 0.5;
	parameter.geometry.shear = true;
	parameter.geometry.n_inject_boundaries = 0;  // Will be set during initialization

	// Physical constants
	parameter.constant_physical.sigma = 10.0;
	parameter.constant_physical.viscosity_water = 1.0;  // viscosity_ratio = 1.0, mu_scale = 1.0
	parameter.constant_physical.viscosity_oil = 1.0;     // mu_scale / sqrt(viscosity_ratio)

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.1;
	parameter.plot.volume_max_to_inject = 0.5;

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
	//~ std::vector<int> id_fluid_inject_v{0, 1};  // Changed from double to int
	//~ std::vector<double> sigma_v{0, 10, 1000};
	//~ std::vector<double> radius_contrast_v{0.5};
	//~ std::vector<double> viscosity_ratio_v{10, 1, 0.1};
	std::vector<int> id_fluid_inject_v{0};  // Changed from double to int
	std::vector<double> sigma_v{1e1};
	std::vector<double> radius_contrast_v{0.8};
	std::vector<double> viscosity_ratio_v{1.0};
	
	output::Result output_result;
	
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
					

					parameter.constant_physical.viscosity_water = viscosity_ratio;
					parameter.constant_physical.viscosity_oil = 1.0;
					
					// Run simulation
					auto system = simulate::Menu::run(parameter);
					
					// Add to results
					output_result.add(system, generate_visual_property());
				}
			}
		}
	}
	
}
