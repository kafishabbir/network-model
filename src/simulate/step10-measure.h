#ifndef SIMULATE_STEP10_MEASURE_H
#define SIMULATE_STEP10_MEASURE_H

#include "simulate/utility.h"

namespace simulate
{
	class Step10Measure
	{

		static double total_delta(const nst::State& state);
		static double water_delta(const nst::State& state);
		static double oil_delta(const nst::State& state);
		static double find_average_pressure(const nst::State& state);

		
		static std::vector<std::pair<double, double>> generate_pressure_vs_y(
			const nst::State& state
		);
		static std::vector<std::pair<double, double>> generate_saturation_vs_x(
			const nst::State& state
		);

	   public:

		static void measure(nst::State& state);
		static void assign_saturation_and_pressure_vs_coordinate(nst::State& state);
	};
}

#endif



