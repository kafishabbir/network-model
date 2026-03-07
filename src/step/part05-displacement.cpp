#include "step/part05-displacement.h"

void step::Part05Displacement::assign_volume_length_displacement(
	dst::System& system
)
{
	const double time_step = system.state.calculated.time_step;
	
	for(auto& tube: system.state.tubes)
	{
		tube.calculated.length_displacement_p = time_step * std::abs(tube.calculated.velocity) / tube.length;
		tube.calculated.volume_displacement = time_step * std::abs(tube.calculated.flow_rate);
	}
}
