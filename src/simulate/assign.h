#ifndef SIMULATE_ASSIGN_H
#define SIMULATE_ASSIGN_H

#include "dst/system.h"

namespace simulate
{
	class Assign
	{

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
		
		static void update_node_contact_with_fluid(
			nst::Node& node,
			const int id_fluid_in_tube
		);
	};
}

#endif
