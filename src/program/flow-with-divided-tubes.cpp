#include "program/flow-with-divided-tubes.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::FlowWithDividedTubes::generate_parameter()
{
	dst::Parameter parameter;

	parameter.simulation.is_mode_overlapping_tubes_of_various_radii = false;
	parameter.simulation.is_flow_as_opposed_to_test = true;     // true = flow simulation
	parameter.simulation.is_flow_const_flow_rate = true;        // true = constant volume injection
	parameter.simulation.is_const_porosity = false;              // true = constant porosity
	parameter.simulation.is_tubes_divided = true;
	parameter.simulation.run_iterative = false;
	parameter.simulation.flow_rate_in_pore_volumes = 0.1;
	parameter.simulation.id_fluid_inject = 0;
	parameter.simulation.is_initially_filled = false;
	parameter.simulation.n_periods_of_initial_disturbance = 0.5;
	parameter.simulation.real_geometry = true;
	parameter.simulation.inlet_pressure = -1;  // Ignored for constant volume injection
	parameter.simulation.is_biscuit = true;
	
	// Geometry
	parameter.geometry.n_tube_rows = 20;
	parameter.geometry.n_tube_cols = 60;
	parameter.geometry.radius_contrast = 0.999;
	parameter.geometry.length_scale = 5.0;
	parameter.geometry.n_periods = 6;
	parameter.geometry.is_skewed = false;
	parameter.geometry.is_random_radius = false;
	parameter.geometry.n_inject_boundaries = 0;  // Will be set during initialization
	
	// Physical constants
//	parameter.constant_physical.sigma = 10.0;
//	parameter.constant_physical.viscosity_water = 1.0;  // viscosity_ratio = 1.0, mu_scale = 1.0
//	parameter.constant_physical.viscosity_oil = 1.0;     // mu_scale / sqrt(viscosity_ratio)

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.05;
	parameter.plot.volume_max_to_inject = 0.501;

	return parameter;
}

output::Property program::FlowWithDividedTubes::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::FlowWithDividedTubes::run()
{
	std::vector<int> id_fluid_inject_v{0}; 
	std::vector<double> radius_contrast_v{10};
	std::vector<double> sigma_v{0, 10, 30, 50}; 
	std::vector<double> viscosity_ratio_v{1};
	
	std::vector<double> n_initial_disturbance_v{1.5};
	
	output::Result output_result;
	
	for(auto n_initial_disturbance: n_initial_disturbance_v)
	{
		for(int id_fluid_inject: id_fluid_inject_v)
		{
			for(auto radius_contrast: radius_contrast_v)
			{
				for(auto sigma: sigma_v)
				{
					for(auto viscosity_ratio: viscosity_ratio_v)
					{
						// Generate base parameter
						auto parameter = generate_parameter();
						
						// Override with loop values
						parameter.simulation.id_fluid_inject = id_fluid_inject;
						parameter.constant_physical.sigma = sigma;
						parameter.geometry.radius_contrast = radius_contrast;
						
						if(viscosity_ratio < 1.0)
						{
							parameter.constant_physical.viscosity_water = viscosity_ratio;
							parameter.constant_physical.viscosity_oil = 1.0;
						}
						else
						{
							parameter.constant_physical.viscosity_water = 1.0;
							parameter.constant_physical.viscosity_oil = 1.0 / viscosity_ratio;
						}
						
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
