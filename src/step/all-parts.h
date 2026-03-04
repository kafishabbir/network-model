#ifndef STEP_ALL_PARTS_H
#define STEP_ALL_PARTS_H

#include "step/part01-reference.h"
#include "step/part02-pressure.h"
#include "step/part03-velocity.h"
#include "step/part04-time.h"
#include "step/part05-displacement.h"
#include "step/part06-pour.h"
#include "step/part07-inject.h"
#include "step/part08-distribute.h"
#include "step/part09-displace.h"
#include "step/part10-measure.h"

namespace step
{
	class AllParts
	{
	public:
	
		static void run_single_time_step(
			dst::System& state,
			bool& is_solver_prepared,
			Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
		);

	};
}

#endif
