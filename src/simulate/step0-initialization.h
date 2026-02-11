#ifndef SIMULATE_STEP0_INITIALIZATION_H
#define SIMULATE_STEP0_INITIALIZATION_H

#include "ic/menu.h"

namespace simulate
{
    class Step0Initialization
    {
		static nst::State state_flow_test();
        public:

		static nst::State choose_state();
    };
}

#endif
