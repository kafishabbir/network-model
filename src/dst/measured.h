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
			double flow_rate;
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
