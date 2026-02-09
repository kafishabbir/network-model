#ifndef SIMULATE_PHYSICS_H
#define SIMULATE_PHYSICS_H

#include "global/decl.h"
#include "global/dst.h"

namespace simulate
{
    class Physics
    {
        public:

		// resistence factor of tube in pousielle equation
        static double calculate_resistance(
			const nst::Tube& tube,
			const nst::State& state
		);

		static double calculate_capillary_pressure_magnitude(
			const nst::Tube& tube,
			const nst::State& state
		);

		static double determine_capillary_pressure_sign(
			const nst::Tube& tube,
			const int node_id_relative_to
		);
    };
}

#endif
