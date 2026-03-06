#ifndef DST_SYSTEM_OUTPUT_H
#define DST_SYSTEM_OUTPUT_H

#include "dst/parameter.h"
#include "dst/measured.h"

namespace dst
{
	class SystemOutput
	{
	public:
		const Parameter parameter;
		Measured measured;
		
		SystemOutput(const Parameter&, const Measured&);
		static void blank();
	}; 
}

#endif
