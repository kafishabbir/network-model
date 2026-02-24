#ifndef PROGRAM_FLOW_IN_PERIODIC_MEDIUM_H
#define PROGRAM_FLOW_IN_PERIODIC_MEDIUM_H

#include "simulate/menu.h"
#include "output/property.h"

namespace program
{
	class FlowInPeriodicMedium
	{
		static output::Property generate_visual_property();
		static simulate::Property generate_property();

		public:
		static void run();
	};
}

#endif
