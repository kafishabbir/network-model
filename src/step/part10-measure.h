#ifndef STEP_PART10_MEASURE_H
#define STEP_PART10_MEASURE_H

#include "dst/system.h"

namespace step
{
	class Part10Measure
	{		
	public:
		static void compulsory(dst::System& system);
		static void capture(dst::System& system);
		static void high_frequency_data(dst::System& system);
	};
}

#endif
