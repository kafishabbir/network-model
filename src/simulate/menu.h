#ifndef SIMULATE_MENU_H
#define SIMULATE_MENU_H

#include "io/file-write.h"

#include "simulate/property.h"
#include "simulate/step0-preparation.h"
#include "simulate/step1-tube-flow-coefficient.h"
#include "simulate/step2-pressure.h"
#include "simulate/step3-velocity.h"
#include "simulate/step4-time-step.h"
#include "simulate/step5-displacement.h"
#include "simulate/step6-pour-into-node.h"
#include "simulate/step7-inject-evacuate.h"
#include "simulate/step8-distribute.h"
#include "simulate/step9-update-tube-mpos.h"
#include "simulate/step10-measure.h"

namespace simulate
{
    class Menu
    {
		static void perform_single_time_step(
			nst::State& state,
			bool& is_solver_prepared,
			Eigen::SimplicialLLT<Eigen::SparseMatrix<double>>& solver
		);

		static dst::States steps(nst::State& state);

        public:
		static dst::States run(const simulate::Property& simulate_property);
    };
}

#endif
