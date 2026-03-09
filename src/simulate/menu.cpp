#include "simulate/menu.h"

#include "simulate/system-generator.h"
#include "simulate/preparation.h"
#include "simulate/set-solver.h"
#include "step/all-parts.h"
#include "step/part10-measure.h"

//#include <cmath>
#include <iomanip>


bool simulate::Menu::inject_more_fluid(const dst::System& system)
{
	const double volume_system = system.measured.initial_fluid.volume_total();
	
	if(system.parameter.simulation.is_flow_const_flow_rate && 
		volume_system <= 1.1 &&
		volume_system >= 0.9
	)
	{
		return system.state.measured.time_elapsed < system.parameter.plot.volume_max_to_inject;
	}
	
	return system.state.measured.fluid_added.volume_total() < 
		system.parameter.plot.volume_max_to_inject *
		volume_system;
	
}

void simulate::Menu::capture_this_state(dst::System& system)
{
	const double target =
			system.parameter.plot.capture_frequency_in_volume_fraction *
			system.measured.states.size();
	
	const double volume_system = system.measured.initial_fluid.volume_total();
	bool capture = false;
	
	if(system.parameter.simulation.is_flow_const_flow_rate && 
		volume_system <= 1.1 &&
		volume_system >= 0.9
	)
	{
		// Need to capture based on time_elapsed and not volume injected
		// Because for high sigmas, flow back happens,
		// Fluid is added from the outlet boundary
		
		capture = (system.state.measured.time_elapsed >= target);
	}
	else
	{
		capture =
			system.state.measured.fluid_added.volume_total() / volume_system >= target;
	}
	
	
	if(capture)
	{
		step::Part10Measure::capture(system);
		system.measured.states.push_back(system.state);
	}
}


void simulate::Menu::high_frequency_measurement(dst::System& system)
{
	if(system.state.reference.id_step % 10 == 0)
	{
		step::Part10Measure::high_frequency_data(system);
	}
}

void simulate::Menu::print_time_spent(const double time_program, const dst::System& system)
{
	const auto& state = system.state;
	std::cout << "Time simulation=" << d(time_program/1000) << "s" << std::endl;
	std::cout << "Time per step=" << d(time_program/state.reference.id_step) << "ms, " << "n_steps=" << state.reference.id_step << std::endl;
	std::cout <<  ", spent on linear equations." << std::endl;

	int count = 0;
	for(auto t_step: system.measured.time_taken_by_each_step)
	{
		std::cout << "step-" << count++ << " t=" << std::setw(5) << std::setprecision(2) << std::fixed << t_step / 1000 << "s, tf=";
		std::cout << std::setprecision(0) << std::round(t_step / time_program * 100) << "%" << '\n';
	}
}


dst::SystemOutput simulate::Menu::run(
	const dst::Parameter& parameter
)
{
	utility::Time time;

	dst::System system(SystemGenerator::generate_parameter_processed_and_basic_state(parameter));
	
	std::cout << std::endl << "\n\n" << std::string(30, '=') << '\n';
	std::cout << "Simulation started\n" << system.parameter.str_cmd() << std::endl;
	
	Preparation::run(system);	
	SetSolver::run(system);
	system.measured.time_taken_by_each_step[0] += time.passed();
	//system.print_matrix();
	
	system.state.reference.id_step = 0;
	while(inject_more_fluid(system))
	{
		++ system.state.reference.id_step;
		
		step::AllParts::run_single_time_step(system);
		//~ step::AllParts::run_single_time_step_debug(system);
		
		//REMOVE
		//return dst::SystemOutput(system.parameter, system.measured);
		
		capture_this_state(system);
		high_frequency_measurement(system);
		
	}

	print_time_spent(time.passed(), system);
	
	return dst::SystemOutput(system.parameter, system.measured);
}



