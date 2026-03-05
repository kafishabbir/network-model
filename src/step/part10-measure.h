#ifndef SIMULATE_STEP10_MEASURE_H
#define SIMULATE_STEP10_MEASURE_H

#include "simulate/utility.h"

namespace step
{
	class Part10Measure
	{

		static double total_delta(const dst::System& system);
		static double water_delta(const dst::System& system);
		static double oil_delta(const dst::System& system);
		static double find_average_pressure(const dst::System& system);

		
		static std::vector<std::pair<double, double>> generate_pressure_vs_y(
			const dst::System& system
		);
		static std::vector<std::pair<double, double>> generate_saturation_vs_x(
			const dst::System& system
		);

	   public:

		static void measure(dst::System& system);
		static void assign_saturation_and_pressure_vs_coordinate(dst::System& system);
	};
}

#endif



