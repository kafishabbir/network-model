#ifndef SIMULATE_STEP6_POUR_INTO_NODE_H
#define SIMULATE_STEP6_POUR_INTO_NODE_H

#include "dst/system.h"

namespace step
{
	class Part06Pour
	{

		static nst::Tank produce_tank_with_fluids_flow_out_from_tube(
			const nst::Tube& tube
		);

		static std::vector<double> mpos_long_until(
			const nst::Tube& tube,
			const double lp
		);

		static void assign_id_node_id_tube_flow_direction(
			dst::System& state
		);

		static void assign_tank_to_tubes(
			dst::System& state
		);

		static void pour_from_tube_to_id_node_tank(
			dst::System& state
		);

		public:
		static void pour_from_tubes_to_node_tank(
			dst::System& state
		);
	};
}

#endif
