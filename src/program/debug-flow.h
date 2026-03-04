#ifndef PROGRAM_DEBUG_FLOW_H
#define PROGRAM_DEBUG_FLOW_H

#include "dst/parameter.h"
#include "output/property.h"

namespace program
{
	class DebugFlow
	{
		static output::Property generate_visual_property();
		static dst::Parameter generate_parameter();

		public:
		static void run();

	};
}

#endif
