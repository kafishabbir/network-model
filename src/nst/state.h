#ifndef NST_STATE_H
#define NST_STATE_H

#include "nst/node.h"
#include "nst/tube.h"

namespace nst
{
	class State
	{
		struct Calculated
		{
			double time_step;
		};

	public:
		std::vector<nst::Node> nodes;
		std::vector<nst::Tube> tubes;
		double mu1;
		double mu2;
		double sigma;
		double time_step_resolution;
		std::vector<std::vector<int>> table_tubes_connected_to_nodes;

		Calculated calculated;
		State(
			const std::vector<nst::Node>& nodes,
			const std::vector<nst::Tube>& tubes,
			const double mu1 = 1,
			const double mu2 = 1,
			const double sigma = 1,
			const double time_step_resolution = 0.1
		);

		std::vector<std::vector<int>> generate_table_tubes_connected_to_nodes() const;
		std::vector<int> tubes_connected_to_this_node(const int id_node) const;
	};

}
#endif
