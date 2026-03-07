#include "step/part04-time.h"

void step::Part04Time::time_for_each_tube(
	dst::System& system
)
{
	for(auto& tube: system.state.tubes)
	{
		tube.calculated.time = (tube.length / std::abs(tube.calculated.velocity));
	}
}

void step::Part04Time::select_tube_with_minimum_time(
	dst::System& system
)
{
	double val_min = system.state.tubes.front().calculated.time;
	int id_tube_time_min = 0;
	const int n_tubes = system.state.tubes.size();
	
	for(int i = 0; i < n_tubes; ++ i)
	{
		const auto& tube = system.state.tubes[i];
		const double time = tube.calculated.time;
		if(time < val_min)
		{
			id_tube_time_min = i;
			val_min = time;
		}
	}

	for(int i = 0; i < n_tubes; ++ i)
	{
		auto& tube = system.state.tubes[i];
		tube.calculated.is_time_min = (i == id_tube_time_min);
	}

	system.state.calculated.time_step = system.parameter.constant_computational.time_step_resolution * val_min;
	system.state.measured.time_elapsed += system.state.calculated.time_step;
}

void step::Part04Time::assign_time_step_to_state(
	dst::System& system
)
{
	time_for_each_tube(system);
	select_tube_with_minimum_time(system);
}
