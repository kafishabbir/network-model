#ifndef SIMULATE_MENU_H
#define SIMULATE_MENU_H

//#include "ic/flow-visualization.h"
#include "ic/displacement-test.h"

#include "simulate/step-preparation.h"
#include "simulate/step1-pressure.h"
#include "simulate/step2-flow-rate.h"
#include "simulate/step3-velocity.h"
#include "simulate/step4-time-step.h"
#include "simulate/step5-integration.h"

#include "io/file-write.h"

#include "visualize/menu.h"

namespace simulate
{

	class Menu
	{

		static void set_boundaries(nst::State& state);
	public:

		// static void displace();
		static void generate_and_plot();
	};
}

#endif
