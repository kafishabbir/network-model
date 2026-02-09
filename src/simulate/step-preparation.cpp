#include "simulate/step-preparation.h"

void simulate::StepPreparation::calculate_and_assign_resistance_and_capillary_pressures_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		const double resistance =
			simulate::Physics::calculate_resistance(tube, state);

		const double capillary_pressure =
			simulate::Physics::calculate_capillary_pressure_magnitude(tube, state);

		tube.calculated.resistance_coefficient = resistance;
		tube.calculated.capillary_pressure_magnitude = capillary_pressure;
	}
}
