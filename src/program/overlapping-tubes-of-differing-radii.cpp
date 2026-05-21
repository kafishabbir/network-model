#include "program/overlapping-tubes-of-differing-radii.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::OverlappingTubesOfDifferingRadii::generate_parameter()
{	
	dst::Parameter parameter;

	parameter.simulation.run_iterative = false;
	
	parameter.simulation.is_mode_overlapping_tubes_of_various_radii = true;
	parameter.simulation.is_flow_as_opposed_to_test = true; 
	parameter.simulation.is_const_porosity = false;
	parameter.simulation.real_geometry = true;
	parameter.simulation.inlet_pressure = -1;
	
	parameter.simulation.is_tubes_divided = true;
	parameter.simulation.run_iterative = true;
	parameter.simulation.flow_rate_in_pore_volumes = 0.1;
	parameter.simulation.id_fluid_inject = 0;

	parameter.simulation.is_flow_const_flow_rate = true; 
	parameter.simulation.inlet_pressure = -1;  // Ignored for constant volume injection

	// Geometry
	parameter.geometry.n_tube_rows = 10;
	parameter.geometry.n_tube_cols = 80;
	parameter.geometry.radius_contrast = 0.95;
	parameter.geometry.length_scale = 5.0;
	parameter.geometry.n_periods = 20;
	parameter.geometry.n_inject_boundaries = 0;  // Will be set during initialization
	
	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.2;
	parameter.plot.volume_max_to_inject = 0.605;
	
	parameter.plot.max_time_steps_for_debug = 1;
	return parameter;
}

output::Property program::OverlappingTubesOfDifferingRadii::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::OverlappingTubesOfDifferingRadii::run()
{
	std::vector<int> id_fluid_inject_v{0}; 
	std::vector<double> sigma_v{0, 0.01, 0.1, 1}; 
	std::vector<double> viscosity_ratio_v{1};
	

	
	output::Result output_result;

	for(int id_fluid_inject: id_fluid_inject_v)
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
				
				// Run simulation
				auto system = simulate::Menu::run(parameter);
				
				// Add to results
				output_result.add(system, generate_visual_property());
			}
		}
	}
}

