#ifndef SIMULATE_STEP4_TIME_STEP_H
#define SIMULATE_STEP4_TIME_STEP_H

#include "global/dst.h"

namespace simulate
{
    class Step4TimeStep
    {
		static void calculate_and_assign_time_to_tubes(
			nst::State& state
		);
        public:

        static void assign_time_step_to_state(
			nst::State& state
		);
    };
}

#endif
