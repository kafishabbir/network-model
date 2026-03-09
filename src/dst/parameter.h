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
			bool is_flow_as_opposed_to_test;
			bool is_flow_const_flow_rate;
			bool is_const_porosity;
			int id_fluid_inject;
			
			double inlet_pressure; // Ignored by const_q simulations
			bool is_initially_filled;
		};
		
		struct Geometry
		{
			int n_tube_rows;
			int n_tube_cols;
			double radius_contrast;
			double length_scale;
			double n_periods;
			bool is_skewed;
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
