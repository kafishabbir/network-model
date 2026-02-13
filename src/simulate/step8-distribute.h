#ifndef SIMULATE_STEP8_DISTRIBUTE_H
#define SIMULATE_STEP8_DISTRIBUTE_H

#include "global/dst.h"
#include <algorithm>

namespace simulate
{
    class Step8Distribute
    {
		static void sort_id_tube_v_flow_out_at_node(
			nst::State& state
		);

		static void assign_proportion_to_tube(
			nst::State& state
		);

		static void assign_proportion_to_tube(
			const std::vector<int>& flow_out_id_tube_v,
			const nst::Tank& tank,
			nst::State& state
		);

        public:
        static void distribute_fluids_from_node_to_tube(
			nst::State& state
		);
    };
}

#endif
