#ifndef DST_PARAMETER_H
#define DST_PARAMETER_H

#include <string>
#include "utility/str.h"

namespace dst
{
	class Parameter
	{
		static inline constexpr auto s = utility::Str::scientific;
		
		struct Simulation
		{
			bool is_permeability_test = false;
			bool is_mode_overlapping_tubes_of_various_radii;
			bool is_flow_as_opposed_to_test;
			bool is_flow_const_flow_rate;
			bool is_const_porosity;
			bool is_tubes_divided;
			bool real_geometry;
			bool run_iterative;
			bool is_biscuit = false;
			int id_fluid_inject;
			
			double inlet_pressure; // Ignored by const_q simulations
			bool is_initially_filled;
			double n_periods_of_initial_disturbance;
			
			double flow_rate_in_pore_volumes = 1.0;
			
		};
		
		struct Geometry
		{
			int n_tube_rows;
			int n_tube_cols;
			double radius_contrast;
			double length_scale;
			double n_periods;
			bool is_skewed;
			bool is_random_radius;
			int n_inject_boundaries; // to be filled by SystemGenerator
		};
		
		
		struct ConstantPhysical
		{
			double sigma;
			double viscosity_water;
			double viscosity_oil;
		};
		
		struct ConstantComputational
		{
			double time_step_resolution;
		};
		
		
		struct Plot
		{
			double volume_max_to_inject;
			double capture_frequency_in_volume_fraction;	
			int max_time_steps_for_debug;		
		};
	public:
	
		struct GeometryDistributions
		{
			struct Distribution
			{
				double ratio;
				double average;
				double max;
				double min;
				double variance;
			};
			
			Distribution radius;
			Distribution length;
			Distribution volume;
		};
		
	public:
		
		Simulation simulation;
		Geometry geometry;
		ConstantPhysical constant_physical;
		ConstantComputational constant_computational;
		Plot plot;
		GeometryDistributions geometry_distributions; // to be filled by SystemGenerator
		
		std::string str_cmd() const;
		std::string str() const;
	};
}

#endif
