#ifndef SIMULATE_STEP3_VELOCITY_H
#define SIMULATE_STEP3_VELOCITY_H

#include "global/dst.h"

namespace simulate
{
    class Step3Velocity
    {
		static double flow_rate(
			const nst::Tube& tube,
			const nst::State& state
		);

		static void flow_rate(
			nst::State& state
		);

		static void velocity(
			nst::State& state
		);

        public:

        static void calculate_and_assign_flow_rate_and_velocity_to_tube(
			nst::State& state
		);
    };
}

#endif
