#include "simulate/step4-time-step.h"


void simulate::Step4TimeStep::time_for_each_tube(
	nst::State& state
)
{
	for(auto& tube: state.tubes)
	{
		tube.calculated.time = (tube.length / std::abs(tube.calculated.velocity));
	}
}


void simulate::Step4TimeStep::select_tube_with_minimum_time(
	nst::State& state
)
{
	double val_min = state.tubes.front().calculated.time;
	int id_tube_time_min = 0;
	const int n_tubes = state.tubes.size();
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = state.tubes[i];
		const double time = tube.calculated.time;
		if(time < val_min)
		{
			id_tube_time_min = i;
			val_min = time;
		}
	}

	for(int i = 0; i < n_tubes; ++ i)
	{
		auto& tube = state.tubes[i];
		tube.calculated.is_time_min = (i == id_tube_time_min);
	}

	state.calculated.time_step = state.simulation_constant.time_step_resolution * val_min;
	state.measured.time_elapsed += state.calculated.time_step;
}

void simulate::Step4TimeStep::assign_time_step_to_state(
	nst::State& state
)
{
	time_for_each_tube(state);
	select_tube_with_minimum_time(state);
}
