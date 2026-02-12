#ifndef SIMULATE_STEP1_TUBE_FLOW_COEFFICIENT_H
#define SIMULATE_STEP1_TUBE_FLOW_COEFFICIENT_H

#include "global/dst.h"

namespace simulate
{
    class Step1TubeFlowCoefficient
    {
		static double resistance_coefficient(
			const nst::Tube& tube,
			const nst::State& state
		);

		static double capillary_pressure_magnitude(
			const nst::Tube& tube,
			const nst::State& state
		);

		static void capillary_pressure_magnitude(
			nst::State& state
		);

		static void resistance_coefficient(
			nst::State& state
		);

	public:
        static void assign_resistance_and_capillary_pressure_to_tubes(nst::State& state);
    };
}

#endif
