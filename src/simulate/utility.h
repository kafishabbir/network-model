#ifndef SIMULATE_UTILITY_H
#define SIMULATE_UTILITY_H

#include "dst/system.h"

namespace simulate
{
	class Utility
	{
		
		
		static int find_type_fluid_contact(
			const int existing,
			const int addition
		);

		public:

		static nst::Tank total_fluid_in_system(const dst::System& system);
		

		static void assign_pressure(
			dst::System& system,
			const double pressure_left_boundary,
			const double pressure_right_boundary
		);
		
		static nst::Tank tube_inventory(const nst::Tube& tube);

		static void assign_type_fluid_contact(
			dst::System& system
		);
		
		
		static bool decide_if_more_fluid_still_needs_to_be_injected(const dst::System& system);
		static bool decide_if_capture_state_for_plot(dst::System& system);
	};
}

#endif
