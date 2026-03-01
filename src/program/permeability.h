#ifndef PROGRAM_PERMEABILITY_H
#define PROGRAM_PERMEABILITY_H

#include "simulate/menu.h"
#include "output/property.h"

namespace program
{
	class Permeability
	{
		static output::Property generate_visual_property();
		static simulate::Property generate_property();

		public:
		static void run();
	};
}

#endif
