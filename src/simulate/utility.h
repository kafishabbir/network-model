#ifndef SIMULATE_UTILITY_H
#define SIMULATE_UTILITY_H

#include "global/dst.h"

namespace simulate
{
    class Utility
    {
		static nst::Tank tube_inventory(const nst::Tube& tube);


        public:

		static nst::Tank total_fluid_in_system(const nst::State& state);
		static void reset_calculated(nst::State& state);

		static void assign_pressure(
			const double pressure_left_boundary,
			const double pressure_right_boundary
		);

		static bool decide_if_more_fluid_still_needs_to_be_injected(const nst::State& state);
		static bool decide_if_capture_state_for_plot(const nst::State& state);
    };
}

#endif
