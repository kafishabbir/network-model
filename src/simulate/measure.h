#ifndef SIMULATE_MEASURE_H
#define SIMULATE_MEASURE_H

#include "dst/system.h"

namespace simulate
{
	class Measure
	{
		
	public:
		static nst::Tank tube_inventory(const nst::Tube& tube);
		static nst::Tank fluid_in_system(const dst::System& system);
	};
}

#endif
