#ifndef SIMULATE_STEP5_DISPLACEMENT_H
#define SIMULATE_STEP5_DISPLACEMENT_H

#include "global/dst.h"

namespace simulate
{
    class Step5Displacement
    {
        public:
        static void assign_volume_length_displacement(
			nst::State& state
		);
    };
}

#endif
