#ifndef PROGRAM_DEBUG_FLOW_H
#define PROGRAM_DEBUG_FLOW_H

#include "simulate/menu.h"
#include "output/property.h"

namespace program
{
	class DebugFlow
	{
		static output::Property generate_visual_property();
		static simulate::Property generate_property();

		public:
		static void run();

	};
}

#endif
