#ifndef SIMULATE_MEASURE_H
#define SIMULATE_MEASURE_H

#include "dst/system.h"

namespace simulate
{
	class Measure
	{
		static nst::Tank tube_inventory(const nst::Tube& tube);
		
	public:
		static nst::Tank total_fluid_in_system(const dst::System& system);
	};
}

#endif
