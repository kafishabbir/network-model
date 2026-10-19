#include "program/permeability-mixture.h"
#include "simulate/menu.h"
#include "output/result.h"

dst::Parameter program::PermeabilityMixture::generate_parameter()
{
	dst::Parameter parameter;

	parameter.simulation.is_permeability_test = true;
	
	parameter.simulation.is_mode_overlapping_tubes_of_various_radii = false; 
	parameter.simulation.is_flow_as_opposed_to_test = true;     // true = flow simulation
	parameter.simulation.is_flow_const_flow_rate = false;        // true = constant volume injection
	parameter.simulation.is_const_porosity = false;              // true = constant porosity
	parameter.simulation.is_tubes_divided = false;
	parameter.simulation.run_iterative = true;
	parameter.simulation.flow_rate_in_pore_volumes = -1;
	parameter.simulation.id_fluid_inject = 0;
	parameter.simulation.is_initially_filled = false;
	parameter.simulation.n_periods_of_initial_disturbance = 4;
	parameter.simulation.real_geometry = true;
	parameter.simulation.inlet_pressure = -1;  // Ignored for constant volume injection



	parameter.simulation.is_permeability_test_dual_porosity_media = true;
	parameter.simulation.is_inject_mixture = true;
	
	// Geometry
	parameter.geometry.n_tube_rows = 40;
	parameter.geometry.n_tube_cols = 40;
	parameter.geometry.radius_contrast = 10;
	parameter.geometry.length_scale = 10.0;
	parameter.geometry.n_periods = 4;
	parameter.geometry.is_skewed = false;
	parameter.geometry.is_random_radius = false;
	parameter.geometry.n_inject_boundaries = 0;  // Will be set during initialization
	
	// Physical constants
	parameter.constant_physical.sigma = 0.0728;
	parameter.constant_physical.viscosity_water = 1e-3;  // viscosity_ratio = 1.0, mu_scale = 1.0
	parameter.constant_physical.viscosity_oil = 1e-3;     // mu_scale / sqrt(viscosity_ratio)

	// Computational constants
	parameter.constant_computational.time_step_resolution = 0.1;  // Default

	// Plot parameters
	parameter.plot.capture_frequency_in_volume_fraction = 0.5;
	parameter.plot.volume_max_to_inject = 2.6;

	return parameter;
}



output::Property program::PermeabilityMixture::generate_visual_property()
{
	output::Property property;

	property.tube_radius_min = 0.02;
	property.tube_radius_max = 0.10;
	property.largest_angle_tube_project_on_node = std::acos(-1) / 2.0;

	return property;
}

void program::PermeabilityMixture::run()
{
	
	//std::cout << "Executed" << std::endl;
	//return;
	//std::vector<int> id_fluid_inject_v{0}; 
	//std::vector<double> inlet_pressure_v{5e4};
	//std::vector<double> inlet_pressure_v{1e6, 2e4, 1e4, 7.5e3};
	//std::vector<double> inlet_pressure_v{1e6, 1e3, 5e2, 2e2, 1e2, 5e1};
	std::vector<double> inlet_pressure_v{300};
	std::vector<double> inlet_water_saturation_v{0, 0.2, 0.4, 0.6, 0.8, 1.0};
	
	output::Result output_result;
	
	for(const auto inlet_water_saturation: inlet_water_saturation_v)
	{
		for(const auto pressure: inlet_pressure_v)
		{
			auto parameter = generate_parameter();
			
			parameter.simulation.inlet_water_saturation = inlet_water_saturation;
			parameter.simulation.inlet_pressure = pressure;
			
			// Run simulation
			auto system = simulate::Menu::run(parameter);
			
			// Add to results
			output_result.add(system, generate_visual_property());
		}
	}
}
