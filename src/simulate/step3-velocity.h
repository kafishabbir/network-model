#ifndef SIMULATE_STEP3_VELOCITY_H
#define SIMULATE_STEP3_VELOCITY_H

#include "global/dst.h"

namespace simulate
{
    class Step3Velocity
    {
        public:
		static void calculate_and_assign_velocity_to_tubes(
			nst::State& state
		);
    };
}

#endif
