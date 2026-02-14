#ifndef SIMULATE_STEP10_MEASURE_H
#define SIMULATE_STEP10_MEASURE_H

#include "global/dst.h"

namespace simulate
{
    class Step10Measure
    {
		static nst::Tank tube_inventory(const nst::Tube& tube);

		static double total_delta(const nst::State& state);
		static double water_delta(const nst::State& state);
		static double oil_delta(const nst::State& state);

       public:
		static nst::Tank total_fluid_in_system(const nst::State& state);
        static void measure(nst::State& state);
    };
}

#endif



