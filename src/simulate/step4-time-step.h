#ifndef SIMULATE_STEP4_TIME_STEP_H
#define SIMULATE_STEP4_TIME_STEP_H

#include "global/dst.h"

namespace simulate
{
    class Step4TimeStep
    {
		static void time_for_each_tube(
			nst::State& state
		);

		static void select_tube_with_minimum_time(
			nst::State& state
		);

        public:
        static void assign_time_step_to_state(
			nst::State& state
		);
    };
}

#endif
