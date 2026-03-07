#ifndef SIMULATE_ACCURACY_H
#define SIMULATE_ACCURACY_H

#include "dst/system.h"

namespace simulate
{
	class Accuracy
	{
	public:
		static double total_delta(const dst::System& system);
		static double water_delta(const dst::System& system);
		static double oil_delta(const dst::System& system);
	};
}

#endif
