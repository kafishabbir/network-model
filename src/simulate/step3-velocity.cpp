#include "simulate/step3-velocity.h"


void simulate::Step3Velocity::calculate_and_assign_velocity_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		const double r = tube.radius;
		const double area = decl::pi * std::pow(r, 2);
		const double flow_rate = tube.calculated.flow_rate;
		tube.calculated.velocity = flow_rate / area;
	}
}
