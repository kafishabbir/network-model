#ifndef PROGRAM_PERMEABILITY_H
#define PROGRAM_PERMEABILITY_H

#include "dst/parameter.h"
#include "output/property.h"

namespace program
{
	class Permeability
	{
		static output::Property generate_visual_property();
		static dst::Parameter generate_property();

		public:
		static void run();
	};
}

#endif
