#ifndef NST_STATE_H
#define NST_STATE_H

#include "nst/node.h"
#include "nst/tube.h"

namespace nst
{
	class State
	{
	public:
		Nodes nodes;
		Tubes tubes;
		double mu1;
		double mu2;
		double sigma;
		std::vector<std::vector<int>> table_tubes_connected_to_nodes;

		State(
			const Nodes& nodes,
			const Tubes& tubes,
			const double mu1 = 1,
			const double mu2 = 1,
			const double sigma = 1
		);

		std::vector<std::vector<int>> generate_table_tubes_connected_to_nodes() const;
		std::vector<int> tubes_connected_to_this_node(const int id_node) const;
	};

	typedef std::vector<State> States; // Sadly not the United States of America
}
#endif
