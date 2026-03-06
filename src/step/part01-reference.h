#ifndef SIMULATE_STEP1_TUBE_FLOW_COEFFICIENT_H
#define SIMULATE_STEP1_TUBE_FLOW_COEFFICIENT_H

#include "dst/system.h"

namespace step
{
	class Part01Reference
	{
		static void reset_calculated(dst::System& system);
		
		static double evaluate_mu(
			const nst::Tube& tube,
			const dst::System& system
		);
		
		// For individual tubes
		static double resistance_coefficient(
			const nst::Tube& tube,
			const dst::System& system
		);

		static double capillary_pressure_magnitude(
			const nst::Tube& tube,
			const dst::System& system
		);
	
		
		static void resistance_coefficient(
			dst::System& system
		);
		
		
		static void capillary_pressure_magnitude(
			dst::System& system
		);

		
	public:
		static void assign_resistance_and_capillary_pressure_to_tubes(dst::System& system);
	};
}

#endif
