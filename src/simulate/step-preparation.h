#ifndef SIMULATE_STEP_PREPARATION_H
#define SIMULATE_STEP_PREPARATION_H

#include "ic/menu.h"

namespace simulate
{
    class StepPreparation
    {
		static void choose_network_geometry(
			nst::State& state
		);

		static void modify_constants(
			nst::State& state
		);

		static void modify_boundary(
			nst::State& state
		);

		static void create_connections_id_tube_v_for_node(
			nst::State& state
		);

        public:

		static nst::State generate_state();
    };
}

#endif
