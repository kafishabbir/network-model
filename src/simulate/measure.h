#ifndef SIMULATE_MEASURE_H
#define SIMULATE_MEASURE_H

namespace simulate
{
	class Measure
	{
	public:
		static void blank();
	};
}

#endif

namespace simulate
{
	class Utility
	{
		
		static int find_type_fluid_contact(
			const int existing,
			const int addition
		);

		public:

		static nst::Tank total_fluid_in_system(const dst::System& system);
		

		static void assign_pressure(
			dst::System& system,
			const double pressure_left_boundary,
			const double pressure_right_boundary
		);
		
		static nst::Tank tube_inventory(const nst::Tube& tube);

		static void assign_type_fluid_contact(
			dst::System& system
		);
	};
}
