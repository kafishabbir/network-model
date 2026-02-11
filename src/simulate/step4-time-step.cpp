#include "simulate/step4-time-step.h"


void simulate::Step4TimeStep::calculate_and_assign_time_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.time = (tube.length / std::abs(tube.calculated.velocity));
	}
}

void simulate::Step4TimeStep::assign_time_step_to_state(
	nst::State& state
)
{
	calculate_and_assign_time_to_tubes(state);

	double min_val = state.tubes.front().calculated.time;
	int id_tube_min_time = 0;
	const int n_tubes = state.tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = state.tubes[i];
		const double time = tube.calculated.time;
		if(time < min_val)
		{
			id_tube_min_time = i;
			min_val = time;
		}
	}

	for(int i = 0; i < n_tubes; ++ i)
	{
		auto& tube = state.tubes[i];
		tube.calculated.is_minimum_time = (i == id_tube_min_time);
	}

	state.calculated.time_step = state.simulation_constant.time_step_resolution * min_val;
}
