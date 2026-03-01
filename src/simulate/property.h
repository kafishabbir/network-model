#ifndef SIMULATE_PROPERTY_H
#define SIMULATE_PROPERTY_H

#include "utility/str.h"

namespace simulate
{
	class Property
	{
		static inline constexpr auto d = utility::Str::general;
		
	public:
		enum class TypeSimulation
			{
				test_simple,
				test_random,
				periodic_const_pressure_variable_porosity,
				periodic_const_volume_injection_variable_porosity,
				periodic_const_pressure_const_porosity,
				periodic_const_volume_injection_const_porosity
			};
		
		//~ enum class TypeSimulation
		//~ {
			//~ test_simple,
			//~ test_random,
			//~ periodic_const_pressure_variable_porosity,
			//~ periodic_const_volume_injection_variable_porosity,
			//~ periodic_const_pressure_const_porosity,
			//~ periodic_const_volume_injection_const_porosity
		//~ };
		
		TypeSimulation type_simulation;
		int n_tube_rows;
		int n_tube_cols;
		int id_fluid_inject;
		double constant_sigma;
		double constant_radius_contrast;
		double constant_mu1_by_mu2;
		double constant_mu_scale;
		double constant_length_scale;
		double capture_frequency_in_volume_fraction;
		double volume_max_to_inject;
		int n_periods;
		double inlet_pressure; // Ignored by const_q simulations

		// Plotting
		int capture_frequency_for_frequent_data; 
	
		//~ // Geometry of network model
		//~ int n_tube_rows;
		//~ int n_tube_cols;
		//~ int n_periods;
		//~ double constant_radius_contrast;
		//~ double constant_length_scale;
		
		//~ // Simulation type
		//~ TypeSimulation type_simulation;
		//~ int id_fluid_inject;
		
		//~ // Physical constants 
		//~ double constant_sigma;
		//~ double constant_mu1_by_mu2;
		//~ double constant_mu_scale;
		
		//~ // Boundary conditions
		//~ double inlet_pressure; // Ignored by const_q simulations
		
		//~ // When to stop
		//~ double volume_max_to_inject;
		
		//~ // Plotting
		//~ double capture_frequency_in_volume_fraction;
		//~ int capture_frequency_for_frequent_data; // First save all the points from every step, and then discard the ones to keep output.json small

		Property();
		std::string str() const;
	};
}

#endif
