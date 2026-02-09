#ifndef IC_FLOW_VISUALIZATION_H
#define IC_FLOW_VISUALIZATION_H

#include "global/dst.h"
#include "utility/random.h"

namespace ic
{
	class FlowVisualization
	{
		static dst::Tubes generate_tubes_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static dst::Nodes generate_nodes_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static nst::State generate_rectangular(
			const int n_rows_tube,
			const int n_cols_tube
		);
	public:


		static dst::States generate_states_rectangular_plus_random();
	};

}

#endif
