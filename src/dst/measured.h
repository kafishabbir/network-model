#ifndef DST_MEASURED_H
#define DST_MEASURED_H

#include <vector>
#include "dst/state.h"

namespace dst
{
	class Measured
	{
		struct HighFrequencyData
		{
			double time;
			double pressure;
			double saturation;
			double flow_rate;
		};
	public:
	
		nst::Tank initial_fluid;
		std::vector<HighFrequencyData> high_frequency_data_v;
		std::vector<dst::State> state_v;

	};
}

#endif
