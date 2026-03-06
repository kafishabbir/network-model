#ifndef STEP_ALL_PARTS_H
#define STEP_ALL_PARTS_H

#include "dst/system.h"

namespace step
{
	class AllParts
	{
	public:
	
		static void run_single_time_step(
			dst::System& system
			//~ bool& is_solver_prepared,
			//~ Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
		);

	};
}

#endif
