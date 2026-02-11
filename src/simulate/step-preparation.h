#ifndef SIMULATE_STEP_PREPARATION_H
#define SIMULATE_STEP_PREPARATION_H

#include "simulate/physics.h"

namespace simulate
{
	class StepPreparation
	{
	public:
		static void assign_resistance_to_tubes(nst::State& state);
		static void assign_capillary_pressure_magnitude_to_tubes(nst::State& state);
		static void assign_connections_id_tube_to_nodes(nst::State& state);
	};
}

#endif
