#ifndef SIMULATE_PREPARATION_H
#define SIMULATE_PREPARATION_H

#include "dst/system.h"

namespace simulate
{
	class Preparation
	{
		static void fill_system_initial_upto_certain_x(
			dst::System& system
		);

		static void set_inlet_outlet_boundaries(
			dst::System& system
		);
		
		static void create_connections_id_tube_v_for_node(
			dst::System& system
		);
		
		static void assign_initial_total_fluid_to_system(
			dst::System& system
		);
		
	public:
		static void run(
			dst::System& system
		);
	};
}

#endif
