#ifndef DST_PARAMETER_H
#define DST_PARAMETER_H

#include <string>

namespace dst
{
	class Parameter
	{
		struct Simulation
		{
			bool is_flow_as_opposed_to_test;
			bool is_flow_const_flow_rate;
			bool is_const_porosity;
			int id_fluid_inject;
			
			double inlet_pressure; // Ignored by const_q simulations
		};
		
		struct Geometry
		{
			int n_tube_rows;
			int n_tube_cols;
			double radius_contrast;
			double length_scale;
			double n_periods;
			
			int n_inject_boundaries;
		};
		
		struct GeometryDistributions
		{
			struct Distribution
			{
				double average;
				double min;
				double max;
				double variance;
			};
			
			Distribution radius;
			Distribution length;
			Distribution volume;
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
		
		Simulation simulation;
		Geometry geometry;
		GeometryDistributions geometry_distributions;
		ConstantPhysical constant_physical;
		ConstantComputational constant_computational;
		Plot plot;
		
		std::string str_cmd() const;
	};
}

#endif
