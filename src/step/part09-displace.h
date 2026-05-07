#ifndef SIMULATE_STEP9_UPDATE_TUBE_MPOS_H
#define SIMULATE_STEP9_UPDATE_TUBE_MPOS_H

#include "dst/system.h"

namespace step
{
	class Part09Displace
	{
		static std::pair<int, std::vector<double>> generate_tube_front(
			const double ap,
			const double lp
		);

		
		static std::pair<int, std::vector<double>> join_tubes(
			const std::pair<int, std::vector<double>>& tube_front,
			const std::pair<int, std::vector<double>>& tube_back,
			const double lp
		);

		static std::pair<int, std::vector<double>> generate_new_mpos_from_add_proportion(
			const nst::Tube& tube
		);

		static std::vector<double> combine_swabs(
			const nst::Tube& tube
		);


		public:
		static void generate_new_mpos_from_add_proportion(
			dst::System& system
		);


	};
}

#endif
