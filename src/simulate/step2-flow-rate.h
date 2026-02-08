#ifndef SIMULATE_STEP2_FLOW_RATE_H
#define SIMULATE_STEP2_FLOW_RATE_H

#include "global/dst.h"
#include "simulate/physics.h"

namespace simulate
{
    class Step2FlowRate
    {
        public:
        static void calculate_and_assign_flow_rates_to_tubes(
			nst::State& state
		);
    };
}

#endif
