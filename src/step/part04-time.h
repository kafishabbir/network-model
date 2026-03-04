#ifndef SIMULATE_STEP4_TIME_STEP_H
#define SIMULATE_STEP4_TIME_STEP_H

#include "dst/system.h"

namespace step
{
	class Part04Time
	{
		static void time_for_each_tube(
			dst::System& state
		);

		static void select_tube_with_minimum_time(
			dst::System& state
		);

		public:
		static void assign_time_step_to_state(
			dst::System& state
		);
	};
}

#endif
