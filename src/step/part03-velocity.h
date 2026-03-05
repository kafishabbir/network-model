#ifndef SIMULATE_STEP3_VELOCITY_H
#define SIMULATE_STEP3_VELOCITY_H

#include "dst/system.h"

namespace step
{
	class Part03Velocity
	{
		static double flow_rate(
			const nst::Tube& tube,
			const dst::System& system
		);

		static void flow_rate(
			dst::System& system
		);

		static void velocity(
			dst::System& system
		);

		public:

		static void calculate_and_assign_flow_rate_and_velocity_to_tube(
			dst::System& system
		);
	};
}

#endif
