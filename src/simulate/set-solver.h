#ifndef SIMULATE_SET_SOLVER_H
#define SIMULATE_SET_SOLVER_H

#include "dst/system.h"

namespace simulate
{
	class SetSolver
	{
		static void assign_symmetric_id_to_nodes(
			dst::System& system
		);
		
		static void fill_sparse_matrix(
			dst::System& system
		);
		
		static void analyze_pattern(
			dst::System& system
		);
		
	public:
		static void run(
			dst::System& system
		);
	};
}

#endif
