#ifndef SIMULATE_ASSIGN_H
#define SIMULATE_ASSIGN_H

#include "dst/system.h"

namespace simulate
{
	class Assign
	{
		static int find_type_fluid_contact(
			const int existing,
			const int addition
		);

	public:

		static void assign_pressures_inlet(
			dst::System& system,
			const double pressure_inlet
		);
		
		static void assign_pressures_outlet(
			dst::System& system,
			const double pressure_outlet
		);
		
		static void assign_pressures(
			dst::System& system,
			const double pressure_inlet,
			const double pressure_outlet
		);
		
		static void assign_type_fluid_contact(
			dst::System& system
		);
		
	};
}

#endif
