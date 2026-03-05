#ifndef PROGRAM_FLOW_IN_PERIODIC_MEDIUM_H
#define PROGRAM_FLOW_IN_PERIODIC_MEDIUM_H

#include "dst/parameter.h"
#include "output/property.h"

namespace program
{
	class FlowInPeriodicMedium
	{
		static output::Property generate_visual_property();
		static dst::Parameter generate_parameter();

		public:
		static void run();
	};
}

#endif
