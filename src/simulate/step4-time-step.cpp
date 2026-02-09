#include "simulate/step4-time-step.h"


void simulate::Step4TimeStep::calculate_and_assign_time_to_tubes(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.time = (tube.length / std::abs(tube.calculated.velocity));
		std::cout << tube.calculated.time << std::endl;
	}
}

void simulate::Step4TimeStep::assign_time_step_to_state(
	nst::State& state
)
{
	calculate_and_assign_time_to_tubes(state);

	double min_val = state.tubes.front().calculated.time;
	int tube_id_min_time = 0;
	const int n_tubes = state.tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = state.tubes[i];
		const double time = tube.calculated.time;
		if(time < min_val)
		{
			tube_id_min_time = i;
			min_val = time;
		}
	}

	for(int i = 0; i < n_tubes; ++ i)
	{
		auto& tube = state.tubes[i];
		tube.calculated.is_minimum_time = (i == tube_id_min_time);
	}

	const double time_step = state.time_step_resolution * min_val;

	state.calculated.time_step = time_step;
}
