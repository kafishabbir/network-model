#ifndef STEP_PART02_PRESSURE_H
#define STEP_PART02_PRESSURE_H

#include "dst/system.h"

namespace step
{
	class Part02Pressure
	{
		struct Equation
		{
			std::vector<std::pair<int, double>> entry_v;
			double b;
		};
		
		static Equation generate_equation_for_node(
			const int id_node,
			const dst::System& system
		);
		
	public:
		static void run(
			dst::System& system
		);
	};
}

#endif
