#ifndef STEP_ALL_PARTS_H
#define STEP_ALL_PARTS_H

#include "dst/system.h"
#include "utility/time.h"

namespace step
{
	class AllParts
	{
	public:
	
		static void run_single_time_step(
			dst::System& system
		);
		
		static void run_single_time_step_debug(
			dst::System& system
		);


	};
}

#endif
