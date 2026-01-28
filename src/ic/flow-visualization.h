#ifndef IC_FLOW_VISUALIZATION_H
#define IC_FLOW_VISUALIZATION_H

#include "global/dst.h"
#include <utility>

namespace ic
{
	class FlowVisualization
	{
		static Tubes generate_tubes_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static Nodes generate_nodes_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static State generate_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);
	public:


		static States generate_states_rectangular_plus_random();
	};

}

#endif
