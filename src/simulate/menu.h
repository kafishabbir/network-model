#ifndef SIMULATE_MENU_H
#define SIMULATE_MENU_H

#include "io/file-write.h"

#include "simulate/step-preparation.h"
#include "simulate/step0-initialization.h"
#include "simulate/step1-pressure.h"
#include "simulate/step2-flow-rate.h"
#include "simulate/step3-velocity.h"
#include "simulate/step4-time-step.h"
#include "simulate/step5-integration.h"


namespace simulate
{

	class Menu
	{

	public:

		static void generate_and_plot();
	};
}

#endif
