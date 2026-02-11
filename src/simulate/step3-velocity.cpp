#include "simulate/step3-velocity.h"


void simulate::Step3Velocity::calculate_and_assign_velocity_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.velocity = tube.calculated.flow_rate / tube.area();
	}
}
