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
			dst::System& system,
			const dst::Parameter& simulate_property
		);

		static std::pair<dst::Nodes, dst::Tubes> choose_network_geometry(
			const dst::Parameter& simulate_property
		);

		static void choose_network_geometry(
			dst::System& system,
			const dst::Parameter& simulate_property
		);

		static void modify_constants(
			dst::System& system,
			const dst::Parameter& simulate_property
		);

		static void modify_boundary(
			dst::System& system,
			const dst::Parameter& simulate_property
		);
		
		static void calculate_and_set_lr_min_max(dst::System& system);
		
		static int count_inlet_nodes(
			const dst::System& system
		);
		
		static void set_other_references(
			dst::System& system,
			const dst::Parameter& simulate_property
		);

		static void create_connections_id_tube_v_for_node(
			dst::System& system
		);

		static void assign_initial_total_fluid_to_state(
			dst::System& system
		);

		public:
		static nst::State generate_state(
			const dst::Parameter& simulate_property
		);
	};
}

#endif
