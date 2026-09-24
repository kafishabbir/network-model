#ifndef DST_MEASURED_H
#define DST_MEASURED_H

#include <vector>
#include "dst/state.h"

namespace dst
{
	class Measured
	{
	public:
		struct HighFrequencyData
		{
			double time;
			double pressure;
			double saturation;
			
			double volume_total_fluid_injected;
			double volume_inject_fluid_injected;
			double volume_inject_fluid_removed;
			
			double average_velocity_water;
			double flow_rate_all_fluids_all_boundaries;
			double flow_rate_inject_fluid_input_boundary;
			double flow_rate_inject_fluid_output_boundary;
			
			double permeability_using_average_velocity_water;
			double permeability_using_total_flow_rate;
			double permeability_using_inject_fluid_injected;
			double permeability_using_inject_fluid_evacuated;
		};
		
	public:
		
		double time_taken_by_solving_linear_equations;
		std::vector<double> time_taken_by_each_step;
		
		nst::Tank initial_fluid;
		
		std::vector<HighFrequencyData> high_frequency_data_v;
		std::vector<dst::State> states;
		
		
		Measured();

	};
}

#endif
