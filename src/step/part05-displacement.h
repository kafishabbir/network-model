#ifndef SIMULATE_STEP5_DISPLACEMENT_H
#define SIMULATE_STEP5_DISPLACEMENT_H

#include "dst/system.h"

namespace step
{
	class Part05Displacement
	{
		public:
		static void assign_volume_length_displacement(
			dst::System& state
		);
	};
}

#endif
