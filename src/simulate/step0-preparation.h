#ifndef SIMULATE_STEP0_PREPARATION_H
#define SIMULATE_STEP0_PREPARATION_H

#include "ic/geometry-rand.h"
#include "ic/geometry-flow.h"
#include "utility/str.h"
#include "simulate/property.h"
#include "simulate/utility.h"

namespace simulate
{
    class Step0Preparation
    {
        static void assign_str_of_simulate_property_to_state(
            nst::State& state,
            const simulate::Property& simulate_property
        );

        static std::pair<dst::Nodes, dst::Tubes> choose_network_geometry(
            const simulate::Property& simulate_property
        );

        static void choose_network_geometry(
            nst::State& state,
            const simulate::Property& simulate_property
        );

        static void modify_constants(
            nst::State& state,
            const simulate::Property& simulate_property
        );

        static void modify_boundary(
            nst::State& state,
            const simulate::Property& simulate_property
        );

        static void create_connections_id_tube_v_for_node(
            nst::State& state
        );

        static void assign_initial_total_fluid_to_state(
            nst::State& state
        );

        public:
		static nst::State generate_state(
			const simulate::Property& simulate_property
		);
    };
}

#endif
