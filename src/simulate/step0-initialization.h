#ifndef SIMULATE_STEP0_INITIALIZATION_H
#define SIMULATE_STEP0_INITIALIZATION_H

#include "ic/menu.h"

namespace simulate
{
    class Step0Initialization
    {
		static const double fluid_water_viscosity;
		static const double fluid_water_density;
		static const double fluid_oil_viscosity;
		static const double fluid_oil_density;
		static const double sigma;
		static const double time_step_resolution;

        public:

		static nst::State generate_state();
    };
}

#endif
