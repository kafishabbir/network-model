#ifndef SIMULATE_STEP7_INJECT_EVACUATE_H
#define SIMULATE_STEP7_INJECT_EVACUATE_H

#include "global/dst.h"

namespace simulate
{
    class Step7InjectEvacuate
    {
		static void assign_volume_flow_out_to_node(
			nst::State& state
		);

		static void balance_flow_at_open_nodes(
			nst::State& state
		);

        public:
        static void inject_and_evacuate_fluid_from_system(
			nst::State& state
		);
    };
}

#endif
