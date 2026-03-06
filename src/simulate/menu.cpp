#include "simulate/menu.h"

#include "simulate/system-generator.h"
#include "simulate/preparation.h"
#include "step/all-parts.h"

//#include <cmath>
#include <iomanip>


bool simulate::Menu::inject_more_fluid(const dst::System& system)
{
	return system.state.measured.fluid_added.volume_total() < system.parameter.plot.volume_max_to_inject;
}

void simulate::Menu::capture_this_state(dst::System& system)
{
	const double vol = system.state.measured.fluid_added.volume_total();
	const double target =
		system.parameter.plot.capture_frequency_in_volume_fraction *
		system.measured.states.size();
	
	if(vol >= target)
	{
		// Conduct measurements
		system.measured.states.push_back(system.state);
	}
}

void simulate::Menu::print_time_spent(const double time_program, const dst::System& system)
{
	const auto& state = system.state;
	std::cout << "Time simulation=" << d(time_program/1000) << "s" << std::endl;
	std::cout << "Time per step=" << d(time_program/state.reference.id_step) << "ms, " << "n_steps=" << state.reference.id_step << std::endl;
	std::cout << "Fraction of time="
		<< d(system.measured.time_taken_by_solving_linear_equations / time_program);
	std::cout <<  ", spent on linear equations." << std::endl;

	int count = 0;
	for(auto t_step: system.measured.time_taken_by_each_step)
	{
		std::cout << "step-" << count++ << " t=" << std::setw(5) << std::setprecision(2) << std::fixed << t_step / 1000 << "ms, tf=" << std::round(t_step / time_program * 100) << "%" << '\n';
	}
}


dst::SystemOutput simulate::Menu::run(
	const dst::Parameter& parameter
)
{
	std::cout << std::endl << "\n\n" << std::string(30, '=') << '\n';
	std::cout << "Simulation started, parameters: " << parameter.str_cmd() << std::endl;
	
	utility::Time time;

	dst::System system(SystemGenerator::generate_parameter_processed_and_basic_state(parameter));
	
	Preparation::run(system);
	SetSolver::run(system);
	
	system.state.reference.id_step = 0;
	while(inject_more_fluid(system))
	{
		++ system.state.reference.id_step;
		
		step::AllParts::run_single_time_step(system);
		capture_this_state(system);		
	}

	print_time_spent(time.passed(), system);
	
	return dst::SystemOutput(system.parameter, system.measured);
}



