#include "program/permeability.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::Permeability::generate_parameter()
{
	dst::Parameter parameter;

	// Simulation type
	parameter.simulation.is_flow_as_opposed_to_test = true;
	parameter.simulation.is_flow_const_flow_rate = false;  // Using constant pressure (not constant flow rate)
	parameter.simulation.is_const_porosity = false;        // Variable porosity
	parameter.simulation.id_fluid_inject = 0;
	parameter.simulation.inlet_pressure = 1e6;

	// Geometry
	parameter.geometry.n_tube_rows = 60;
	parameter.geometry.n_tube_cols = 60;
	parameter.geometry.radius_contrast = 0.9;
	parameter.geometry.length_scale = 10.0;
	parameter.geometry.n_periods = 5.5;

	// Physical constants
	parameter.constant_physical.sigma = 10.0;
	parameter.constant_physical.viscosity_water = 1.0;  // mu_scale * mu1_by_mu2
	parameter.constant_physical.viscosity_oil = 1.0;    // mu_scale

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.01;  // Default value

	// Plot parameters
	parameter.plot.volume_max_to_inject = 0.61;
	parameter.plot.capture_frequency_in_volume_fraction = 0.2;

	return parameter;
}



output::Property program::Permeability::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::Permeability::run()
{
	std::vector<int> id_fluid_inject_v{0, 1};  // Changed from double to int
	std::vector<double> sigma_v{10};
	std::vector<double> radius_contrast_v{0.8};
	std::vector<double> viscosity_ratio_v{1};
	std::vector<double> inlet_pressure_v{1e5, 1e6, 1e7};  // Renamed to avoid conflict with parameter member
	
	output::Result output_result;
	
	for(int id_fluid_inject : id_fluid_inject_v)
	{
		for(auto radius_contrast : radius_contrast_v)
		{
			for(auto sigma : sigma_v)
			{
				for(auto viscosity_ratio : viscosity_ratio_v)
				{
					for(auto pressure : inlet_pressure_v)
					{
						// Generate base parameter
						auto parameter = generate_parameter();
						
						// Override with loop values
						parameter.simulation.id_fluid_inject = id_fluid_inject;
						parameter.constant_physical.sigma = sigma;
						parameter.geometry.radius_contrast = radius_contrast;
						
						parameter.constant_physical.viscosity_water = viscosity_ratio;
						parameter.constant_physical.viscosity_oil = 1.0;
						
						parameter.simulation.inlet_pressure = pressure;
						
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
