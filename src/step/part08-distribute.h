#ifndef SIMULATE_STEP8_DISTRIBUTE_H
#define SIMULATE_STEP8_DISTRIBUTE_H

#include "dst/system.h"
#include <algorithm>

namespace step
{
	class Part08Distribute
	{
		static void sort_id_tube_v_flow_out_at_node(
			dst::System& state
		);

		static void assign_proportion_to_tube(
			dst::System& state
		);

		static void assign_proportion_to_tube(
			const std::vector<int>& flow_out_id_tube_v,
			const nst::Tank& tank,
			dst::System& state
		);

		public:
		static void distribute_fluids_from_node_to_tube(
			dst::System& state
		);
	};
}

#endif
