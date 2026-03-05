#include "simulate/menu.h"
#include "step/all-parts.h"
#include "simulate/step0-preparation.h"

#include <cmath>
#include <iomanip>


dst::States simulate::Menu::run(
	const dst::Parameter& parameter
)
{
	std::cout << std::endl << "\n\n" << std::string(30, '=') << '\n';
	std::cout << "Simulation started, parameters: " << parameter.str_cmd() << std::endl;
	
	utility::Time time;

	auto system = Step0Preparation::generate_state(parameter);

	dst::States states;
	state.reference.id_step = 0;
	while(Utility::decide_if_more_fluid_still_needs_to_be_injected(system))
	{
		step::AllParts::run_single_time_step(system);

		if(Utility::decide_if_capture_state_for_plot(system))
		{
			// ADD generalize
			step::Part10Measure::assign_saturation_and_pressure_vs_coordinate(state);
			
			states.push_back(system.state);
		}
		
		++ state.reference.id_step;
	}

	print_time_spent(time.passed(), system.state);
	
	return states;
}


void simulate::Menu::print_time_spent(const double time_program, dst::System& system)
{
	std::cout << "Time simulation=" << d(time_program/1000) << "s" << std::endl;
	std::cout << "Time per step=" << d(time_program/state.reference.id_step) << "ms" << std::endl;
	std::cout << "Fraction of time="
		<< d(state.measured.time_taken_by_solving_linear_equations / time_program);
	std::cout <<  ", spent on linear equations." << std::endl;

	int count = 0;
	for(auto t_step: state.measured.time_taken_by_each_step)
	{
		std::cout << "step-" << count++ << " t=" << std::setw(5) << std::round(t_step) << "ms, tf=" << std::round(t_step / time_program * 100) << "%" << '\n';
	}

	return states;
}



