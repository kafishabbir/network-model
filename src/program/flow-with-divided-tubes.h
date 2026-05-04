#ifndef PROGRAM_FLOW_WITH_DIVIDED_TUBES_H
#define PROGRAM_FLOW_WITH_DIVIDED_TUBES_H

#include "dst/parameter.h"
#include "output/property.h"

namespace program
{
	class FlowWithDividedTubes
	{
		static output::Property generate_visual_property();
		static dst::Parameter generate_parameter();

		public:
		static void run();
	};
}

#endif
