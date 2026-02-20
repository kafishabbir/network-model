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

       public:

        static void measure(nst::State& state);
    };
}

#endif



