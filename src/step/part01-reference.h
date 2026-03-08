#ifndef STEP_PART01_REFERENCE_H
#define STEP_PART01_REFERENCE_H

#include "dst/system.h"

namespace step
{
	class Part01Reference
	{
		static void reset_calculated(
			dst::System& system
		);
		
		static double evaluate_mu(
			const nst::Tube& tube,
			const dst::System& system
		);
		
		static double resistance_coefficient(
			const nst::Tube& tube,
			const dst::System& system
		);
		
		static std::pair<int, int> add_pseudo_meniscus(
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
		static void run(
			dst::System& system
		);
	};
}

#endif
