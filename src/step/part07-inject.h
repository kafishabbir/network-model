#ifndef SIMULATE_STEP7_INJECT_EVACUATE_H
#define SIMULATE_STEP7_INJECT_EVACUATE_H

#include "dst/system.h"

namespace step
{
	class Part07Inject
	{
		static nst::Tank produce_tank_with_oil_sliced_out(
			const nst::Tank& tank,
			const double volume
		);

		static void assign_volume_flow_out_to_node(
			dst::System& state
		);

		static void balance_flow_at_open_nodes(
			dst::System& state
		);

		public:
		static void inject_and_evacuate_fluid_from_system(
			dst::System& state
		);
	};
}

#endif
