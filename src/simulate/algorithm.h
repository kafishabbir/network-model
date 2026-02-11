#ifndef SIMULATE_ALGORITHM_H
#define SIMULATE_ALGORITHM_H

#intclude "global/dst.h"

namespace simulate
{
    class Algorithm
    {
	public:
		static void unlock_all_tubes(
			nst::State& state,
			const std::vector<int>& flow_out_id_tube_v
		);

		static void distribute_water(
			nst::State& state,
			const std::vector<int>& flow_out_id_tube_v,
			nst::Tank& tank
		);

		static void distribute_oil(
			nst::State& state,
			const std::vector<int>& flow_out_id_tube_v,
			nst::Tank& tank
		);

		static std::pair<std::vector<double>, int> join_tank_to_tube(
			nst::Tube& tube,
			const nst::Tank& tank
		);
    };
}

#endif
