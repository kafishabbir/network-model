#ifndef PROGRAM_OVERLAPPING_TUBES_OF_DIFFERING_RADII_H
#define PROGRAM_OVERLAPPING_TUBES_OF_DIFFERING_RADII_H

#include "dst/parameter.h"
#include "output/property.h"


namespace program
{
	class OverlappingTubesOfDifferingRadii
	{
		static output::Property generate_visual_property();
		static dst::Parameter generate_parameter();

	public:
		static void run();
	};
}

#endif
