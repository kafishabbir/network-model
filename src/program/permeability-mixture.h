#ifndef PROGRAM_PERMEABILITY_MIXTURE_H
#define PROGRAM_PERMEABILITY_MIXTURE_H

#include "dst/parameter.h"
#include "output/property.h"

namespace program
{
	class PermeabilityMixture
	{
		static output::Property generate_visual_property();
		static dst::Parameter generate_parameter();

		public:
		static void run();
	};
}

#endif
