#ifndef GENERATOR_IC_H
#define GENERATOR_IC_H

#include "global/dst.h"
#include <utility>

namespace generator
{
	class Ic
	{
		static Tubes generate_v_tubes_for_square_lattice(
			const int n_rows_tube,
			const int n_cols_tube
		);

		static Nodes generate_v_nodes_for_square_lattice(
			const int n_rows_tube,
			const int n_cols_tube
		);

	public:
		static std::pair<Nodes, Tubes> square_lattice(
			const int n_rows_tube,
			const int n_cols_tube
		);
	};


}
#endif
