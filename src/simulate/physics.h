#ifndef SIMULATE_PHYSICS_H
#define SIMULATE_PHYSICS_H

#include "global/dst.h"

namespace simulate
{
    class Physics
    {
        public:

		// resistence factor of tube in pousielle equation
        static double calculate_resistance(const nst::Tube& tube, const nst::State& state);
    };
}

#endif
