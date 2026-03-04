#ifndef SIMULATE_STEP9_UPDATE_TUBE_MPOS_H
#define SIMULATE_STEP9_UPDATE_TUBE_MPOS_H

#include "dst/system.h"

namespace step
{
	class Part09Displace
	{
		static nst::Tube generate_tube_front(
			const nst::Tube& tube,
			const double lp,
			const double ap
		);

		static void join_tubes(
			nst::Tube& tube_front,
			const nst::Tube& tube_back,
			const double lp
		);

		static nst::Tube update_tube_mpos_according_to_proportion(
			const nst::Tube& tube
		);

		static std::vector<double> combine_swabs(
			const nst::Tube& tube
		);


		public:
		static void update_tube_mpos_according_to_proportion(
			dst::System& state
		);


	};
}

#endif
