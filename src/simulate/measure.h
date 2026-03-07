#ifndef SIMULATE_MEASURE_H
#define SIMULATE_MEASURE_H

#include "dst/system.h"

namespace simulate
{
	class Measure
	{
	public:
		static std::vector<std::pair<double, double>> generate_pressure_vs_y(
			const dst::System& system
		);
		static std::vector<std::pair<double, double>> generate_saturation_vs_x(
			const dst::System& system
		);
		static double find_average_pressure(const dst::System& system);
		static nst::Tank tube_inventory(const nst::Tube& tube);
		static nst::Tank fluid_in_system(const dst::System& system);
	};
}

#endif
