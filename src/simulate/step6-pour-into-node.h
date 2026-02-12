#ifndef SIMULATE_STEP6_POUR_INTO_NODE_H
#define SIMULATE_STEP6_POUR_INTO_NODE_H

#include "global/dst.h"

namespace simulate
{
    class Step6PourIntoNode
    {
		static void assign_id_node_id_tube_flow_direction(
			nst::State& state
		);

		static void clear_node_tank(
			nst::State& state
		);

		static void pour_from_tube_to_id_node_tank(
			nst::State& state
		);

        public:
        static void pour_from_tubes_to_node_tank(
			nst::State& state
		);
    };
}

#endif
