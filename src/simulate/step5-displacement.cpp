#include "simulate/step5-displacement.h"


void simulate::Step5Displacement::assign_volume_length_displacement(
	nst::State& state
)
{
	const double time_step = state.calculated.time_step;
	for(auto& tube: state.tubes)
	{
		tube.calculated.length_displacement_p = time_step * std::abs(tube.calculated.velocity) / tube.length;
		tube.calculated.volume_displacement = time_step * std::abs(tube.calculated.flow_rate);
	}
}

