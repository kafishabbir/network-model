#include "step/part05-displacement.h"


void step::Part05Displacement::assign_volume_length_displacement(
	dst::System& state
)
{
	const double time_step = state.calculated.time_step;
	for(auto& tube: state.tubes)
	{
		tube.calculated.length_displacement_p = time_step * std::abs(tube.calculated.velocity) / tube.length;
		tube.calculated.volume_displacement = time_step * std::abs(tube.calculated.flow_rate);
	}
}

