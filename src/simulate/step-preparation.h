#ifndef SIMULATE_STEP_PREPARATION_H
#define SIMULATE_STEP_PREPARATION_H

#include "global/dst.h"
#include "simulate/physics.h"

namespace simulate
{
    class StepPreparation
    {
        public:
        static void calculate_and_assign_resistance_and_capillary_pressures_to_tubes(
			nst::State& state
		);
    };
}

#endif
